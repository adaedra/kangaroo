#include "kg/webview/webview.hh"

#include "kg/util/log.hh"

#include <include/cef_app.h>

class kg::WebView::CefBridge : public CefClient, public CefLifeSpanHandler {
public:
    CefBridge() {}

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        _browser = browser;
    }

    virtual void OnBeforeClose(CefRefPtr<CefBrowser>) override {
        _browser = nullptr;
    }

    CefRefPtr<CefBrowser> _browser;

    IMPLEMENT_REFCOUNTING(CefBridge);
};

kg::WebView::WebView(wxWindow * parent) : wxWindow { parent, wxID_ANY } {
    FinishInit();
}

kg::WebView::~WebView() {
    KG_LOG_TRACE() << " " << KG_LOG_VAR(_cef);
}

wxBEGIN_EVENT_TABLE(kg::WebView, wxWindow)
    EVT_SIZE(kg::WebView::OnSize)
    EVT_WINDOW_DESTROY(kg::WebView::OnDestroy)
wxEND_EVENT_TABLE()

bool kg::WebView::TryBefore(wxEvent &) {
    CefDoMessageLoopWork();
    return false;
}

void kg::WebView::CreateBrowser() {
    CefWindowInfo window;
    CefBrowserSettings settings;

    PrepareWindow(window);
    _cef = new CefBridge {};

    CefBrowserHost::CreateBrowser(window, _cef, "https://www.google.com", settings, nullptr, nullptr);
}

void kg::WebView::OnSize(wxSizeEvent & event) {
    if (_cef && _cef->_browser) {
        ResizeBrowser(_cef->_browser, event.GetSize().GetWidth(), event.GetSize().GetHeight());
    }
}

void kg::WebView::OnDestroy(wxWindowDestroyEvent &) {
    KG_LOG_TRACE();

    if (_cef && _cef->_browser) {
        _cef->_browser->GetHost()->CloseBrowser(true);
    }

    _cef = nullptr;
}
