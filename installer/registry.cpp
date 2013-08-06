#include "registry.h"
#ifndef _SSTREAM_
    #include <sstream>
#endif

Registry::Registry() {}

wstring Registry :: getInstallPath() {
    CRegKey reg;
    wstring s;
    if (reg.Open(HKEY_CURRENT_USER, _T("Software\\Blizzard Entertainment\\Warcraft III"), KEY_READ | KEY_WOW64_64KEY)==ERROR_SUCCESS) {
        s=this->getRegString(reg, _T("InstallPath"));
        reg.Close();
        return s;
    }
    else return _T("");
}

wstring Registry :: DWORD2STR(DWORD d) {
   std::wostringstream stream;
   stream << d;
   wstring str = stream.str();
   return str;
}

wstring Registry :: getRegString(CRegKey reg, wstring name) {
    LPTSTR szBuffer = new TCHAR[1024];
    ULONG bufsize=1024;
    DWORD s = reg.QueryStringValue(name.c_str(), szBuffer, &bufsize);
    if (s == ERROR_SUCCESS) {
        reg.QueryStringValue(name.c_str(), szBuffer, &bufsize);
        wstring s( szBuffer );
        return s;
    }
    else if (s == ERROR_INVALID_DATA) {
        //cout << "invalid data";
        return _T("");
    }
    else if (s == ERROR_MORE_DATA) {
        //cout << "more data";
        return _T("");
    }
    else {
        /*DWORD lastError = GetLastError();
        std::cout << "General failure. GetLastError returned " << std::hex << lastError << ".";
        cout << "general fail";*/
        return _T("");
    }
}

DWORD Registry :: getRegDWORD(CRegKey reg, wstring name) {
    DWORD buf;
    DWORD s = reg.QueryDWORDValue(name.c_str(), buf);
    if (s == ERROR_SUCCESS) {
        reg.QueryDWORDValue(name.c_str(), buf);
        return buf;
    }
    else if (s == ERROR_INVALID_DATA) {
        return -1;
    }
    else {
        return -1;
    }
}

bool Registry :: setRegString(CRegKey reg, wstring name, wstring value) {
    DWORD s = reg.SetStringValue(name.c_str(), value.c_str());
    if (s==ERROR_SUCCESS) {
        return true;
    }
    else {
        return false;
    }
}
