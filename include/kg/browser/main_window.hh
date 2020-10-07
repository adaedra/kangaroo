#pragma once
#include "kg/util/bridge.hh"
#include "kg/webview/webview.hh"

#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

namespace kg {
    class MainWindow : public wxFrame {
    public:
        MainWindow();
        ~MainWindow();

    private:
        WebView * _webview;
    };
}
