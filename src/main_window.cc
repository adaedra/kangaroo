#include "kg/main_window.hh"

#include <wx/aui/auibook.h>

kg::main_window::main_window()
  : wxFrame { nullptr, wxID_ANY, "Kangaroo" },
    _notebook { this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                wxAUI_NB_TAB_FIXED_WIDTH } {
    auto control = wx::ptr<wxControl> { _notebook, wxID_ANY };
    _notebook->AddPage(control, "Google");
}
