#include "kg/browser/app.hh"

#include "kg/browser/main_window.hh"
#include "kg/util/defines.hh"
#include "kg/util/log.hh"
#include "kg/webview/webview.hh"

#include <functional>

#ifdef _WIN32
#    include <filesystem>
#else
#    include <experimental/filesystem>

namespace std {
    namespace filesystem = experimental::filesystem;
}
#endif

class kg::App::CefBridge : public CefApp, public CefBrowserProcessHandler {
public:
    CefBridge(kg::App * app) : CefApp {}, CefBrowserProcessHandler {}, _app { app }, _timer {} {
        _timer.Bind(wxEVT_TIMER, [](wxTimerEvent &) { wxWakeUpIdle(); });

        CefMainArgs args { _app->GetCefMainArgs() };
        CefSettings settings;
        auto helper = std::filesystem::current_path() / kg::HELPER_BINARY;

        settings.external_message_pump = true;
        CefString(&settings.browser_subprocess_path) = helper.native();

        CefPreInit();
        CefInitialize(args, settings, this, nullptr);
    }

    virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override {
        return this;
    }

    virtual void OnContextInitialized() override {
        _app->OnCefReady();
    }

    virtual void OnScheduleMessagePumpWork(int64 delay) override {
        if (delay <= 0) {
            wxWakeUpIdle();
            return;
        }

        _timer.Stop();
        _timer.StartOnce(delay);
    }

    IMPLEMENT_REFCOUNTING(CefBridge);

private:
    void CefPreInit();

    kg::App * _app;
    wxTimer _timer;
};

#ifdef _WIN32
void kg::App::CefBridge::CefPreInit() {
    CefEnableHighDPISupport();
}
#else
void kg::App::CefBridge::CefPreInit() {}
#endif

kg::App::App() : wxApp {}, _main_window { nullptr } {}

kg::App::~App() {}

bool kg::App::OnInit() {
    _cef = new CefBridge { this };
    return true;
}

int kg::App::OnExit() {
    _cef = nullptr;
    CefShutdown();

    return 0;
}

wxBEGIN_EVENT_TABLE(kg::App, wxApp)
    EVT_IDLE(kg::App::OnIdle)
wxEND_EVENT_TABLE()

#ifdef _WIN32
CefMainArgs kg::App::GetCefMainArgs() {
    return CefMainArgs { GetModuleHandleW(nullptr) };
}
#else
CefMainArgs kg::App::GetCefMainArgs() {
    return CefMainArgs { argc, argv };
}
#endif

void kg::App::OnCefReady() {
    _main_window = new MainWindow {};
}

void kg::App::OnIdle(wxIdleEvent &) {
    CefDoMessageLoopWork();
}
