#include "kg/browser/main_window.hh"

static std::string const KG_WINDOW_NAME { "Kangaroo" };

kg::MainWindow::MainWindow() : wxFrame { nullptr, wxID_ANY, KG_WINDOW_NAME }, _webview { new WebView { this } } {
    Show();
}

kg::MainWindow::~MainWindow() {}
