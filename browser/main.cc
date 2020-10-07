#include "kg/browser/app.hh"
#include "kg/util/log.hh"
#include "wx/ptr.hh"

#ifdef _WIN32
int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdline, INT mode) {
    kg::App app {};

    return wxEntry(instance, prevInstance, cmdline, mode);
}
#else
int main(int argc, char ** argv) {
    kg::App * app = new kg::App {};

    return wxEntry(argc, argv);
}
#endif
