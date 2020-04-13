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

#ifndef INSTALL_H
#define INSTALL_H

#include <QObject>
#include "Windows.h"
#include "config.h"
#include "QProcess"
#include "bnftp.h"

class Install : public QObject
{
    Q_OBJECT    
signals:
    void sendInfo(QString info);
    void setValue(int val);
    void finished(bool a);
    void startDl(QString cmd);
public slots:
    void startInstall();
    void abortInstall();
private:
    bool updateW3();
    bool updateMPQ(QString w3path);
    bool extractFiles();
    bool updateGateways();
    bool finish();
    bool bnftp();
    bool bnupdate();

    bool rupdateW3();
    bool rupdateMPQ();
    bool rextractFiles();
    bool rupdateGateways();
    bool rfinish();

    bool bextractFiles();
    bool bupdateMPQ();
    wchar_t * gateBuffer;
    QString old_installpath;
    ULONG gateSize;
    bool gateBackupFailed;

    QStringList backedEuroFilesFROM;
    QStringList backedEuroFilesTO;
    QStringList backedW3FilesFROM;
    QStringList backedW3FilesTO;
    QStringList newFiles;

    bool w3wasupdated;

    bool desktopShortcutExisted;
    bool roamingExisted;
    bool progFilesExisted;

public:
    Config * config;
    Install();
    ~Install();
    bool isAbort;
};

#endif // WORKERTHREAD_H
