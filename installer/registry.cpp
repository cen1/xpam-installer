#include "registry.h"
#include "util.h"
#include "winutils.h"

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
    wchar_t * szBuffer = new wchar_t[MAX_PATH];
    ULONG bufsize=MAX_PATH;
    std::wstring w=name.toStdWString();

    DWORD s = reg->QueryStringValue(w.c_str(), szBuffer, &bufsize);
    if (s == ERROR_SUCCESS) {
        QString s=QString::fromWCharArray(szBuffer);
        delete[] szBuffer;
        return s;
    }
    else {
        return "";
    }
}

bool Registry :: getRegMultiString(CRegKey * reg, QString name, wchar_t * buffer, ULONG * bufsize) {
    std::wstring w=name.toStdWString();

    DWORD s = reg->QueryMultiStringValue(w.c_str(), buffer, bufsize);
    if (s == ERROR_SUCCESS) {
        return true;
    }
    else {
        return false;
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

bool Registry :: setRegDWORD(CRegKey reg, QString name, DWORD value) {
    std::wstring w=name.toStdWString();
    DWORD s = reg.SetDWORDValue(w.c_str(), value);
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
        wchar_t lines[21][255]= {
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
            _T("-1"),
            _T("Eurobattle.net"),
            _T("localhost"),
            _T("-1"),
            _T("Eurobattle.net GProxy"),
            _T("")
        };
        size_t totalSize=0;
        for (int i=0; i<21; i++) {
            totalSize+=(wcslen(lines[i])+1)*sizeof(wchar_t);
        }

        LPBYTE pString;
        pString = static_cast<LPBYTE>(malloc(totalSize));

        size_t offset=0;
        for (int i=0; i<21; i++) {
            size_t len=(wcslen(lines[i])+1)*sizeof(wchar_t);
            memcpy(pString+offset, lines[i], len);
            offset+=len;
        }

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

DWORD Registry :: setBnetGateways() {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS){
        wchar_t lines[15][255]= {
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
            _T("")
        };
        size_t totalSize=0;
        for (int i=0; i<15; i++) {
            totalSize+=(wcslen(lines[i])+1)*sizeof(wchar_t);
        }

        LPBYTE pString;
        pString = static_cast<LPBYTE>(malloc(totalSize));

        size_t offset=0;
        for (int i=0; i<15; i++) {
            size_t len=(wcslen(lines[i])+1)*sizeof(wchar_t);
            memcpy(pString+offset, lines[i], len);
            offset+=len;
        }

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

DWORD Registry :: setOriginalGateways(wchar_t * buffer, ULONG bufsize) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS){
        LPBYTE pString;
        pString = reinterpret_cast<LPBYTE>(buffer);

        DWORD r = RegSetValueEx(reg, _T("Battle.net Gateways"), 0, REG_MULTI_SZ, pString, bufsize);

        reg.Close();
        delete pString;

        return r;
    }
    else {
        return GetLastError();
    }
    return GetLastError();
}

bool Registry::createEuroKey() {
    CRegKey reg;
    if(reg.Create(HKEY_CURRENT_USER,  _T("Software\\Eurobattle.net"), REG_NONE, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY, NULL, NULL)==ERROR_SUCCESS) {
        reg.Close();
        return true;
    }
    else {
        reg.Close();
        return false;
    }
}

bool Registry::createW3Key() {
    CRegKey reg;
    if(reg.Create(HKEY_CURRENT_USER,  _T("Software\\Blizzard Entertainment\\Warcraft III"), REG_NONE, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY, NULL, NULL)==ERROR_SUCCESS) {
        reg.Close();
        return true;
    }
    else {
        reg.Close();
        return false;
    }
}

bool Registry::setEuropath(QString europath) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "europath", europath);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setW3dir(QString w3dir) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "w3dir", w3dir);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setInstallPath(QString w3dir) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegString(reg, "InstallPath", w3dir);
        reg.Close();
        return r;
    }
    return false;
}

bool Registry::setPatchVersion(int version) {
    CRegKey reg;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        bool r = this->setRegDWORD(reg, "patch", (DWORD)version);
        reg.Close();
        return r;
    }
    return false;
}

DWORD Registry::addInstallationEntries(Config * config) {
    CRegKey reg;
    DWORD ret;

    if (Winutils::IsWow64()) {
        ret = reg.Create(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), REG_NONE, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY, NULL, NULL);
        if (ret!=ERROR_SUCCESS) return 1;
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "DisplayName", "Eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "UninstallString", "\""+config->EUROPATH+"\\uninstaller.exe\"");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "InstallLocation", config->EUROPATH);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "DisplayIcon ", config->EUROPATH+"\\xpam.exe");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "Publisher", "Eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "HelpLink", "http://eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "NoModify", 1);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "NoRepair", 1);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "EstimatedSize", 15360);
        reg.Close();
    }
    else {
        ret = reg.Create(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), REG_NONE, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY, NULL, NULL);
        if (ret!=ERROR_SUCCESS) return 1;
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "DisplayName", "Eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "UninstallString", "\""+config->EUROPATH+"\\uninstaller.exe\"");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "InstallLocation", config->EUROPATH);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "DisplayIcon ", config->EUROPATH+"\\xpam.exe");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "Publisher", "Eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegString(reg, "HelpLink", "http://eurobattle.net");
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "NoModify", 1);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "NoRepair", 1);
        reg.Close();

        reg.Open(HKEY_LOCAL_MACHINE,  _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\Eurobattle.net"), KEY_WRITE | KEY_WOW64_64KEY);
        this->setRegDWORD(reg, "EstimatedSize", 15360);
        reg.Close();
    }

    return 0;
}

bool Registry::removeInstallationEntries() {
    CRegKey reg;

    if (Winutils::IsWow64()) {
        if (reg.Open(HKEY_LOCAL_MACHINE, _T("Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_ALL_ACCESS | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
            DWORD ret = reg.RecurseDeleteKey(_T("Eurobattle.net"));
            reg.Close();
            if (ret==ERROR_SUCCESS) return true;
            else return false;

        }
        return false;
    }
    else {
        if (reg.Open(HKEY_LOCAL_MACHINE, _T("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall"), KEY_ALL_ACCESS | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
            DWORD ret = reg.RecurseDeleteKey(_T("Eurobattle.net"));
            reg.Close();
            if (ret==ERROR_SUCCESS) return true;
            else return false;

        }
        return false;
    }
}
