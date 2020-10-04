#pragma once
#include "kg_webview_export.hh"

#include <include/cef_client.h>

namespace kg {
    class webview;

    class cef_client : public CefClient, public CefLifeSpanHandler {
    public:
        KG_WEBVIEW_EXPORT cef_client(webview * _parent);
        KG_WEBVIEW_EXPORT virtual ~cef_client();

        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

        virtual void OnAfterCreated(CefRefPtr<CefBrowser>) override;
        virtual void OnBeforeClose(CefRefPtr<CefBrowser>) override;

        HWND handle() const;

        void will_close();
        void load_url(std::string const & url);

        CefRefPtr<CefBrowser> _browser;

    private:
        webview * _parent;

        IMPLEMENT_REFCOUNTING(kg::cef_client);
    };
}
