#include <include/cef_app.h>

int mainImpl(CefMainArgs & args) {
    int ret { CefExecuteProcess(args, nullptr, nullptr) };
    if (ret >= 0) {
        return ret;
    }

    return 0;
}
