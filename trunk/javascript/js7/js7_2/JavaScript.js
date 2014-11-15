function checkEmail(text) {
    var rExp = /^[a-z][a-z0-9\-]{2,9}@(([a-z0-9]+)|([a-z0-9]+\.[a-z0-9]+))\.[a-z]{2,3}$/;
    if (rExp.test(text))
        alert("Thanks!");
    else
        alert("Incorrect input. Please try again.");
}