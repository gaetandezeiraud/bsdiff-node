#include "Util.hpp"

#include <Windows.h>

namespace bsdpNode {
#ifdef WIN32
  std::string Utf8ToAnsi(const std::string& utf8str)
  {
    int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), strlen(utf8str.c_str()), NULL, 0);
    wchar_t* wszString = new wchar_t[wcsLen + 1];
    ::MultiByteToWideChar(CP_UTF8, NULL, utf8str.c_str(), strlen(utf8str.c_str()), wszString, wcsLen);
    wszString[wcsLen] = '\0';

    int ansiLen = ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcsLen, NULL, 0, NULL, NULL);
    char* ansiString = new char[ansiLen + 1];
    ::WideCharToMultiByte(CP_ACP, NULL, wszString, wcsLen, ansiString, ansiLen, NULL, NULL);
    ansiString[ansiLen] = '\0';

    std::string result = ansiString;

    delete[] wszString;
    delete[] ansiString;

    return result;
  }
#endif
}