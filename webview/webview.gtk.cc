#include "kg/webview/webview.hh"

#include <gdk/gdkx.h>
#include <gtk/gtk.h>

void kg::WebView::FinishInit() {}

void kg::WebView::GTKHandleRealized() {
    CreateBrowser();
}

void kg::WebView::PrepareWindow(CefWindowInfo & window) {
    Window xid { gdk_x11_drawable_get_xid(GetHandle()->window) };
    wxSize size { GetSize() };
    CefRect rect { 0, 0, size.GetWidth(), size.GetHeight() };

    window.SetAsChild(xid, rect);
}

void kg::WebView::ResizeBrowser(CefRefPtr<CefBrowser> & browser, unsigned int width, unsigned int height) {
    Window xid { browser->GetHost()->GetWindowHandle() };
    Display * display { gdk_x11_drawable_get_xdisplay(GetHandle()->window) };

    XResizeWindow(display, xid, width, height);
}
