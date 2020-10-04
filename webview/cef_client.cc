#include "kg/webview/cef_client.hh"

#include "kg/util/log.hh"

kg::cef_client::cef_client(webview * parent)
  : CefClient {}, CefLifeSpanHandler {}, _parent { parent }, _browser { nullptr } {}

kg::cef_client::~cef_client() {
    kg::log::debug() << "~cef_client";
    kg::log::debug() << "Browser is " << (_browser ? "active" : "inactive");
}

CefRefPtr<CefLifeSpanHandler> kg::cef_client::GetLifeSpanHandler() {
    return this;
}

void kg::cef_client::OnAfterCreated(CefRefPtr<CefBrowser> browser) {
    _browser = browser;
    kg::log::debug() << "Browser is ready.";
}

void kg::cef_client::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
    kg::log::debug() << "OnBeforeClose";
    _browser = nullptr;
}

HWND kg::cef_client::handle() const {
    if (!_browser) {
        return nullptr;
    }

    return _browser->GetHost()->GetWindowHandle();
}

void kg::cef_client::will_close() {
    _parent = nullptr;
}

void kg::cef_client::load_url(std::string const & url) {
    _browser->GetMainFrame()->LoadURL(url);
}
