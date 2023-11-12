/*
Copyright (c) 2013, cen (imbacen@gmail.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 
   
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "winutils.h"
#include <QFileDialog>
#include <QThread>
#include <QSettings>
#include "window0.h"
#include "ui_window0.h"
#include <QTemporaryFile>
#include <QDebug>

#include "install.h"
#include "config.h"

#define EURO_VERSION 0

QThread *ithread = new QThread();
Install *install = new Install();
Config *config = new Config();

Window0::Window0(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window0)
{
    ui->setupUi(this);
}

Window0::~Window0()
{
    delete ui;
}

//First next button, welcome screen
void Window0::on_nextButton_1_clicked()
{
    if (!ui->checkBox_vcredist->isChecked() && !vcredistRun) {
        //2015-2019
        QFile vcredistResource2022(":\\data\\vc_redist.x64.exe");
        QString dst2022 = QDir::temp().absolutePath()+"/vc_redist.x64.exe";
        vcredistResource2022.copy(dst2022);
        QProcess p2015;
        p2015.start(dst2022);
        p2015.waitForFinished(-1);

        //TODO: for seam reason it seems the file is still busy after exit here and cant me removed
        QThread::sleep(1);

        QFile rm15(dst2022);
        rm15.setPermissions(QFile::ReadOther|QFile::WriteOther);
        if (rm15.exists() && rm15.remove()) {
            qDebug() << "removed 2022";
        }
        else {
            qDebug() << rm15.errorString();
        }

        //2013
        QFile vcredistResource2013(":\\data\\vcredist_x86.exe");
        QString dst2013 = QDir::temp().absolutePath()+"/vcredist_x86.exe";
        vcredistResource2013.copy(dst2013);
        QProcess p2013;
        p2013.start(dst2013);
        p2013.waitForFinished(-1);

        QThread::sleep(1);

        QFile rm13(dst2013);
        rm13.setPermissions(QFile::ReadOther|QFile::WriteOther);
        if (rm13.exists() && rm13.remove()) {
            qDebug() << "removed 2013";
        }
        else {
            qDebug() << rm13.errorString();
        }

        vcredistRun = true;
    }

    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

//Second next button, system paths
void Window0::on_nextButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);

    //Client path program files
    if (ui->lineEdit_2->text() == "") {
        QString pf = Winutils::getProgramFiles();
        if (pf != "")
        {
            ui->lineEdit_2->setText(pf+"\\Eurobattle.net");
        }
        else ui->errlabel_3->setText("Info: "+Util::getLastErrorMsg());
    }
}

//Folder browser dialog for W3 path latest
void Window0::on_pushButton_latest_clicked()
{    
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    if (p!="") { //On Cancel it returns empty
        p=p.replace(QChar('/'), QChar('\\'));
        ui->lineEdit_latest->setText(p);
    }
}

//Folder browser dialog for W3 path 126
void Window0::on_pushButton_126_clicked()
{
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    if (p!="") { //On Cancel it returns empty
        p=p.replace(QChar('/'), QChar('\\'));
        ui->lineEdit_126->setText(p);
    }
}

//Folder browser dialog for Eurobattle path
void Window0::on_pushButton_2_clicked()
{
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    if (p!="") {
        p=p.replace(QChar('/'), QChar('\\'));
        ui->lineEdit_2->setText(p+"\\Eurobattle.net");
    }
}

//First back button
void Window0::on_backButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

//Second back button
void Window0::on_backButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
}

//Finish button
void Window0::on_pushButton_3_clicked()
{
    qApp->quit();
}

//Install button
void Window0::on_nextButton_3_clicked()
{
    QString basepath = ui->lineEdit_2->text().replace(QString("\\Eurobattle.net"), QString(""));
    if (!QDir(basepath).exists())
    {
        ui->errlabel_1->setText("Error: Client directory does not exist");
    }
    else
    {
        if (!ui->lineEdit_latest->text().isEmpty()) {
            config->W3PATH_LATEST = ui->lineEdit_latest->text();
            if (config->W3PATH_LATEST.endsWith('\\') || config->W3PATH_LATEST.endsWith('/')) {
                config->W3PATH_LATEST.remove(config->W3PATH_LATEST.length()-1, 1);
            }
            if (!checkW3PathUnicode(config->W3PATH_LATEST, "Warcraft III.exe")) {
                ui->errlabel_1->setText("Warcraft III 1.28.5 directory is invalid");
                return;
            }
        }
        if (!ui->lineEdit_126->text().isEmpty()) {
            config->W3PATH_126 = ui->lineEdit_126->text();
            if (config->W3PATH_126.endsWith('\\') || config->W3PATH_126.endsWith('/')) {
                config->W3PATH_126.remove(config->W3PATH_126.length()-1, 1);
            }
            if (!checkW3PathUnicode(config->W3PATH_126, "war3.exe")) {
                ui->errlabel_1->setText("Warcraft III 1.26a directory is invalid");
                return;
            }
        }

        config->EUROPATH = ui->lineEdit_2->text();
        if (config->EUROPATH.endsWith('\\') || config->EUROPATH.endsWith('/')) {
            config->EUROPATH.remove(config->EUROPATH.length()-1, 1);
        }

        install->config = config;

        //set registry keys
        Registry reg;
        reg.createEuroKey();

        //create InstallPath and Battle.net Gateways if they do not yet exist
        CRegKey rkey;
        if (rkey.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_READ | KEY_WOW64_64KEY) != ERROR_SUCCESS){
            //if we can't open it create it (copied W3)
            if (!reg.createW3Key()) {
                ui->errlabel_1->setText("W3 registry key could not be open nor created");
                return;
            }
            else {
                rkey.Close();
                CRegKey rkey2;
                if (rkey2.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS){
                    if (!reg.setRegString(rkey2, "InstallPath", config->W3PATH_LATEST)){
                        ui->errlabel_1->setText("Could not create installpath "+Util::getLastErrorMsg());
                        return;
                    }
                    if (reg.setBnetGateways()!=ERROR_SUCCESS){
                        ui->errlabel_1->setText("Could not create gateways "+Util::getLastErrorMsg());
                        return;
                    }
                }
                else {
                    ui->errlabel_1->setText("W3 registry key was created but still can't be opened");
                    return;
                }
            }
        }
        else {
            if (reg.getInstallPath()=="") reg.setRegString(rkey, "InstallPath", config->W3PATH_LATEST);

            wchar_t * buffer=(wchar_t *)malloc(1024);
            ULONG bufsize=1024;
            if (!reg.getRegMultiString(&rkey, "Battle.net Gateways", buffer, &bufsize))
                reg.setBnetGateways();
            rkey.Close();
            delete buffer;
        }

        if (!reg.setEuropath(config->EUROPATH)) {
            ui->errlabel_1->setText("Eurobattle path registry error: "+Util::getLastErrorMsg());
        }
        else if (!reg.setPatchVersion(EURO_VERSION)) {
            ui->errlabel_1->setText("Patch version registry error: "+Util::getLastErrorMsg());
        }
        else {
            QObject::connect(this, SIGNAL(startInstall()), install, SLOT(startInstall()));
            QObject::connect(this, SIGNAL(abortInstall()), install, SLOT(abortInstall()));
            QObject::connect(install, SIGNAL(sendInfo(QString)), ui->textBrowser_2, SLOT(append(QString)), Qt::QueuedConnection);
            QObject::connect(install, SIGNAL(finished(bool)), ui->nextButton_4, SLOT(setEnabled(bool)), Qt::QueuedConnection);
            QObject::connect(install, SIGNAL(finished(bool)), this, SLOT(disableAbort(bool)), Qt::QueuedConnection);
            QObject::connect(install, SIGNAL(setValue(int)), ui->progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
            install->moveToThread(ithread);
            ithread->start();
            emit startInstall();

            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
        }
    }
}

//Next after installation
void Window0::on_nextButton_4_clicked()
{
    if (install->isAbort) ui->stackedWidget->setCurrentIndex(5);
    else ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

//Cancel aka abort installation
void Window0::on_pushButton_4_clicked()
{
    install->isAbort=true;
    emit abortInstall();
}

//When something goes wrong
void Window0::fail(QString msg)
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->label_6->setText(msg);
}

//Error Finish
void Window0::on_pushButton_5_clicked()
{
    qApp->exit();
}

void Window0::disableAbort(bool b)
{
    ui->pushButton_4->setEnabled(false);
}

bool Window0::checkW3PathUnicode(QString w3path, QString exeName) {
    bool isUnicode = false;

    for(int i = 0; i < w3path.size(); i++) {
        if(w3path.at(i).unicode() > 127) {
            isUnicode = true;
            break;
        }
    }

    //Check if W3 path contains .exe
    QFile f(w3path+"/"+exeName);
    if (!f.exists()) {
        QMessageBox mb(QMessageBox::Critical, "W3 path alert",
           "Your W3 path is missing '"+exeName+"' which probably means the path is incorrect.",
           QMessageBox::Ok);
         mb.exec();
         return false;
    }

    if (isUnicode) {
        QMessageBox mb(QMessageBox::Critical, "Unicode alert",
           "It appears your W3 is installed in  path that contains non-ASCII characters. Please move it to path that conains only ASCII characters or you will have a lot of problems.",
           QMessageBox::Ok);
         mb.exec();
         return false;
    }

    return true;
}
