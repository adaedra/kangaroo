#include <include/cef_app.h>
#ifdef _WIN32
#include <Windows.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, INT) {
    CefMainArgs args { hInstance };
    CefEnableHighDPISupport();
#else
int main(int argc, char ** argv) {
    CefMainArgs args { argc, argv };
#endif

    int ret { CefExecuteProcess(args, nullptr, nullptr) };
    if (ret >= 0) {
        return ret;
    }

    return 0;
}
