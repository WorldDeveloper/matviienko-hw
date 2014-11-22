function CreateList() {
    document.open();
    document.write("<ul id='toSort'>");
    for (var i = 0; i < 10; ++i) {
        var randomNumber = Math.floor(Math.random() * 10);
        document.write("<li>item " + randomNumber + "</li>");
    }
    document.write("</ul>");
    document.close();
}

function SortElements() {
    var list = document.getElementById('toSort');
    var childCount = list.childElementCount;

    while (childCount > 1)
    {
        childCount--;
        for (var item = 0; item < childCount; ++item)
        {
            var current = list.childNodes[item];
            var next = list.childNodes[item + 1];

            if (current.textContent > next.textContent) {
                list.insertBefore(next, current);
            }
        }
    }
}