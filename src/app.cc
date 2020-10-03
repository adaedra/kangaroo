#include "kg/app.hh"

#include "kg/main_window.hh"
#include "kg/webview.hh"

#include <wx/ptr.hh>

kg::app::app() : wxApp() {}

bool kg::app::OnInit() {
    auto window = wx::ptr<kg::main_window> {};
    window->Show();

    return true;
}
