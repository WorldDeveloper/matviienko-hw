function checkSurname(text) {

    var capLetter = "[A-ZА-ЯЁІЇЄ']";
    var smallLetter = "[a-zа-яёіїє']";
    var re = "^" + capLetter + smallLetter + "+ ((" + capLetter + "\.)|(" + capLetter + ")){2}$"

    var rExp = new RegExp(re, "");
    if (rExp.test(text))
        alert("Thanks, "+text+"!");
    else
        alert("Incorrect input. Please try again.");
}