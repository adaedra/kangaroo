#include "kg/browser/app.hh"
#include "kg/util/log.hh"
#include "wx/ptr.hh"

#ifdef _WIN32
int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdline, INT mode) {
#else
int main(int argc, char ** argv) {
#endif
    // When the problem of CefShutdown() in app is fixed, simplify this function back.
    wx::ptr<kg::app> app {};
#ifdef _WIN32
    int ret { wxEntry(instance, prevInstance, cmdline, mode) };
#else
    int ret { wxEntry(argc, argv) };
#endif

    delete &*app;
    KG_LOG_TRACE();

    CefShutdown();
    return ret;
}
