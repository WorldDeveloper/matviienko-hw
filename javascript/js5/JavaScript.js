
function CreateWnd(path) {
    var wndWidth=640;
    var wndHeight=480;
    var wndLeft=(screen.availWidth-wndWidth)/2;
    var wndTop = (screen.availHeight - wndHeight) / 2;

    var wnd = window.open("", "", "width=" + wndWidth + ", height=" + wndHeight + ", left=" + wndLeft + ", top=" + wndTop + ", resizable=0");

    wnd.document.open();
    wnd.document.write("<html><body style='margin:0;'><img src='" + path + "' /></body></html>");
    wnd.document.close();
}
