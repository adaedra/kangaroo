#include "kg/browser/main_window.hh"

#include "kg/util/log.hh"

kg::main_window::main_window() : _wx { new wx_bridge { this } }, _webview { KG_LOG_SHOW(_wx) } {
    wxSize size { _wx->GetClientSize() };
    KG_LOG_TRACE() << " size = (" << size.GetWidth() << ", " << size.GetHeight() << ")";
    _webview.set_size(size.GetWidth(), size.GetHeight());
}

kg::main_window::~main_window() {
    KG_LOG_TRACE();
}

void kg::main_window::wx_end() {
    KG_LOG_TRACE();
    _wx = nullptr;
}

static std::string const KG_WINDOW_NAME { "Kangaroo" };

kg::main_window::wx_bridge::wx_bridge(kg::main_window * parent)
  : wxFrame { nullptr, wxID_ANY, KG_WINDOW_NAME }, bridge<kg::main_window> { *parent } {
    Show();
}

kg::main_window::wx_bridge::~wx_bridge() {
    KG_LOG_TRACE();
    _parent.wx_end();
}
