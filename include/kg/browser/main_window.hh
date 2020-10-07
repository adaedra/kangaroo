#pragma once
#include "kg/util/bridge.hh"
#include "kg/webview/webview.hh"

#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

namespace kg {
    class main_window {
    public:
        main_window();
        ~main_window();

    private:
        void wx_end();

        class wx_bridge : public wxFrame, public bridge<main_window> {
        public:
            wx_bridge(main_window *);
            ~wx_bridge();
        };

        friend class wx_bridge;
        wx_bridge * _wx;

        webview _webview;
    };
}
