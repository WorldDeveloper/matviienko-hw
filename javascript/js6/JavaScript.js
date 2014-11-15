
function OpenUrl(){
    if (navigationBar.newWindow.checked) window.open(navigationBar.destUrl.value);
    else document.getElementById("mainFrame").src = navigationBar.destUrl.value;
}

