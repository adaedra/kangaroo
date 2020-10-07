#pragma once
#include "kg_webview_export.hh"

#include <include/cef_client.h>
#include <wx/_wrapper.hh>

namespace kg {
    class WebView : public wxWindow {
    public:
        KG_WEBVIEW_EXPORT WebView(wxWindow * parent);
        KG_WEBVIEW_EXPORT virtual ~WebView();

#ifndef _WIN32
        virtual void GTKHandleRealized() override;
#endif

        wxDECLARE_EVENT_TABLE();

    protected:
        virtual bool TryBefore(wxEvent &) override;

    private:
        void CreateBrowser();
        void OnSize(wxSizeEvent &);
        void OnDestroy(wxWindowDestroyEvent &);

        class CefBridge;

        CefRefPtr<CefBridge> _cef;
    };
}
