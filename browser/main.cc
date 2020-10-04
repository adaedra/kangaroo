#include "kg/browser/app.hh"
#include "kg/util/log.hh"
#include "wx/ptr.hh"

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdline, INT mode) {
    // When the problem of CefShutdown() in app is fixed, simplify this function back.
    wx::ptr<kg::app> app {};
    int ret = wxEntry(instance, prevInstance, cmdline, mode);

    delete &*app;
    KG_LOG_TRACE();

    CefShutdown();
    return ret;
}
