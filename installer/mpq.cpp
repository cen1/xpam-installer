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

#include "mpq.h"
#include "StormLib.h"
#include "QMessageBox"
#include "iostream"
#include "fstream"

QString getLastErrorMsg() {
    LPWSTR bufPtr = NULL;
    DWORD err = GetLastError();
    FormatMessageW(FORMAT_MESSAGE_ALLOCATE_BUFFER |
                   FORMAT_MESSAGE_FROM_SYSTEM |
                   FORMAT_MESSAGE_IGNORE_INSERTS,
                   NULL, err, 0, (LPWSTR)&bufPtr, 0, NULL);
    const QString result =
        (bufPtr) ? QString::fromUtf16((const ushort*)bufPtr).trimmed() :
                   QString("Unknown Error %1").arg(err);
    LocalFree(bufPtr);
    return result;
}

Mpq::Mpq(){

}

int Mpq::open(QString file){
    QByteArray ba = file.toLocal8Bit();
    const char *c_str = ba.data();
    return SFileOpenArchive(c_str, 0, 0, &(this->hMpq));
}

bool Mpq::flush(){
    return SFileFlushArchive(this->hMpq);
}

bool Mpq::close() {
    //close file handles first
    SFileCloseFile(this->hOpenFile);

    return SFileCloseArchive(this->hMpq);
}

bool Mpq::openFile(QString filename) {
    QByteArray ba = filename.toLocal8Bit();
    const char *c_str = ba.data();

    return SFileOpenFileEx(this->hMpq, c_str, 0, &(this->hOpenFile));
}

DWORD Mpq::getFileSize() {
    return SFileGetFileSize(this->hOpenFile, NULL);
}

bool Mpq::readFile(char * buffer) {
    char  szBuffer[0x10000];
    DWORD dwBytes = 1;

    while(dwBytes > 0)
    {
        if (!SFileReadFile(this->hOpenFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL)) return false;
        if(dwBytes > 0)
            strcat(buffer, szBuffer);
    }
    return true;
}

QString Mpq::readFileToString() {
    char  szBuffer[1];
    DWORD dwBytes = 1;
    QString content = "";
    std::ofstream out;
    out.open("stderr.txt");
    DWORD bread=0;
    while(dwBytes > 0)
    {
        SFileReadFile(this->hOpenFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
        if(dwBytes > 0) {
            bread+=dwBytes;
            content = content+QString::fromLocal8Bit(szBuffer, 1);
        }
    }
    out << bread;
    return content;
}

bool Mpq::closeFile() {
    return SFileCloseFile(this->hOpenFile);
}

QString Mpq::getFileName() {
    char buffer[255];
    if (SFileGetFileName(this->hOpenFile, buffer)) {
        return QString::fromLocal8Bit(buffer);
    }
    else return "";
}

bool Mpq::createFileFromLocal(QString name, DWORD filesize) {
    QByteArray ba = name.toLocal8Bit();
    const char *c_str = ba.data();

    return SFileCreateFile(this->hMpq, c_str, 0, filesize, SFileGetLocale(), MPQ_FILE_COMPRESS, &(this->hOpenFile));
}

bool Mpq::createFileFromMpq(Mpq * mpq) {
    QByteArray ba = mpq->getFileName().toLocal8Bit();
    const char *c_str = ba.data();

    return SFileCreateFile(this->hMpq, c_str, 0, mpq->getFileSize(), SFileGetLocale(), NULL, &(this->hOpenFile));
}

bool  Mpq::writeFile(void * data, DWORD size) {
    return SFileWriteFile(this->hOpenFile, &data, size, MPQ_FILE_COMPRESS);
}

bool Mpq::finishWriteFile() {
    return SFileFinishFile(this->hOpenFile);
}





