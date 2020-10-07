#pragma once
#include "kg/util/bridge.hh"
#include "kg_webview_export.hh"

#include <include/cef_client.h>
#include <wx/_wrapper.hh>

namespace kg {
    class webview {
    public:
        KG_WEBVIEW_EXPORT webview(wxWindow * parent);
        KG_WEBVIEW_EXPORT ~webview();

        KG_WEBVIEW_EXPORT void set_size(unsigned int width, unsigned int height);

    private:
        void resized(unsigned int, unsigned int);

        class wx_bridge : public bridge<webview>, public wxWindow {
        public:
            wx_bridge(webview &, wxWindow *);

            void OnResize(wxSizeEvent &);

            wxDECLARE_EVENT_TABLE();
        };

        friend class wx_bridge;
        wx_bridge * _wx;

        class cef_bridge : public bridge<webview>, public CefClient, public CefLifeSpanHandler {
        public:
            cef_bridge(webview &);
            ~cef_bridge();

            void resize_control(unsigned int width, unsigned int height);

            virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
            virtual void OnAfterCreated(CefRefPtr<CefBrowser>) override;
            virtual void OnBeforeClose(CefRefPtr<CefBrowser>) override;

            IMPLEMENT_REFCOUNTING(cef_bridge);

        private:
            CefRefPtr<CefBrowser> _browser;
        };

        friend class cef_bridge;
        cef_bridge * _cef;
    };
}
