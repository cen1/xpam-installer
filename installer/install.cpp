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
#include <QThread>
#include <QTextStream>
#include "QStringList"
#include "util.h"
#include "registry.h"
#include "QDir"
#include "QProcess"
#include "QCryptographicHash"

Install::Install()
{
    isAbort=false;
}
Install::~Install(){
    delete gateBuffer;
}

/*
 * TOP LEVEL INSTALL DIRECTIONS
 * It is only possible to abort after each step.
 * If you abort mid execution of the step the step will complete and then start reverting all steps
 */
void Install::startInstall()
{
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("===== Starting installation process =====");
    emit sendInfo("Received w3 path: "+config->W3PATH);
    emit sendInfo("Received euro path: "+config->EUROPATH);
    emit sendInfo(".........................................");
    emit sendInfo(".........................................");
    emit sendInfo(".........................................");

    extractFiles();
    if (isAbort)
    {
        rextractFiles();
        emit finished(true);
    }
    else {
        emit setValue(20);
        updateW3();
        if (isAbort) {
            rupdateW3();
            rextractFiles();
            emit setValue(0);
            emit finished(true);
        }
        else {
            emit setValue(40);
            updateMPQ();
            if (isAbort)
            {
                rupdateMPQ();
                rupdateW3();
                emit setValue(20);
                rextractFiles();
                emit setValue(0);
                emit finished(true);
            }
            else {
                emit setValue(60);
                updateGateways();
                if (isAbort)
                {
                    rupdateGateways();
                    rupdateMPQ();
                    emit setValue(40);
                    rupdateW3();
                    emit setValue(20);
                    rextractFiles();
                    emit setValue(0);
                    emit finished(true);
                }
                else {
                    emit setValue(80);
                    finish();
                    if (isAbort)
                    {
                        rfinish();
                        rupdateGateways();
                        emit setValue(60);
                        rupdateMPQ();
                        emit setValue(40);
                        rupdateW3();
                        emit setValue(20);
                        rextractFiles();
                        emit setValue(0);
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

/*
 * Abort slot. The installation can be aborted from the main thread
 * Usually this thread is too busy in the first place so the actual abort is via public member isAbort
 * We can check that mid-execution so it's a better solution
 */
void Install::abortInstall()
{
    emit sendInfo("!!! Aborting install !!!");
    emit sendInfo("!!! Aborting install !!!");
    emit sendInfo("!!! Aborting install !!!");
    isAbort=true;
}

/*
 * Extracting files from qrc, gproxy, client, config files etc
 * All extracted files are Read only on the disk! This is because they are Read only in the .qrc
 * We need to remove that because it causes all sort of trouble
 * The files that would get overwritten are first backed up in case of cancelation
 */
bool Install::extractFiles()
{
    emit sendInfo("=================================");
    emit sendInfo("=============STEP 1==============");
    emit sendInfo("=================================");
    emit sendInfo("Extracting files");

    //do a backup copy of any existing files
    if (Winutils::getAppData()=="") {
        emit sendInfo("Could not get AppData directory");
        isAbort=true;
        return false;
    }

    config->APPDATA=Winutils::getAppData()+"\\Eurobattle.net";

    QDir d(config->APPDATA);
    roamingExisted=false;
    if (d.exists()) roamingExisted=true;

    QDir e(config->EUROPATH);
    progFilesExisted=false;
    if (e.exists()) progFilesExisted=true;

    QDir dl(config->W3PATH+"\\Maps\\Download");
    if (!dl.exists()) {
        emit sendInfo("Creating Maps/Downloads folder since it does not exist");
        if (!QDir().mkpath(config->W3PATH+"\\Maps\\Download")) {
            emit sendInfo("Could not create Maps/Downloads folder");
            isAbort=true;
            return false;
        }
    }

    if (!QDir().mkpath(config->APPDATA)) {
        emit sendInfo("Could not create AppData/Eurobattle.net folder");
        isAbort=true;
        return false;
    }
    if (!bextractFiles()) {
        emit sendInfo("Backing up failed..");
        isAbort=true;
        return false;
    }


    if (!QDir().mkpath(config->EUROPATH)) { //if it already exists returns true!!!
        emit sendInfo("Could not create Eurobattle.net folder");
        isAbort=true;
        return false;
    }
    if (!QDir().mkpath(config->EUROPATH+"\\sounds")) {
        emit sendInfo("Could not create Eurobattle.net sounds folder");
        isAbort=true;
        return false;
    }
    if (!QDir().mkpath(config->EUROPATH+"\\platforms")) {
        emit sendInfo("Could not create Qt platforms folder");
        isAbort=true;
        return false;
    }
    if (!QDir().mkpath(config->EUROPATH+"\\uninstall")) {
        emit sendInfo("Could not create Eurobattle.net uninstall folder");
        isAbort=true;
        return false;
    }

    QFile inputFile(":\\data\\move.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");

            if (l[0]=="m") {

                //REMOVE THE FUCKING READ-ONLY FROM FILES
                //GOD FUCKING DAMN!!!!


                if  (l[2]=="EUROPATH") {
                    QFile p(config->EUROPATH+"\\"+l[1]);
                    if (p.exists()) {
                        p.setPermissions(QFile::ReadOther | QFile::WriteOther);

                        emit sendInfo("Deleting "+config->EUROPATH+"\\"+l[1]);
                        if (!p.remove()) {
                            emit sendInfo("Could not delete file. "+p.errorString());
                            isAbort=true;
                            return false;
                        }
                    }

                    QFile c(":\\data\\"+l[1]);
                    emit sendInfo("Copying :\\data\\"+l[1]+" to "+config->EUROPATH+"\\"+l[1]);
                    if (!c.copy(config->EUROPATH+"\\"+l[1])) {
                        emit sendInfo("Could not copy file. "+c.errorString());
                        isAbort=true;
                        return false;
                    }
                    QFile f(config->EUROPATH+"\\"+l[1]);
                    f.setPermissions(QFile::ReadOther | QFile::WriteOther);
                    p.close();
                    c.close();
                    f.close();
                }
                else if(l[2]=="W3PATH") {
                    QFile p(config->W3PATH+"\\"+l[1]);

                    if (p.exists() && l[3]=="ignore") {
                        p.close();
                        continue;
                    }

                    if (p.exists()) {
                        if (!p.setPermissions(QFile::ReadOther | QFile::WriteOther)) emit sendInfo("HOLY FUCKING FAIL");

                        emit sendInfo("Deleting "+config->EUROPATH+"\\"+l[1]);
                        if (!p.remove()) {
                            emit sendInfo("Could not delete file. "+p.errorString());
                            isAbort=true;
                            return false;
                        }
                    }

                    QFile c(":\\data\\"+l[1]);
                    emit sendInfo("Copying :\\data\\"+l[1]+" to "+config->W3PATH+"\\"+l[1]);
                    if (!c.copy(config->W3PATH+"\\"+l[1])) {
                        emit sendInfo("Could not copy file. "+c.errorString());
                        isAbort=true;
                        return false;
                    }
                    QFile f(config->W3PATH+"\\"+l[1]);
                    f.setPermissions(QFile::ReadOther | QFile::WriteOther);
                    p.close();
                    c.close();
                    f.close();
                }
            }
            else if (l[0]=="r") {
                if  (l[2]=="EUROPATH") QFile::remove(config->EUROPATH+"\\"+l[1]);
                else if(l[2]=="W3PATH") QFile::remove(config->W3PATH+"\\"+l[1]);
            }
        }
    }
    else {
        emit sendInfo("Could not open file data\\move.txt");
        isAbort=true;
        return false;
    }
    inputFile.close();
    emit sendInfo("Finished extracting files");

    return true;
}

/*
 * There are quite a few steps needed to update W3
 * First we backup all the files which will be changes in the process in case of cancelation
 * Then we get war3.exe version and compare it to 1.26a
 * If it needs to be updated we extract LANGID from mpq so we know which patch mpq to download (each language is different mpq)
 * We call bnftp and then bnupdate
 */
bool Install::updateW3()
{
    emit sendInfo("=================================");
    emit sendInfo("=============STEP 2==============");
    emit sendInfo("=================================");

    emit sendInfo("Checking for Warcraft III updates");

    QString version = Winutils::getFileVersion(config->W3PATH+"\\war3.exe");
    emit sendInfo("Detected W3 version: "+version);

    if (version.startsWith("ERROR")) {
        emit sendInfo("Could not get w3 version, reason:");
        emit sendInfo(version);
        emit sendInfo("Will assume that W3 is up to date.. skipping");
        w3wasupdated=false;
        return true;
    }
    if (version != config->W3VERSION) {
        emit sendInfo("W3 needs to be updated to latest patch!");
        /*emit sendInfo("WARNING: downloading the patch can take a few minutes!");

        //get w3 language
        Mpq mpq;
        if (mpq.open(config->W3PATH+"\\war3.mpq")==false) {
            emit sendInfo("Could not open war3.mpq: "+Util::getLastErrorMsg());
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }
        if (mpq.openFile("config.txt")==false){
            emit sendInfo("Could not open file: config.txt");
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }
        QString content = mpq.readFileToString();
        if (content==""){
            emit sendInfo("Did not receive any content from config.txt");
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }
        //get LANGID from content
        int t = content.length()-content.lastIndexOf("LANGID");
        QString tmp = content.right(t);
        QRegExp regex("LANGID='([a-zA-Z]{4})'");
        regex.indexIn(tmp);
        QString langid = regex.cap(1);
        emit sendInfo("LANGID detected: "+langid);

        config->LANGID=langid;
        config->ARCHIVE="W3XP_IX86_1xx_126A_"+langid+".mpq";
        config->ARCHIVE_FULL=config->EUROPATH+"\\W3XP_IX86_1xx_126A_"+langid+".mpq";

        //check if this is a reinstall
        if (!QFile::exists(config->ARCHIVE_FULL)) {
            emit sendInfo("Patch does not exist. Preparing to download it.");

            if (!this->bnftp()) {
                emit sendInfo("Could not download the patch MPQ");
                emit sendInfo("Skipping W3 update");
                w3wasupdated=false;
                return true;
            }
        }

        emit sendInfo("MPQ downloaded. Checking the hash.");

        QFile file(config->EUROPATH+"\\W3XP_IX86_1xx_126A_"+langid+".mpq");
        file.open(QFile::ReadOnly);
        if (!file.isOpen()) {
            emit sendInfo("Could not open the patch MPQ");
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }

        QString sha1(QCryptographicHash::hash(file.readAll(), QCryptographicHash::Sha1).toHex());
        if (sha1!=config->hashmap[langid]) {
            emit sendInfo("MPQ hash mismatch. File is corrupted.");
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }

        emit sendInfo("HASH OK");
        emit sendInfo("Starting the patch process");

        file.close();

        if (!this->bnupdate()) {
            emit sendInfo("Could not patch the MPQ");
            emit sendInfo("Skipping W3 update");
            w3wasupdated=false;
            return true;
        }
        w3wasupdated=true;
        */
        isAbort=true;
        return false;
    }
    else {
        emit sendInfo("Version is up to date");
    }
    w3wasupdated=false;
    return true;
}

/*
 * Insert custom channel icons to War3Patch.mpq
 * No extraction to disk, direct insertion from .qrc
 */
bool Install::updateMPQ()
{
    emit sendInfo("=================================");
    emit sendInfo("=============STEP 3==============");
    emit sendInfo("=================================");

    //back up
    if (!bupdateMPQ()) {
        emit sendInfo("Backup process failed");
        isAbort=true;
        return false;
    }

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
                //copy war3patch.mpq to uninstall/
                QFile tmp(config->EUROPATH+"\\uninstall\\"+l[1]);
                if (tmp.exists()) tmp.remove();

                QFile::copy(config->W3PATH+"\\"+l[1], config->EUROPATH+"\\uninstall\\"+l[1]);

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
                f.close();
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

/*
 * We add server gateway and gproxy (localhost) gateway
 */
bool Install::updateGateways()
{
    emit sendInfo("=================================");
    emit sendInfo("=============STEP 4==============");
    emit sendInfo("=================================");

    //backup existing gateways
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        Registry r;
        gateBuffer = (wchar_t *)malloc(1024);
        gateSize=1024;
        if (!r.getRegMultiString(&reg, "Battle.net Gateways", gateBuffer, &gateSize)) {
            emit sendInfo("Could not backup the gateways");
            gateBackupFailed=true;
        }
        else {
            gateBackupFailed=false;
            emit sendInfo("Backed up "+QString::number(gateSize)+" bytes");
        }
    }
    else {
        emit sendInfo("Could not open gateway key");
        isAbort=true;
        return false;
    }

    //update
    emit sendInfo("Updating gateways");
    Registry r;
    DWORD d = r.setGateways();
    if (d==ERROR_SUCCESS) {
        emit sendInfo("Successfully modified Battle.net Gateways");

        //backup installpath
        Registry b;
        old_installpath = b.getInstallPath(); //we dont really care if this is empty because it might not exist

        //update InstallPath
        Registry p;
        if(p.setInstallPath(config->W3PATH)) {
            emit sendInfo("Successfully modified InstallPath");
            return true;
        }
        else {
            emit sendInfo("Could not modify InstallPath");
            isAbort=true;
            return false;
        }

    }
    else {
        emit sendInfo("Could not modify Battle.net Gateways: "+QString::number(d));
        isAbort=true;
        return false;
    }

    return false;
}

/*
 * Creating desktop shortcut
 * Any other minor stuff that might be needed in the future
 */
bool Install::finish()
{
    emit sendInfo("=================================");
    emit sendInfo("=============STEP 5==============");
    emit sendInfo("=================================");

    emit sendInfo("Finishing");

    QFile f(Winutils::getDesktop()+"\\Eurobattle.net Client.lnk");
    if (f.exists()) desktopShortcutExisted=true;
    else desktopShortcutExisted=false;
    f.close();

    //create xpam.exe shortcut
    if(!QFile::link(this->config->EUROPATH+"\\xpam.exe", Winutils::getDesktop()+"\\Eurobattle.net Client.lnk")) {
        emit sendInfo("Could not create desktop shortcut. It already exists?");
    }

    //create registry entries for Add/Remove programs and other info
    Registry reg;
    if (reg.addInstallationEntries(config) == 1) {
        emit sendInfo("Unable to add registry entry for Add/Remove programs");
        isAbort=true;
    }

    //isAbort=true; //uncomment to test full reversal of installation

    if (!isAbort) {
        QDir d(config->APPDATA);
        d.removeRecursively();
    }
    return true;
}

/*
 * Copy back all the backed up files from AppData
 */
bool Install::rupdateW3()
{
    if (w3wasupdated){
        emit sendInfo("Rolling back W3 update");
        return true;
    }
    else {
        emit sendInfo("W3 was not updated. Nothing to revert.");
        return true;
    }
}

/*
 * Reverts mpq changes in War3Patch.mpq by copying back the backup
 */
bool Install::rupdateMPQ() {
    emit sendInfo("Rolling back icons");

    QFile f(config->W3PATH+"\\War3Patch.mpq");
    if (f.exists()) f.remove();
    f.close();

    QFile p(config->APPDATA+"\\MPQ\\War3Patch.mpq");

    if (!p.copy(config->W3PATH+"\\War3Patch.mpq")) {
        emit sendInfo("Could not revert the file: "+p.errorString());
        isAbort=true;
        return false;
    }
    p.close();

    QDir d(config->APPDATA+"\\MPQ");
    d.removeRecursively();

    return true;
}

/*
 * We copy back all the backed up files in AppData
 * And also remove the AppData subfolders
 */
bool Install::rextractFiles()
{
    emit sendInfo("Deleting new files ("+QString::number(newFiles.length())+")");

    //delete new files
    for (int i=0; i<newFiles.length(); i++){
        emit sendInfo("Deleting "+newFiles[i]);
        QFile r(newFiles[i]);
        if (!r.remove()){
            emit sendInfo("Could not remove "+r.fileName());
        }
        r.close();
    }
    //copy backed files
    for (int i=0; i<backedEuroFilesFROM.length(); i++) {
        QFile b(backedEuroFilesTO[i]);
        emit sendInfo("Reverting "+backedEuroFilesTO[i]);
        QFile t(backedEuroFilesFROM[i]);
        if (t.exists()) t.remove();
        if (!b.copy(backedEuroFilesFROM[i])) {
            emit sendInfo("Failed to copy the backup"+b.errorString());
        }
        b.close();
        t.close();
    }
    for (int i=0; i<backedW3FilesFROM.length(); i++) {
        QFile b(backedW3FilesTO[i]);
        emit sendInfo("Reverting "+backedW3FilesTO[i]);
        QFile t(backedW3FilesFROM[i]);
        if (t.exists()) t.remove();
        if (!b.copy(backedW3FilesFROM[i])) {
            emit sendInfo("Failed to copy the backup"+b.errorString());
        }
        b.close();
        t.close();
    }

    QDir d1(config->APPDATA+"\\EUROPATH");
    d1.removeRecursively();
    QDir d2(config->APPDATA+"\\W3PATH");
    d2.removeRecursively();

    if (!roamingExisted){
        QDir d(config->APPDATA);
        d.removeRecursively();
    }

    if (!progFilesExisted){
        QDir d(config->EUROPATH);
        d.removeRecursively();
    }
    emit sendInfo("INSTALLATION FAILED OR WAS CANCELED. SEE THE ABOVE LOG FOR ERRORS OR CONTACT TECHNICAL SUPPORT");

    return true;
}

/*
 * Change gateways back to what they were before install
 */
bool Install::rupdateGateways()
{
    if (!gateBackupFailed) {
        emit sendInfo("Rolling back gateways");
        Registry r;
        gateSize*=2; //because winapi returns the size in bytes but wchar_t is actually 2 bytes
        DWORD d = r.setOriginalGateways(gateBuffer, gateSize);
        if (d==ERROR_SUCCESS) {
            emit sendInfo("Successfully reverted Battle.net Gateways");
        }
        else {
            emit sendInfo("Could not revert Battle.net Gateways: "+QString::number(d));
            isAbort=true;
            return false;
        }
    }
    else {
        emit sendInfo("Gateway backup failed. Restoring to original Battle.net instead");
        Registry r;
        DWORD d = r.setBnetGateways();
        if (d==ERROR_SUCCESS) {
            emit sendInfo("Successfully reverted Battle.net Gateways to Battle.net originals");
        }
        else {
            emit sendInfo("Could not revert Battle.net Gateways: "+QString::number(d));
            isAbort=true;
            return false;
        }
    }

    //revert InstallPath
    Registry r;
    if (r.setInstallPath(old_installpath)) {
        emit sendInfo("Successfully reverted InstallPath");
        return true;
    }
    else {
        emit sendInfo("Could not revert InstallPath");
        isAbort=true;
        return false;
    }
    return false;
}

/*
 * Remove desktop shortcut if it did not exist before
 */
bool Install::rfinish()
{
    emit sendInfo("Rolling back Eurobattle.net finish step");

    if (!desktopShortcutExisted) QFile::remove(Winutils::getDesktop()+"\\Eurobattle.net Client.lnk");

    Registry reg;
    reg.removeInstallationEntries();

    return false;
}

/*
 * Runs bnftp.exe client (part of PvPGN project)
 * with parameters for full 1.26a W3 TFT patch with the detected language
 */
bool Install::bnftp() {

    //prepare parameters and working directory
    QString bnftpdir=config->EUROPATH;
    QString bnftpexe="\""+config->EUROPATH+"\\bnftp.exe\"";
    QStringList list;
    list << "--client=W3XP";
    list << "--arch=IX86";
    list << "--file="+config->ARCHIVE;
    list << config->BNET_EUROPE;
    list << "6112";

    emit sendInfo("Launching "+bnftpexe);

    QProcess qp;
    qp.setWorkingDirectory(bnftpdir);
    qp.start(bnftpexe, list);
    if (!qp.waitForStarted()) {
        emit sendInfo("Could not start bnftp.exe: "+qp.errorString());
        return false;
    }

    emit sendInfo("Bnftp started");
    int counter=0;
    while (true) {
        qp.waitForReadyRead();
        if (qp.canReadLine()) {
            QString line(qp.readLine());
            line=line.simplified();
            if (line.length()<255) emit sendInfo(line); //limit line length because last line is very long string of dots
        }
        else {
            if ((counter%500)==0) emit sendInfo("Download in progress..."); //bnftp is spamming the dots so we just limit the ouput a bit
        }
        counter++;
        if (qp.state() != QProcess::Running) break;
        if (isAbort) {
            qp.terminate();
            return false;
        }
    }
    return true;
}

/*
 * This is a manual replacement for BNUpdate.exe
 * 1. Extract files as instructed by prepatch.lst
 * 2. Extract mpqs listed by mpqs.lst
 * 3. For each extracted mpq do...
 * 4. Open patch.lst
 * 5. Lines are ; delimited. Either of type <to>;<from>;<hex offset?> or just <to>;<from>
 * 6. 3 part lines are meant for mpq to mpq patching while 2 part lines are for mpq to filesystem
 * 7. Files in the patch mpq are binary. We use binary patch tool bspatch against the existing file
 */
bool Install::bnupdate() {
    Mpq dlpatchmpq; //the patch mpq we just downloaded
    if (!dlpatchmpq.open(config->ARCHIVE_FULL)) {
        emit sendInfo("Could not open the patch archive: "+config->ARCHIVE_FULL);
        emit sendInfo(Util::getLastErrorMsg());
        return false;
    }

    //read prepatch.lst and extract files
    if (!dlpatchmpq.openFile("prepatch.lst")) {
        emit sendInfo("Could not open prepatch.lst");
        emit sendInfo(Util::getLastErrorMsg());
        return false;
    }
    QString prepatch = dlpatchmpq.readFileToString();
    dlpatchmpq.closeFile();

    QTextStream in(&prepatch);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList l = line.split(" ");

        if (l[0]=="extract") {
            emit sendInfo("Extracting from prepatch: "+l[1]);

            if (!dlpatchmpq.extractFile(l[1], config->W3PATH+"\\"+l[1])){
                emit sendInfo("Could not extract "+l[1]);
                emit sendInfo(Util::getLastErrorMsg());
                return false;
            }
        }
    }

    //extract mpqs.lst listed mpqs
    if (!dlpatchmpq.openFile("mpqs.lst")){
        emit sendInfo("Could not open mpqs.lst");
        emit sendInfo(Util::getLastErrorMsg());
        return false;
    }
    QString mpqslst = dlpatchmpq.readFileToString();
    dlpatchmpq.closeFile();

    QStringList cleanup;

    QTextStream in2(&mpqslst);
    QStringList mpqlist;

    while (!in2.atEnd()) {
        QString line = in2.readLine();
        line=line.simplified();
        mpqlist << line;
        emit sendInfo("Extracting partial mpq "+line);

        if (!dlpatchmpq.extractFile(line, config->EUROPATH+"\\"+line)) {
            emit sendInfo("Could not extract "+line);
            emit sendInfo(Util::getLastErrorMsg());
            return false;
        }
        cleanup << config->EUROPATH+"\\"+line;
    }

    //loop over all mpqs and perform the update
    //delete.lst
    //patch.lst: 3 parameters=move to War3Patch.mpq, 2 parameters=move to (InstallPath)\\<target>
    //revert.lst
    //hdfiles.lst
    Mpq war3patch;
    if (!war3patch.open(config->W3PATH+"\\War3Patch.mpq")){
        emit sendInfo("Could not open War3Patch.mpq");
        emit sendInfo(Util::getLastErrorMsg());
        return false;
    }

    for (QStringList::iterator it = mpqlist.begin(); it != mpqlist.end(); ++it) {
        Mpq partialmpq; //partial patch mpq that we just extracted

        emit sendInfo("Opening partial mpq "+config->EUROPATH+"\\"+*it);
        if (!partialmpq.open(config->EUROPATH+"\\"+*it)){
            emit sendInfo("Could not open "+*it);
            emit sendInfo(Util::getLastErrorMsg());
            return false;
        }
        if (!partialmpq.openFile("patch.lst")){
            emit sendInfo("Could not open patch.lst");
            emit sendInfo(Util::getLastErrorMsg());
            return false;
        }
        QString patchlst = partialmpq.readFileToString();
        partialmpq.closeFile();

        QTextStream in3(&patchlst);
        while (!in3.atEnd()) {
            QString line = in3.readLine();
            QStringList l = line.split(";");

            //to War3Patch.mpq
            if (l.size()==3) {
                emit sendInfo("Extracting to mpq "+l[1]);
                if (!partialmpq.openFile(l[1])){
                    emit sendInfo("Could not open "+l[1]);
                    emit sendInfo(Util::getLastErrorMsg());
                    return false;
                }
                QByteArray ba;
                if (!partialmpq.readFile(&ba)) {
                    emit sendInfo("Could not read "+l[1]);
                    emit sendInfo(Util::getLastErrorMsg());
                    return false;
                }
                emit sendInfo("Bytes read: "+QString::number(ba.size()));

                if (!war3patch.createFile(l[0], ba.size())){
                    emit sendInfo("Could not create "+l[0]);
                    emit sendInfo(Util::getLastErrorMsg());
                    return false;
                }
                if (!war3patch.writeFile(ba)){
                    emit sendInfo("Could not open write to "+l[0]);
                    emit sendInfo(Util::getLastErrorMsg());
                    return false;
                }
                war3patch.finishWriteFile();
                //war3patch.closeFile();
                partialmpq.closeFile();
            }
            else if (l.size()==2) {
                emit sendInfo("Extracting to directory "+l[1]);
                if (!partialmpq.extractFile(l[1], config->W3PATH+"\\"+l[0])) {
                    emit sendInfo("Could not extract "+l[1]);
                    emit sendInfo(Util::getLastErrorMsg());
                    return false;
                }
            }
        }
        partialmpq.close();
    }
    war3patch.close();

    //cleanup
    for (QStringList::iterator it = cleanup.begin(); it != cleanup.end(); ++it) {
        emit sendInfo("Removing "+*it);
        QFile::remove(*it);
    }


    return true;
}

/*
 * Backs up all files which could be overwritten
 * Backup locations are AppData/Roaming/Eurobattle.net/EUROPATH and
 * AppData/Roaming/Eurobattle.net/W3PATH
 */
bool Install::bextractFiles() {
    emit sendInfo("Backing up files before extraction");

    QDir().mkpath(config->APPDATA+"\\EUROPATH");
    QDir().mkpath(config->APPDATA+"\\EUROPATH\\sounds");
    QDir().mkpath(config->APPDATA+"\\EUROPATH\\platforms");
    QDir().mkpath(config->APPDATA+"\\W3PATH");

    QFile inputFile(":\\data\\move.txt");
    if (inputFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&inputFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList l = line.split(" ");

            if (l[0]=="m") {
                if  (l[2]=="EUROPATH") {
                    QFile p(config->EUROPATH+"\\"+l[1]);
                    if (p.exists()) {
                        emit sendInfo("Backing up "+config->EUROPATH+"\\"+l[1]);
                        QFile b(config->APPDATA+"\\EUROPATH\\"+l[1]);
                        if (b.exists()) b.remove();
                        b.close();

                        if (!p.copy(config->APPDATA+"\\EUROPATH\\"+l[1])) {
                            emit sendInfo("Could not backup file. "+p.errorString());
                            isAbort=true;
                            return false;
                        }
                        backedEuroFilesFROM << config->EUROPATH+"\\"+l[1];
                        backedEuroFilesTO << config->APPDATA+"\\EUROPATH\\"+l[1];
                    }
                    else {
                        newFiles << config->EUROPATH+"\\"+l[1];
                    }
                    p.close();
                }
                else if(l[2]=="W3PATH") {
                    QFile p(config->W3PATH+"\\"+l[1]);
                    if (p.exists()) {
                        emit sendInfo("Backing up "+config->W3PATH+"\\"+l[1]);
                        QFile b(config->APPDATA+"\\W3PATH\\"+l[1]);
                        if (b.exists()) b.remove();
                        b.close();
                        if (!p.copy(config->APPDATA+"\\W3PATH\\"+l[1])) {
                            emit sendInfo("Could not backup file. "+p.errorString());
                            isAbort=true;
                            return false;
                        }
                        backedW3FilesFROM << config->W3PATH+"\\"+l[1];
                        backedW3FilesTO << config->APPDATA+"\\W3PATH\\"+l[1];
                    }
                    else {
                        newFiles << config->W3PATH+"\\"+l[1];
                    }
                    p.close();
                }
            }
        }
    }
    else {
        emit sendInfo("Could not open file data\\move.txt");
        isAbort=true;
        return false;
    }
    inputFile.close();
    emit sendInfo("Finished backing up files");
    return true;
}

/*
 * Copies the patch mpq to AppData before inserting the ICON_SMALL so it can be reverted to normal
 */
bool Install::bupdateMPQ(){
    emit sendInfo("Backing up MPQ");

    QDir().mkpath(config->APPDATA+"\\MPQ");

    QFile p(config->W3PATH+"\\War3Patch.mpq");

    if (!p.exists()) {
        emit sendInfo("War3Patch.mpq does not exist");
        isAbort=true;
        return false;
    }

    QFile f(config->APPDATA+"\\MPQ\\War3Patch.mpq");
    if (f.exists()) f.remove();

    if (!p.copy(config->APPDATA+"\\MPQ\\War3Patch.mpq")){
        emit sendInfo("Could not copy the file: "+p.errorString());
        emit sendInfo("TRY TO MOVE YOUR W3 FOLDER OUTSIDE PROGRAM FILES (DOCUMENTS, DESKTOP OR SIMILAR)");
        isAbort=true;
        return false;
    }
    p.close();

    return true;
}
