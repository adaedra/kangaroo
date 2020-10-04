#include "kg/browser/main_window.hh"

#include "kg/util/log.hh"

kg::main_window::main_window() : _wx { new wx_bridge { *this } }, _webview { KG_LOG_SHOW(_wx) } {
    wxSize size { _wx->GetClientSize() };
    KG_LOG_TRACE() << " size = (" << size.GetWidth() << ", " << size.GetHeight() << ")";
    _webview.set_size(size.GetWidth(), size.GetHeight());
}

kg::main_window::~main_window() {
    KG_LOG_TRACE();
}

kg::main_window::wx_bridge::wx_bridge(kg::main_window & parent)
  : kg::child<kg::main_window> { parent }, wxFrame { nullptr, wxID_ANY, "Kangaroo" } {
    Show();
}
