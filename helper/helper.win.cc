#include <Windows.h>
#include <include/cef_app.h>

int mainImpl(CefMainArgs & args);

int wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, INT) {
    CefMainArgs args { hInstance };
    CefEnableHighDPISupport();

    return mainImpl(args);
}
