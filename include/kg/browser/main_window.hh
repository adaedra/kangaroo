#pragma once
#include "kg/util/child.hh"
#include "kg/webview/webview.hh"

#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

namespace kg {
    class main_window {
    public:
        main_window();
        ~main_window();

    private:
        class wx_bridge : public wxFrame, public child<main_window> {
        public:
            wx_bridge(main_window &);
        };

        friend class wx_bridge;
        wx_bridge * _wx;

        webview _webview;
    };
}
