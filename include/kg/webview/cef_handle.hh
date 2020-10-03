#pragma once
#include "kg_webview_export.hh"

namespace kg {
    class cef_handle {
    public:
        KG_WEBVIEW_EXPORT cef_handle();
        KG_WEBVIEW_EXPORT ~cef_handle();

    private:
        static unsigned int _ref_count;

        static void cef_init();
        static void cef_fini();
    };
}
