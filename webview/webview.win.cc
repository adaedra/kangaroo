#include "kg/webview/webview.hh"

void kg::WebView::FinishInit() {
    CreateBrowser();
}

void kg::WebView::PrepareWindow(CefWindowInfo & window) {
    wxSize size { GetSize() };
    RECT rect { 0, 0, size.GetWidth(), size.GetHeight() };

    window.SetAsChild(GetHWND(), rect);
}

void kg::WebView::ResizeBrowser(CefRefPtr<CefBrowser> & browser, unsigned int width, unsigned int height) {
    SetWindowPos(browser->GetHost()->GetWindowHandle(), nullptr, 0, 0, width, height, SWP_NOZORDER);
}
