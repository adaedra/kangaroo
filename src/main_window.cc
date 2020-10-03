#include "kg/main_window.hh"

#include <wx/aui/auibook.h>

kg::main_window::main_window()
  : wxFrame { nullptr, wxID_ANY, "Kangaroo" }, _webview { this } {}
