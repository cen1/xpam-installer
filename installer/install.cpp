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

#include "install.h"
#ifndef WINUTILS_H
    #include "winutils.h"
#endif
#include "QFile"
#include "mpq.h"
#include "QRegExp"
#include "iostream"
#include "fstream"
#include "bnftp.h"
#include <QThread>


Install::Install()
{
    isAbort=false;
}

/*
 *TOP LEVEL INSTALL DIRECTIONS
 */
void Install::startInstall()
{
    emit sendInfo("Starting installation process");
    updateW3();
    if (isAbort)
    {
        rupdateW3();
    }
    emit setValue(20);


    updateMPQ();
    if (isAbort)
    {
        rupdateMPQ();
        rupdateW3();
    }
    emit setValue(40);


    applyLoaders();
    if (isAbort)
    {
        rapplyLoaders();
        rupdateMPQ();
        rupdateW3();
    }
    emit setValue(60);


    updateGateways();
    if (isAbort)
    {
        rupdateGateways();
        rapplyLoaders();
        rupdateMPQ();
        rupdateW3();
    }
    emit setValue(80);


    installEurobattle();
    if (isAbort)
    {
        rinstallEurobattle();
        rupdateGateways();
        rapplyLoaders();
        rupdateMPQ();
        rupdateW3();
    }
    emit setValue(100);


    emit sendInfo("Installation finished");
    emit finished(true);
}

void Install::abortInstall()
{
    emit sendInfo("Aborting install");
    isAbort=true;
}

bool Install::updateW3()
{
    emit sendInfo("Updating Warcraft III");

    //check war3 version
    QString version = Winutils::getFileVersion(config->W3PATH+"\\war3.exe");
    emit sendInfo("Detected W3 version: "+version);

    if (version != config->W3VERSION) {
        emit sendInfo("W3 needs to be updated... downloading the patch");
        emit sendInfo("WARNING: downloading the patch can take a few minutes!");

        //get w3 language
        Mpq mpq;
        if (mpq.open(config->W3PATH+"\\war3.mpq")==false) {
            emit sendInfo("Could not open war3.mpq. Path tried: "+config->W3PATH+"\\war3.mpq");
            emit sendInfo("Close your W3 or any other program that is locking the file.");
            isAbort=true;
            return false;
        }
        if (mpq.openFile("config.txt")==false){
            emit sendInfo("Could not open file: config.txt");
            isAbort=true;
            return false;
        }
        QString content = mpq.readFileToString();
        if (content==""){
            emit sendInfo("Did not receive any content from config.txt");
            isAbort=true;
            return false;
        }
        //get LANGID from content
        int t = content.length()-content.lastIndexOf("LANGID");
        QString tmp = content.right(t);
        QRegExp regex("LANGID='([a-zA-Z]{4})'");
        regex.indexIn(tmp);
        QString langid = regex.cap(1);
        emit sendInfo("LANGID detected: "+langid);

        QString cmd = "cd data && bnftp.exe --client=W3XP --arch=IX86 --file=W3XP_IX86_1xx_126A_"+langid+".mpq "+config->BNET_EUROPE+" 6112";
        //start download
        Bnftp *bnftp=new Bnftp();
        QThread *dlthread = new QThread();
        QObject::connect(this, SIGNAL(startDl(QString)), bnftp, SLOT(startDl(QString)));
        bnftp->moveToThread(dlthread);
        dlthread->start();
        emit startDl(cmd);

        //wait a bit so bnftp kicks in and makes the log file
        Sleep(3000);
        std::ifstream in;
        std::string line;
        bool finished=false;
        while (true) {
            in.open("data\\bnftplog.txt");
            while (getline(in, line)) {
                if (line.find("EXIT_SUCCESS")!=std::string::npos) {
                    finished = true;
                    break;
                }
            }
            if (finished) break;
            Sleep(5000);
            emit sendInfo("Downloading MPQ..");
            if (isAbort) break;
            in.close();
        }
        if (isAbort) return false;

        emit sendInfo("MPQ downloaded. Starting the update.");
        return true;
    }
    else {
        emit sendInfo("Version is up to date");
    }
    return true;
}

void Install::updateMPQ()
{
     emit sendInfo("Updating MPQ with custom icons");
    //O = open
    //d = delete file
    //f = flush
    //a = add from to
    //C = close
    //exit
}

void Install::applyLoaders()
{
     emit sendInfo("Applying loader");
}

void Install::updateGateways()
{
     emit sendInfo("Updating gateway");
}

void Install::installEurobattle()
{
     emit sendInfo("Installing Eurobattle.net software");
}

void Install::rupdateW3()
{
     emit sendInfo("Rolling back W3 update");
}

void Install::rupdateMPQ()
{
     emit sendInfo("Rolling back MPQ icons");
}

void Install::rapplyLoaders()
{
     emit sendInfo("Rolling back loaders");
}

void Install::rupdateGateways()
{
     emit sendInfo("Rolling back gateways");
}

void Install::rinstallEurobattle()
{
     emit sendInfo("Rolling back Eurobattle.net software");
}
