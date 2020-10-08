#include "kg/browser/app.hh"

int WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmdline, INT mode) {
    kg::App app {};

    return wxEntry(instance, prevInstance, cmdline, mode);
}
