function DropdownList(elem) {

    var child = elem.firstElementChild;
    var parent = elem.parentElement;

    for (var i = 0; i < elem.parentElement.childElementCount; ++i) {      

        if (elem.parentElement.children[i].childElementCount!=0 && elem.parentElement.children[i] != elem ) {            
            elem.parentElement.children[i].style.listStyleImage = 'url("img/plus.png")';
            elem.parentElement.children[i].firstElementChild.style.display = "none";
        }
    }

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