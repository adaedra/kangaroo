#include "kg/browser/app.hh"

CefMainArgs kg::App::GetCefMainArgs() {
    return CefMainArgs { GetModuleHandleW(nullptr) };
}

void CefPreInit() {
    CefEnableHighDPISupport();
}
