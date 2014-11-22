function DropdownList(elem) {

    var child = elem.firstElementChild;
    var parent = elem.parentElement;

    for (var i = 0; i < parent.childElementCount; ++i) {      

        if (parent.children[i].childElementCount!=0 && parent.children[i] != elem ) {            
            parent.children[i].style.listStyleImage = 'url("img/plus.png")';
            parent.children[i].firstElementChild.style.display = "none";
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