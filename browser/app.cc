#include "kg/browser/app.hh"

#include "kg/browser/main_window.hh"
#include "kg/util/log.hh"
#include "kg/webview/webview.hh"

#include <filesystem>
#include <wx/ptr.hh>

kg::app::app() : _cef { new cef_bridge { *this } }, _wx { new wx_bridge { *this } }, _main_window { nullptr } {}

kg::app::~app() {
    KG_LOG_TRACE();
    delete _main_window;
    // delete _wx;
    delete _cef;
}

bool kg::app::init() {
    KG_LOG_TRACE();
    return _cef->init();
}

void kg::app::ready() {
    _main_window = new kg::main_window {};

    KG_LOG_TRACE();
}

void kg::app::idle() {
    // KG_LOG_TRACE();
    CefDoMessageLoopWork();
}

void kg::app::exit() {
    KG_LOG_TRACE();
    // Can't do that here as _main_window is still existing. Have to be smarter.
    // CefShutdown();
}

#pragma mark cef_bridge

kg::app::cef_bridge::cef_bridge(kg::app & app) : kg::child<kg::app> { app }, CefApp {}, CefBrowserProcessHandler {} {}

kg::app::cef_bridge::~cef_bridge() {
    KG_LOG_TRACE();
}

bool kg::app::cef_bridge::init() {
    CefMainArgs args { GetModuleHandleW(nullptr) };
    CefSettings settings;

    auto helper = std::filesystem::current_path() / "kg.helper.exe";
    CefString(&settings.browser_subprocess_path) = helper.native();
    // settings.log_severity = LOGSEVERITY_VERBOSE;

    CefEnableHighDPISupport();
    if (!CefInitialize(args, settings, this, nullptr)) {
        return false;
    }

    return true;
}

CefRefPtr<CefBrowserProcessHandler> kg::app::cef_bridge::GetBrowserProcessHandler() {
    return this;
}

void kg::app::cef_bridge::OnContextInitialized() {
    _parent.ready();
}

#pragma mark wx_bridge

kg::app::wx_bridge::wx_bridge(kg::app & app) : kg::child<kg::app> { app }, wxApp {} {}

bool kg::app::wx_bridge::OnInit() {
    return _parent.init();
}

int kg::app::wx_bridge::OnExit() {
    _parent.exit();
    return 0;
}

void kg::app::wx_bridge::OnIdle(wxIdleEvent &) {
    _parent.idle();
}

wxBEGIN_EVENT_TABLE(kg::app::wx_bridge, wxApp)
    EVT_IDLE(kg::app::wx_bridge::OnIdle)
wxEND_EVENT_TABLE()
