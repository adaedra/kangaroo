#include <include/cef_app.h>

int mainImpl(CefMainArgs & args);

int main(int argc, char ** argv) {
    CefMainArgs args { argc, argv };

    return mainImpl(args);
}
