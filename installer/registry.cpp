#include "registry.h"
#include "util.h"

Registry::Registry() {}

QString Registry :: getInstallPath() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=this->getRegString(&reg, "InstallPath");
        reg.Close();
        return s;
    }
    else return "";
}

QString Registry :: getW3dir() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=this->getRegString(&reg, "w3dir");
        reg.Close();
        return s;
    }
    else return Util::getLastErrorMsg();
}

QString Registry :: getEuroPath() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        QString s=this->getRegString(&reg, "europath");
        reg.Close();
        return s;
    }
    else return Util::getLastErrorMsg();
}

QString Registry :: getRegString(CRegKey * reg, QString name) {
    LPTSTR szBuffer = new TCHAR[1024];
    ULONG bufsize=1024;
    wchar_t w[MAX_PATH];
    name.toWCharArray(w);

    DWORD s = reg->QueryStringValue(w, szBuffer, &bufsize);
    if (s == ERROR_SUCCESS) {
        QString s=QString::fromWCharArray(w);
        delete[] szBuffer;
        return s;
    }
    else {
        return "";
    }
}

DWORD Registry :: getRegDWORD(CRegKey reg, QString name) {
    DWORD buf;
    wchar_t w[MAX_PATH];
    name.toWCharArray(w);
    DWORD s = reg.QueryDWORDValue(w, buf);
    if (s == ERROR_SUCCESS) {
        return buf;
    }
    else {
        return -1;
    }
}

bool Registry :: setRegString(CRegKey reg, QString name, QString value) {
    std::wstring w1=name.toStdWString();
    std::wstring w2=value.toStdWString();
    DWORD s = reg.SetStringValue(w1.c_str(), w2.c_str(), REG_SZ);
    if (s==ERROR_SUCCESS) {
        return true;
    }
    else {
        return false;
    }
}

DWORD Registry :: setGateways() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS){
        wchar_t *lines[20]= {
            _T("1008"),
            _T("05"),
            _T("uswest.battle.net"),
            _T("8"),
            _T("Lordaeron (U.S. West)"),
            _T("useast.battle.net"),
            _T("6"),
            _T("Azeroth (U.S. East)"),
            _T("asia.battle.net"),
            _T("-9"),
            _T("Kalimdor (Asia)"),
            _T("europe.battle.net"),
            _T("-1"),
            _T("Northrend (Europe)"),
            _T("server.eurobattle.net"),
            _T("8"),
            _T("Eurobattle.net"),
            _T("localhost"),
            _T("8"),
            _T("Eurobattle.net GProxy")
        };
        size_t totalSize=0;
        for (int i=0; i<20; i++) {
            totalSize+=(wcslen(lines[i])+1)*sizeof(wchar_t);
        }
        totalSize+=1*sizeof(wchar_t);

        LPBYTE pString;
        pString = static_cast<LPBYTE>(malloc(totalSize));

        size_t offset=0;
        for (int i=0; i<20; i++) {
            size_t len=(wcslen(lines[i])+1)*sizeof(wchar_t);
            memcpy(pString+offset, lines[i], len);
            offset+=len;
        }
        pString[offset+1] = 0;

        DWORD r = RegSetValueEx(reg, _T("Battle.net Gateways"), 0, REG_MULTI_SZ, pString, totalSize);

        reg.Close();
        delete pString;

        return r;
    }
    else {
        return GetLastError();
    }
    return GetLastError();
}
