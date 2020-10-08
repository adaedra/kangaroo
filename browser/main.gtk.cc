#include "kg/browser/app.hh"

int main(int argc, char ** argv) {
    kg::App * app = new kg::App {};

    return wxEntry(argc, argv);
}
