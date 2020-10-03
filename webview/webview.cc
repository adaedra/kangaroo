#include "kg/webview.hh"

#include <include/cef_app.h>
#include <include/cef_client.h>
#include <filesystem>

kg::webview::webview(wxWindow * parent)
  : wxControl { parent, wxID_ANY }, _cef {} {
    SetBackgroundColour(*wxRED);

    CefBrowserSettings browserSettings;
    CefWindowInfo window;

    window.SetAsChild(GetHWND(), wxGetClientRect(GetHWND()));

    CefBrowserHost::CreateBrowser(
        window, nullptr, "https://www.google.com", browserSettings, nullptr,
        nullptr);
}

kg::webview::~webview() {}

void kg::webview::on_resize(wxSizeEvent & event) {
    event.Skip();
}

wxBEGIN_EVENT_TABLE(kg::webview, wxControl)
    EVT_SIZE(kg::webview::on_resize)
wxEND_EVENT_TABLE()
