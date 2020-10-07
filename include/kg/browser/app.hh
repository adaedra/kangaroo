#pragma once
#include "kg/util/bridge.hh"

#include <include/cef_app.h>
#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

namespace kg {
    class MainWindow;

    class App : wxApp {
    public:
        App();
        virtual ~App();

        virtual bool OnInit() override;
        virtual int OnExit() override;

        wxDECLARE_EVENT_TABLE();

    private:
        CefMainArgs GetCefMainArgs();
        void OnCefReady();
        void OnIdle(wxIdleEvent &);

        class CefBridge;
        friend class CefBridge;

        CefBridge * _cef;
        MainWindow * _main_window;
    };
}
