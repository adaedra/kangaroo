#pragma once
#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

class wxAuiNotebook;

namespace kg {
    class main_window : public wxFrame {
    public:
        main_window();

    private:
        wx::ptr<wxAuiNotebook> _notebook;
    };
}
