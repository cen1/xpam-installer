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

#pragma warning(disable: 4995)
#include "winutils.h"
#ifndef WINDOWS_H
    #include <windows.h>
#endif
#ifndef _SHLOBJ_H_
    #include "Shlobj.h"
#endif
#ifndef __ATLBASE_H__
    #include <atlbase.h>
#endif
#include <atlstr.h>
#include <strsafe.h>

Winutils::Winutils()
{
}

QString Winutils :: getProgramFiles()
{
    TCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILESX86, NULL, 0, szPath)))
    {
        return QString::fromWCharArray(szPath);
    }
    else
    {
        return "";
    }
}

QString Winutils::getFileVersion(QString filename)
{
    DWORD  verHandle = NULL;
    UINT   size      = 0;
    LPBYTE lpBuffer  = NULL;
    TCHAR t[MAX_PATH];
    filename.toWCharArray(t);
    DWORD  verSize   = GetFileVersionInfoSize( t, &verHandle);

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfo( t, verHandle, verSize, verData))
        {
            if (VerQueryValue(verData, _T("\\"), (VOID FAR* FAR*)&lpBuffer,&size))
            {
                if (size)
                {
                    VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)lpBuffer;
                    if (verInfo->dwSignature == 0xfeef04bd)
                    {
                        int major = HIWORD(verInfo->dwFileVersionMS);
                        int minor = LOWORD(verInfo->dwFileVersionMS);
                        int revision = HIWORD(verInfo->dwProductVersionLS);
                        int build = verInfo->dwFileVersionLS;
                        TCHAR buffer[255];
                        wsprintf(buffer, _T("%d.%d.%d.%d"), major, minor, revision, build);
                        delete[] verData;
                        return QString::fromWCharArray(buffer);
                    }
                    else {
                        return "-5";
                    }
                }
                else {
                    return "-4";
                }
            }
            else {
                return "-3";
            }
        }
        else {
            delete[] verData;
            return "-2";
        }
    }
    else {
        return "-1";
    }
}


QString Winutils::getFileLang(QString filename)
{
    DWORD  verHandle = NULL;
    UINT   size      = 0;
    //LPBYTE lpBuffer  = NULL;
    TCHAR t[MAX_PATH];
    filename.toWCharArray(t);

    DWORD  verSize   = GetFileVersionInfoSize( t, &verHandle);

    struct LANGANDCODEPAGE {
      WORD wLanguage;
      WORD wCodePage;
    } *lpTranslate;

    if (verSize != NULL)
    {
        LPSTR verData = new char[verSize];

        if (GetFileVersionInfo( t, verHandle, verSize, verData))
        {
            if (VerQueryValue(verData, _T("\\VarFileInfo\\Translation"), (LPVOID*)&lpTranslate, &size))
            {
                if (size)
                {
                    TCHAR c[255];
                    wsprintf(c, _T("%d"), lpTranslate[0].wLanguage);
                    delete[] verData;
                    return QString::fromWCharArray(c);
                }
                else {
                    return "";
                }
            }
            else {
                return "";
            }
        }
        else {
            delete[] verData;
            return "";
        }
    }
    else {
        return "";
    }
}






