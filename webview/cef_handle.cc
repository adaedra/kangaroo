#include "kg/webview/cef_handle.hh"
#include <include/cef_app.h>
#include <filesystem>

unsigned int kg::cef_handle::_ref_count = 0;

kg::cef_handle::cef_handle() {
    if (kg::cef_handle::_ref_count == 0) {
        cef_init();
    }

    ++kg::cef_handle::_ref_count;
}

kg::cef_handle::~cef_handle() {
    --kg::cef_handle::_ref_count;

    if (kg::cef_handle::_ref_count == 0) {
        cef_fini();
    }
}

void kg::cef_handle::cef_init() {
    CefMainArgs args { GetModuleHandle(NULL) };
    CefSettings settings;
    settings.multi_threaded_message_loop = true;

    auto helper = std::filesystem::current_path() / "kg.helper.exe";
    CefString(&settings.browser_subprocess_path) = helper.native();

    if (!CefInitialize(args, settings, nullptr, nullptr)) {
        abort();
    }
}

void kg::cef_handle::cef_fini() { CefShutdown(); }
