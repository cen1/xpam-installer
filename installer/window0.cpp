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
#include "window0.h"
#include "ui_window0.h"

#include "install.h"
#include "config.h"

#define EURO_VERSION 18

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
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

//Second next button, system paths
void Window0::on_nextButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);

    //w3 path
    if (ui->lineEdit->text() == "")
    {
        Registry reg;
        QString w3dir = reg.getInstallPath();
        if (w3dir != "")
        {
            ui->lineEdit->setText(w3dir);
        }
        else
        {
            ui->errlabel_2->setText("Info: "+Util::getLastErrorMsg());
            w3dir=Winutils::getProgramFiles();
            if (w3dir!="") {
                ui->lineEdit->setText(w3dir+"\\Warcraft III");
            }
            else ui->errlabel_1->setText("Info: "+Util::getLastErrorMsg());
        }
    }
    //client path
    if (ui->lineEdit_2->text() == ""){
        QString pf = Winutils::getProgramFiles();
        if (pf != "")
        {
            ui->lineEdit_2->setText(pf+"\\Eurobattle.net");
        }
        else ui->errlabel_3->setText("Info: "+Util::getLastErrorMsg());
    }

}

//Folder browser dialog for W3 path
void Window0::on_pushButton_clicked()
{
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    p=p.replace(QChar('/'), QChar('\\'));
    ui->lineEdit->setText(p);
}

//Folder browser dialog for Eurobattle path
void Window0::on_pushButton_2_clicked()
{
    const QString path = QFileDialog::getExistingDirectory(this);
    QString p = path;
    p=p.replace(QChar('/'), QChar('\\'));
    ui->lineEdit_2->setText(p+"\\Eurobattle.net");
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
    //1. Check if paths exist
    if (!QDir(ui->lineEdit->text()).exists())
    {
        ui->errlabel_1->setText("Error: Warcraft III directory does not exist");
    }
    else if (!QDir(basepath).exists())
    {
        ui->errlabel_1->setText("Error: Client directory does not exist");
    }
    else
    {

        config->W3PATH = ui->lineEdit->text();
        config->EUROPATH = ui->lineEdit_2->text();
        if (config->W3PATH.endsWith('\\') || config->W3PATH.endsWith('/')) config->W3PATH.remove(config->W3PATH.length()-1, 1);
        if (config->EUROPATH.endsWith('\\') || config->EUROPATH.endsWith('/')) config->EUROPATH.remove(config->EUROPATH.length()-1, 1);

        //one final check that W3 dir is real
        QFile war3(config->W3PATH+"\\war3.exe");
        if (!war3.exists()) {
            ui->errlabel_1->setText("Warcraft III directory is invalid");
            return;
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
                    if (!reg.setRegString(rkey2, "InstallPath", config->W3PATH)){
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
            if (reg.getInstallPath()=="") reg.setRegString(rkey, "InstallPath", config->W3PATH);

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
        else if (!reg.setW3dir(config->W3PATH)) {
            ui->errlabel_1->setText("W3dir registry error: "+Util::getLastErrorMsg());
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
