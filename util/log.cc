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

kg::log kg::log::debug() {
    return kg::log { "DEBUG" };
}

kg::log kg::log::info() {
    return kg::log { " INFO" };
}

kg::log kg::log::warning() {
    return kg::log { " WARN" };
}

kg::log kg::log::error() {
    return kg::log { "ERROR" };
}

kg::log::log(std::string const & level) : _stream {} {
    _stream << "[" << level << "] ";
}
