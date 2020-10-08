#include "kg/browser/app.hh"

CefMainArgs kg::App::GetCefMainArgs() {
    return CefMainArgs { argc, argv };
}

void CefPreInit() {}
