#include <Windows.h>
#include <include/capi/cef_app_capi.h>

int wWinMain(HINSTANCE hInstance, HINSTANCE, LPWSTR, INT) {
    cef_main_args_t args { hInstance };
    int ret { cef_execute_process(&args, nullptr, nullptr) };

    if (ret == -1) {
        abort();
    }

    return 0;
}
