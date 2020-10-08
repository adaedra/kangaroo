#include "kg/util/log.hh"
#include "kg_features.h"

#include <include/cef_app.h>
#include <include/cef_client.h>

class cef_client : public CefClient, public CefLifeSpanHandler, public CefLoadHandler, public CefDisplayHandler {
public:
    cef_client() : CefClient {}, CefLifeSpanHandler {}, CefDisplayHandler {}, _browser { nullptr } {}
    ~cef_client() {}

    virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override {
        return this;
    }

    virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override {
        return this;
    }

    virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() override {
        return this;
    }

    virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override {
        kg::log::debug() << "OnAfterCreated";
        _browser = browser;
    }

    virtual bool DoClose(CefRefPtr<CefBrowser> browser) override {
        kg::log::debug() << "DoClose";
        CefQuitMessageLoop();

        return false;
    }

    virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override {
        kg::log::debug() << "OnBeforeClose";
        _browser = nullptr;
    }

    virtual void
    OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override {
        kg::log::debug() << "OnLoadingStateChange isLoading = " << isLoading;
    }

    virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override {
        kg::log::debug() << "OnLoadEnd status = " << httpStatusCode;
    }

    virtual void OnLoadError(
        CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::ErrorCode errorCode,
        CefString const & errorText, CefString const & failedUrl) override {
        kg::log::debug() << "OnLoadError error = (" << errorCode << ") " << errorText << ", url = " << failedUrl;
    }

    virtual void OnLoadStart(
        CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefLoadHandler::TransitionType transition) override {
        kg::log::debug() << "OnLoadStart";
    }

    virtual void
    OnAddressChange(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefString const & url) override {
        kg::log::debug() << "OnAddressChange url = " << url;
    }

    virtual void OnTitleChange(CefRefPtr<CefBrowser> browser, CefString const & title) override {
        kg::log::debug() << "OnTitleChange title = " << title;
    }

    IMPLEMENT_REFCOUNTING(cef_client);

private:
    CefRefPtr<CefBrowser> _browser;
};

class cef_app : public CefApp, public CefBrowserProcessHandler {
public:
    cef_app() : CefApp {}, CefBrowserProcessHandler {} {}

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    virtual void OnContextInitialized() override {
        kg::log::debug() << "OnContextInitialized";

        CefBrowserSettings browserSettings;
        CefWindowInfo window;
        CefRefPtr<cef_client> client { new cef_client {} };

#ifdef _WIN32
        window.SetAsPopup(nullptr, "Sandbox");
#endif
        CefBrowserHost::CreateBrowser(window, client, "https://www.google.com", browserSettings, nullptr, nullptr);
    }

    IMPLEMENT_REFCOUNTING(cef_app);
};

#ifdef _WIN32
int wWinMain(HINSTANCE instance, HINSTANCE, LPWSTR, INT) {
    CefMainArgs args { instance };
    CefEnableHighDPISupport();
#else
int main(int argc, char ** argv) {
    CefMainArgs args { argc, argv };
#endif

    int ret { CefExecuteProcess(args, nullptr, nullptr) };
    if (ret >= 0) {
        return 0;
    }

    CefSettings settings;
    CefRefPtr<cef_app> app { new cef_app {} };

    // auto helper = std_fs_impl::current_path() / "kg.sandbox.exe";
    // CefString(&settings.browser_subprocess_path) = helper.native();

    if (!CefInitialize(args, settings, app, nullptr)) {
        abort();
    }

    CefRunMessageLoop();

    CefShutdown();
    return 0;
}
