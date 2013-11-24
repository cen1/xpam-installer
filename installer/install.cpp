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
#include <QTextStream>
#include "QStringList"
#include "util.h"
#include "registry.h"

Install::Install()
{
    isAbort=false;
}

/*
 *TOP LEVEL INSTALL DIRECTIONS
 */
void Install::startInstall()
{
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("Received w3 path: "+this->config->W3PATH);
    emit sendInfo("Received euro path: "+this->config->EUROPATH);
    emit sendInfo(".........................................");
    emit sendInfo(".........................................");
    emit sendInfo(".........................................");
    updateW3();
    if (isAbort)
    {
        rupdateW3();
        emit finished(true);
    }
    else {
        emit setValue(20);
        updateMPQ();
        if (isAbort) {
            rupdateMPQ();
            rupdateW3();
            emit finished(true);
        }
        else {
            emit setValue(40);
            extractFiles();
            if (isAbort)
            {
                rextractFiles();
                rupdateMPQ();
                rupdateW3();
                emit finished(true);
            }
            else {
                emit setValue(60);
                updateGateways();
                if (isAbort)
                {
                    rupdateGateways();
                    rextractFiles();
                    rupdateMPQ();
                    rupdateW3();
                    emit finished(true);
                }
                else {
                    emit setValue(80);
                    finish();
                    if (isAbort)
                    {
                        rfinish();
                        rupdateGateways();
                        rextractFiles();
                        rupdateMPQ();
                        rupdateW3();
                        emit finished(true);
                    }
                    else {
                        emit setValue(100);
                        emit sendInfo("=================================");
                        emit sendInfo("=================================");
                        emit sendInfo("===== Installation finished =====");
                        emit finished(true);
                    }
                }
            }
        }
    }
}

void Install::abortInstall()
{
    emit sendInfo("!!! Aborting install !!!");
    emit sendInfo("!!! Aborting install !!!");
    emit sendInfo("!!! Aborting install !!!");
    isAbort=true;
}

bool Install::updateW3()
{
    emit sendInfo("Checking for Warcraft III updates");

    QString version = Winutils::getFileVersion(config->W3PATH+"\\war3.exe");
    emit sendInfo("Detected W3 version: "+version);

    if (version.startsWith("ERROR")) {
        emit sendInfo("Could not get w3 language, reason:");
        emit sendInfo(version);
        isAbort=true;
        return false;
    }
    if (version != config->W3VERSION) {
        emit sendInfo("W3 needs to be updated... downloading the patch");
        emit sendInfo("WARNING: downloading the patch can take a few minutes!");

        //get w3 language
        Mpq mpq;
        if (mpq.open(config->W3PATH+"\\war3.mpq")==false) {
            emit sendInfo("Could not open war3.mpq: "+Util::getLastErrorMsg());
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

        if (!this->bnftp(langid)) {
            emit sendInfo("Could not download the patch MPQ");
            isAbort=true;
            return false;
        }

        emit sendInfo("MPQ downloaded. Starting the update.");

        if (!this->bnupdate(langid)) {
            emit sendInfo("Could not patch the MPQ");
            isAbort=true;
            return false;
        }

        return true;
    }
    else {
        emit sendInfo("Version is up to date");
    }
    return true;
}

bool Install::updateMPQ()
{
     emit sendInfo("Updating MPQ with custom icons");
    //O = open
    //d = delete file
    //f = flush
    //a = add from to
    //C = close
    //exit
    Mpq mpq;
    QFile inputFile(":\\data\\eurobattle.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");

            if (l[0]=="O") {
                if (mpq.open(config->W3PATH+"\\"+l[1])==false) {
                    emit sendInfo(Util::getLastErrorMsg()+config->W3PATH+"\\"+l[1]);
                    isAbort=true;
                    return false;
                }
            }
            else if(l[0]=="d") {
                mpq.removeFile(l[1]);
            }
            else if(l[0]=="f") {

            }
            else if(l[0]=="a") {
                QFile f(":\\data\\"+l[1]);
                f.open(QIODevice::ReadOnly);
                QByteArray ba;
                ba = f.readAll();
                DWORD size=ba.size();
                emit sendInfo(l[2]+" ("+QString::number(size)+")");

                if (size==0) return false;
                if (mpq.createFile(l[2], size)==false) {
                    emit sendInfo(Util::getLastErrorMsg());
                    isAbort=true;
                    return false;
                }
                if (mpq.writeFile(ba)==false) {
                    emit sendInfo(Util::getLastErrorMsg());
                    isAbort=true;
                    return false;
                }
                if (mpq.finishWriteFile()==false) {
                    emit sendInfo(Util::getLastErrorMsg());
                    isAbort=true;
                    return false;
                }
            }
            else if(l[0]=="c") {
                emit sendInfo("Closing mpq");
                mpq.close();
            }
            else if(l[0]=="exit") {
                emit sendInfo("End of eurobattle.txt instruction file");
                inputFile.close();
                return true;
            }
        }
    }
    else {
        emit sendInfo("Could not open file data\\eurobattle.txt");
        isAbort=true;
        return false;
    }
    emit sendInfo("Something went terribly wrong...");
    return false;
}

bool Install::extractFiles()
{
    emit sendInfo("Extracting files");

    QFile::copy(":\\data\\w3l.exe", config->W3PATH+"\\w3l.exe");
    QFile::copy(":\\data\\w3lh.dll", config->W3PATH+"\\w3lh.dll");
    QFile::copy(":\\data\\gproxy.exe", config->EUROPATH+"\\gproxy.cfg");
    QFile::copy(":\\data\\gproxy.log", config->EUROPATH+"\\gproxy.log");
    QFile::copy(":\\data\\xpam_pub.pem", config->EUROPATH+"\\xpam_pub.pem");
    QFile::copy(":\\data\\xpam.exe", config->EUROPATH+"\\xpam.exe");
    QFile::copy(":\\data\\xpam.exe", config->EUROPATH+"\\xpam.exe");

    QFile::copy(":\\data\\sounds\\challenge-completed.wav", config->EUROPATH+"\\sounds\\challenge-completed.wav");
    QFile::copy(":\\data\\sounds\\challenge-started.wav", config->EUROPATH+"\\sounds\\challenge-started.wav");
    QFile::copy(":\\data\\sounds\\friend-join-game.wav", config->EUROPATH+"\\sounds\\friend-join-game.wav");
    QFile::copy(":\\data\\sounds\\hosted.wav", config->EUROPATH+"\\sounds\\hosted.wav");
    QFile::copy(":\\data\\sounds\\moderate.wav", config->EUROPATH+"\\sounds\\moderate.wav");
    QFile::copy(":\\data\\sounds\\slap.wav", config->EUROPATH+"\\sounds\\slap.wav");
    QFile::copy(":\\data\\sounds\\started.wav", config->EUROPATH+"\\sounds\\started.wav");
    QFile::copy(":\\data\\sounds\\unmoderate.wav", config->EUROPATH+"\\sounds\\unmoderate.wav");
    QFile::copy(":\\data\\sounds\\whisper.wav", config->EUROPATH+"\\sounds\\whisper.wav");

    emit sendInfo("Finished extracting files");
    return true;
}

bool Install::updateGateways()
{
    emit sendInfo("Updating gateways");
    Registry r;
    DWORD d = r.setGateways();
    if (d==ERROR_SUCCESS) {
        emit sendInfo("Successfully modified Battle.net Gateways");
        return true;
    }
    else {
        emit sendInfo("Could not modify Battle.net Gateways: "+QString::number(d));
        isAbort=true;
        return false;
    }
    return false;
}

bool Install::finish()
{
    emit sendInfo("Finishing");

    //create xpam.exe shortcut
    if(!QFile::link(this->config->EUROPATH+"\\xpam.exe", Winutils::getDesktop()+"\\Eurobattle Launcher.lnk")) {
        emit sendInfo("Could not create desktop shortcut. It already exists?");
    }
    return true;
}

bool Install::rupdateW3()
{
    emit sendInfo("Rolling back W3 update");
    return false;
}

bool Install::rupdateMPQ()
{
    emit sendInfo("Rolling back MPQ icons");
    return false;
}

bool Install::rextractFiles()
{
    emit sendInfo("Rolling back loaders");
    return false;
}

bool Install::rupdateGateways()
{
    emit sendInfo("Rolling back gateways");
    return false;
}

bool Install::rfinish()
{
    emit sendInfo("Rolling back Eurobattle.net software");
    return false;
}

bool Install::bnftp(QString langid) {
    return true;
}

bool Install::bnupdate(QString langid) {
    return true;
}
