#pragma once
#include "kg/util/bridge.hh"

#include <include/cef_app.h>
#include <wx/_wrapper.hh>
#include <wx/ptr.hh>

namespace kg {
    class main_window;

    class app {
    public:
        app();
        ~app();

        bool init();
        void ready();
        void idle();
        void exit();

    private:
        main_window * _main_window;

        class cef_bridge : public bridge<app>, public CefApp, public CefBrowserProcessHandler {
        public:
            cef_bridge(app &);
            ~cef_bridge();

            bool init();

            virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;
            virtual void OnContextInitialized() override;

            IMPLEMENT_REFCOUNTING(cef_bridge);
        };

        friend class cef_bridge;
        cef_bridge * _cef;

        class wx_bridge : public wxApp, public bridge<app> {
        public:
            wx_bridge(app &);

            virtual bool OnInit() override;
            virtual int OnExit() override;
            void OnIdle(wxIdleEvent &);

            wxDECLARE_EVENT_TABLE();
        };

        friend class wx_bridge;
        wx_bridge * _wx;
    };
}
