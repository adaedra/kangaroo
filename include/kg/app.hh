#pragma once
#include <wx/_wrapper.hh>

namespace kg {
    class app : public wxApp {
    public:
        app();

        virtual bool OnInit() override;
    };
}
