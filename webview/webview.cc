#include "kg/webview/webview.hh"

#include "kg/util/log.hh"

#include <include/cef_app.h>

#ifndef _WIN32
#    include <gdk/gdkx.h>
#    include <gtk/gtk.h>
#endif

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
#ifdef _WIN32
    CreateBrowser();
#endif
}

kg::WebView::~WebView() {
    KG_LOG_TRACE() << " " << KG_LOG_VAR(_cef);
}

wxBEGIN_EVENT_TABLE(kg::WebView, wxWindow)
    EVT_SIZE(kg::WebView::OnSize)
    EVT_WINDOW_DESTROY(kg::WebView::OnDestroy)
wxEND_EVENT_TABLE()

#ifndef _WIN32
void kg::WebView::GTKHandleRealized() {
    CreateBrowser();
}
#endif

#ifdef _WIN32
static void prepareWindow(kg::WebView * webview, CefWindowInfo & window) {
    wxSize size { webview->GetSize() };
    RECT rect { 0, 0, size.GetWidth(), size.GetHeight() };

    window.SetAsChild(webview->GetHWND(), rect);
}
#else
static void prepareWindow(kg::WebView * webview, CefWindowInfo & window) {
    Window xid { gdk_x11_drawable_get_xid(webview->GetHandle()->window) };
    wxSize size { webview->GetSize() };
    CefRect rect { 0, 0, size.GetWidth(), size.GetHeight() };

    window.SetAsChild(xid, rect);
}
#endif

bool kg::WebView::TryBefore(wxEvent &) {
    CefDoMessageLoopWork();
    return false;
}

void kg::WebView::CreateBrowser() {
    CefWindowInfo window;
    CefBrowserSettings settings;

    prepareWindow(this, window);
    _cef = new CefBridge {};

    CefBrowserHost::CreateBrowser(window, _cef, "https://www.google.com", settings, nullptr, nullptr);
}

#ifdef _WIN32
static void resizeBrowser(kg::WebView *, CefRefPtr<CefBrowser> browser, unsigned int width, unsigned int height) {
    SetWindowPos(browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, SWP_NOZORDER);
}
#else
static void
resizeBrowser(kg::WebView * webview, CefRefPtr<CefBrowser> browser, unsigned int width, unsigned int height) {
    Window xid { browser->GetHost()->GetWindowHandle() };
    Display * display { gdk_x11_drawable_get_xdisplay(webview->GetHandle()->window) };

    XResizeWindow(display, xid, width, height);
}
#endif

void kg::WebView::OnSize(wxSizeEvent & event) {
    if (_cef && _cef->_browser) {
        resizeBrowser(this, _cef->_browser, event.GetSize().GetWidth(), event.GetSize().GetHeight());
    }
}

void kg::WebView::OnDestroy(wxWindowDestroyEvent &) {
    KG_LOG_TRACE();

    if (_cef && _cef->_browser) {
        _cef->_browser->GetHost()->CloseBrowser(true);
    }

    _cef = nullptr;
}
