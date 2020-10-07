#include "kg/webview/webview.hh"

#include "kg/util/log.hh"

#include <include/cef_app.h>

kg::webview::webview(wxWindow * parent) : _wx { new wx_bridge { *this, parent } }, _cef { new cef_bridge { *this } } {
    _cef->AddRef();
}

kg::webview::~webview() {
    KG_LOG_TRACE();
    _cef->Release();
}

void kg::webview::set_size(unsigned int width, unsigned int height) {
    _wx->SetSize(width, height);
}

void kg::webview::resized(unsigned int width, unsigned int height) {
    _cef->resize_control(width, height);
}

kg::webview::wx_bridge::wx_bridge(webview & parent, wxWindow * wxParent)
  : bridge<webview> { parent }, wxWindow { wxParent, wxID_ANY } {
    SetBackgroundColour(*wxRED);
}

void kg::webview::wx_bridge::OnResize(wxSizeEvent & event) {
    wxSize size { event.GetSize() };
    _parent.resized(size.GetWidth(), size.GetHeight());
}

wxBEGIN_EVENT_TABLE(kg::webview::wx_bridge, wxControl)
    EVT_SIZE(wx_bridge::OnResize)
wxEND_EVENT_TABLE()

kg::webview::cef_bridge::cef_bridge(webview & parent)
  : bridge<webview> { parent }, CefClient {}, CefLifeSpanHandler {}, _browser { nullptr } {
    CefWindowInfo window;
    CefBrowserSettings settings;

    wxSize clientRect { _parent._wx->GetSize() };
#ifdef _WIN32
    RECT rect { 0, 0, clientRect.GetWidth(), clientRect.GetHeight() };

    window.SetAsChild(_kg_parent->_wx->GetHWND(), rect);
#endif
    CefBrowserHost::CreateBrowser(window, this, "https://www.google.fr", settings, nullptr, nullptr);
}

kg::webview::cef_bridge::~cef_bridge() {
    KG_LOG_TRACE();
}

void kg::webview::cef_bridge::resize_control(unsigned int width, unsigned int height) {
    if (!_browser) {
        return;
    }

#ifdef _WIN32
    SetWindowPos(_browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, SWP_NOZORDER);
#endif
    CefDoMessageLoopWork();
}

CefRefPtr<CefLifeSpanHandler> kg::webview::cef_bridge::GetLifeSpanHandler() {
    return this;
}

void kg::webview::cef_bridge::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    _browser = browser;

    wxSize clientRect { _parent._wx->GetSize() };
    KG_LOG_TRACE() << " size = (" << clientRect.GetWidth() << ", " << clientRect.GetHeight() << ")";
    resize_control(clientRect.GetWidth(), clientRect.GetHeight());
}

void kg::webview::cef_bridge::OnBeforeClose(CefRefPtr<CefBrowser>) {
    KG_LOG_TRACE();

    _browser = nullptr;
}
