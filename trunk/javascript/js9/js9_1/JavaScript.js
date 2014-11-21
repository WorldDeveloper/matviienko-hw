function DropdownList(elem) {

    var child = elem.firstElementChild;
    style = window.getComputedStyle(child);
    var displayStyle = style.getPropertyValue('display');

    if (displayStyle == "none") {
        elem.style.listStyleImage = 'url("img/minus.png")';
        child.style.display = "block";       
    }
    else{
        elem.style.listStyleImage = 'url("img/plus.png")';
        child.style.display = "none";
    }
}

function HideExpandText(elem) {

    var child = elem.previousElementSibling;
    style = window.getComputedStyle(child);
    var displayStyle = style.getPropertyValue('display');

    if (displayStyle == "none") {
        elem.textContent='Hide text';
        child.style.display = "block";
    }
    else {
        elem.textContent = 'Expand text';
        child.style.display = "none";
    }
}