#include "kg/webview/webview.hh"

#include "kg/util/log.hh"

#include <include/cef_app.h>

#ifndef _WIN32
#    include <gdk/gdkx.h>
#    include <gtk/gtk.h>
#endif

kg::webview::webview(wxWindow * parent) : _wx { new wx_bridge { *this, parent } }, _cef { new cef_bridge { *this } } {
    _cef->AddRef();

#ifdef _WIN32
    realize();
#endif
}

kg::webview::~webview() {
    _cef->release_browser();
    _cef->Release();
}

void kg::webview::set_size(unsigned int width, unsigned int height) {
    _wx->SetSize(width, height);
}

void kg::webview::resized(unsigned int width, unsigned int height) {
    _cef->resize_control(width, height);
}

void kg::webview::realized() {
    _cef->create_browser();
}

kg::webview::wx_bridge::wx_bridge(webview & parent, wxWindow * wxParent)
  : bridge<webview> { parent }, wxWindow { wxParent, wxID_ANY } {
    SetBackgroundColour(*wxRED);
}

void kg::webview::wx_bridge::OnResize(wxSizeEvent & event) {
    wxSize size { event.GetSize() };
    _parent.resized(size.GetWidth(), size.GetHeight());
}

#ifndef _WIN32
void kg::webview::wx_bridge::GTKHandleRealized() {
    _parent.realized();
}
#endif

bool kg::webview::wx_bridge::ProcessEvent(wxEvent & e) {
    CefDoMessageLoopWork();
    return wxWindow::ProcessEvent(e);
}

wxBEGIN_EVENT_TABLE(kg::webview::wx_bridge, wxControl)
    EVT_SIZE(wx_bridge::OnResize)
wxEND_EVENT_TABLE()

kg::webview::cef_bridge::cef_bridge(webview & parent)
  : bridge<webview> { parent }, CefClient {}, CefLifeSpanHandler {}, _browser { nullptr } {}

void kg::webview::cef_bridge::create_browser() {
    CefWindowInfo window;
    CefBrowserSettings settings;

    wxSize clientRect { _parent._wx->GetSize() };
#ifdef _WIN32
    RECT rect { 0, 0, clientRect.GetWidth(), clientRect.GetHeight() };

    window.SetAsChild(_kg_parent->_wx->GetHWND(), rect);
#else
    CefRect rect { 0, 0, clientRect.GetWidth(), clientRect.GetHeight() };
    unsigned long xid { gdk_x11_drawable_get_xid(_parent._wx->GetHandle()->window) };

    window.SetAsChild(xid, rect);
#endif

    CefBrowserHost::CreateBrowser(window, this, "https://www.google.fr", settings, nullptr, nullptr);
}

kg::webview::cef_bridge::~cef_bridge() {}

void kg::webview::cef_bridge::resize_control(unsigned int width, unsigned int height) {
    if (!_browser) {
        return;
    }

#ifdef _WIN32
    SetWindowPos(_browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, SWP_NOZORDER);
#else
    unsigned int xid { gdk_x11_drawable_get_xid(gtk_widget_get_window(_parent._wx->GetHandle())) };

    XResizeWindow(
        GDK_WINDOW_XDISPLAY(_parent._wx->GetHandle()->window), _browser->GetHost()->GetWindowHandle(), width, height);
#endif
    // CefDoMessageLoopWork();
}

CefRefPtr<CefLifeSpanHandler> kg::webview::cef_bridge::GetLifeSpanHandler() {
    return this;
}

void kg::webview::cef_bridge::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    _browser = browser;

    wxSize clientRect { _parent._wx->GetSize() };
    resize_control(clientRect.GetWidth(), clientRect.GetHeight());
}

void kg::webview::cef_bridge::OnBeforeClose(CefRefPtr<CefBrowser>) {
    _browser = nullptr;
}

void kg::webview::cef_bridge::release_browser() {
    if (_browser) {
        _browser->GetHost()->CloseBrowser(true);
    }

    _browser = nullptr;
}
