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

#include <QFileDialog>
#include <QThread>
#include "window0.h"
#include "ui_window0.h"

#include "registry.h"
#include "winutils.h"
#include "install.h"

QThread *ithread = new QThread();
Install *install = new Install();
Winutils *wu = new Winutils();

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

//First next button
void Window0::on_nextButton_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

//Second next button
void Window0::on_nextButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    //w3 path
    if (ui->lineEdit->text() == "")
    {
        Registry reg;
        QString w3dir = QString::fromStdWString(reg.getInstallPath());
        if (w3dir != "")
        {
            ui->lineEdit->setText(w3dir);
        }
        else
        {
            ui->lineEdit->setText(wu->getProgramFiles()+"\\Warcraft III");
        }
    }
    //client path
    if (ui->lineEdit_2->text() == ""){
        QString pf = wu->getProgramFiles();
        if (pf != "")
        {
            ui->lineEdit_2->setText(pf+"\\Eurobattle");
        }
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
    ui->lineEdit_2->setText(p+"\\Eurobattle");
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
    QString basepath = ui->lineEdit_2->text().replace(QString("\\Eurobattle"), QString(""));
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
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    }

    install->setw3path(ui->lineEdit->text());
    install->seteuropath(ui->lineEdit_2->text());

    QObject::connect(this, SIGNAL(startInstall()), install, SLOT(startInstall()));
    QObject::connect(this, SIGNAL(abortInstall()), install, SLOT(abortInstall()));
    QObject::connect(install, SIGNAL(sendInfo(QString)), ui->textBrowser_2, SLOT(append(QString)), Qt::QueuedConnection);
    QObject::connect(install, SIGNAL(finished(bool)), ui->nextButton_4, SLOT(setEnabled(bool)), Qt::QueuedConnection);
    QObject::connect(install, SIGNAL(setValue(int)), ui->progressBar, SLOT(setValue(int)), Qt::QueuedConnection);
    install->moveToThread(ithread);
    ithread->start();
    emit startInstall();

    QString war3exe = ui->lineEdit->text()+"\\Frozen Throne.exe";
    ui->textBrowser_2->append(wu->getFileLang(war3exe));
}

//Next after installation
void Window0::on_nextButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
}

//Cancel aka abort installation
void Window0::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
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
