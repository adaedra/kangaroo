#include <Windows.h>
#include <include/cef_app.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, INT) {
    CefMainArgs args { hInstance };
    CefEnableHighDPISupport();

    int ret { CefExecuteProcess(args, nullptr, nullptr) };
    if (ret >= 0) {
        return ret;
    }

    return 0;
}
