#pragma once
#include "kg/webview/webview.hh"

#include <wx/_wrapper.hh>

namespace kg {
    class MainWindow : public wxFrame {
    public:
        MainWindow();
        ~MainWindow();

    private:
        WebView * _webview;
    };
}
