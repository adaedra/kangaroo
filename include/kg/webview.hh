#pragma once
#include "kg_webview_export.hh"
#include "kg/webview/cef_handle.hh"

#include <wx/_wrapper.hh>

namespace kg {
    class webview : public wxControl {
    public:
        KG_WEBVIEW_EXPORT webview(wxWindow * parent);
        KG_WEBVIEW_EXPORT ~webview();

    private:
        void on_resize(wxSizeEvent &);
        
        cef_handle _cef;
        
        wxDECLARE_EVENT_TABLE();
    };
}
