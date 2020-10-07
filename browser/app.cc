#include "kg/browser/app.hh"

#include "kg/browser/main_window.hh"
#include "kg/util/defines.hh"
#include "kg/util/log.hh"
#include "kg/webview/webview.hh"

#ifdef _WIN32
#    include <filesystem>
#else
#    include <experimental/filesystem>

namespace std {
    namespace filesystem = experimental::filesystem;
}
#endif
#include <wx/ptr.hh>

kg::app::app() : _cef { new cef_bridge { *this } }, _wx { new wx_bridge { *this } }, _main_window { nullptr } {}

kg::app::~app() {
    KG_LOG_TRACE();
    delete _main_window;
}

bool kg::app::init() {
    KG_LOG_TRACE() << " this = " << this;
    return _cef->init();
}

void kg::app::ready() {
    _main_window = new kg::main_window {};

    KG_LOG_TRACE();
}

bool kg::app::idle() {
    return _cef->idle();
}

void kg::app::exit() {
    KG_LOG_TRACE();
    // Can't do that here as _main_window is still existing. Have to be smarter.
    // CefShutdown();
}

kg::app::cef_bridge::cef_bridge(kg::app & app)
  : bridge<kg::app> { app }, CefApp {}, CefBrowserProcessHandler {}, _has_work { false } {}

kg::app::cef_bridge::~cef_bridge() {
    KG_LOG_TRACE();
}

bool kg::app::cef_bridge::init() {
#ifdef _WIN32
    CefMainArgs args { GetModuleHandleW(nullptr) };
#else
    CefMainArgs args { wxTheApp->argc, wxTheApp->argv };
#endif
    CefSettings settings;

    auto helper = std::filesystem::current_path() / kg::KG_HELPER_BINARY;
    CefString(&settings.browser_subprocess_path) = helper.native();
    // settings.log_severity = LOGSEVERITY_VERBOSE;
    settings.external_message_pump = true;

#ifdef _WIN32
    CefEnableHighDPISupport();
#endif
    if (!CefInitialize(args, settings, this, nullptr)) {
        return false;
    }

    KG_LOG_TRACE() << " Cef Initialized";
    return true;
}

bool kg::app::cef_bridge::idle() {
    KG_LOG_TRACE() << " " KG_LOG_VAR(_has_work);

    if (!_has_work) {
        return false;
    }

    _has_work = false;
    CefDoMessageLoopWork();
    KG_LOG_TRACE() << " " << KG_LOG_VAR(_has_work);

    return _has_work;
}

CefRefPtr<CefBrowserProcessHandler> kg::app::cef_bridge::GetBrowserProcessHandler() {
    return this;
}

void kg::app::cef_bridge::OnContextInitialized() {
    _parent.ready();
}

void kg::app::cef_bridge::OnScheduleMessagePumpWork(int64 delay) {
    KG_LOG_TRACE() << " " << KG_LOG_VAR(delay);
    _has_work = true;

    if (delay <= 0) {
        wxWakeUpIdle();
    }
}

kg::app::wx_bridge::wx_bridge(kg::app & app) : wxApp {}, kg::bridge<kg::app> { app } {}

bool kg::app::wx_bridge::OnInit() {
    return _parent.init();
}

int kg::app::wx_bridge::OnExit() {
    _parent.exit();
    return 0;
}

void kg::app::wx_bridge::OnIdle(wxIdleEvent & event) {
    if (_parent.idle()) {
        event.RequestMore(true);
    }
}

wxBEGIN_EVENT_TABLE(kg::app::wx_bridge, wxApp)
    EVT_IDLE(kg::app::wx_bridge::OnIdle)
wxEND_EVENT_TABLE()
