#include "kg/util/log.hh"

#include <Windows.h>

kg::log::~log() {
    _stream << "\r\n";
    std::string s = _stream.str();

    wchar_t * buf = new wchar_t[s.length() + 1] { 0 };
    mbstowcs_s(nullptr, buf, s.length(), s.c_str(), _TRUNCATE);

    OutputDebugStringW(buf);
    delete[] buf;
}
