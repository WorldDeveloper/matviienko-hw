    
function format (n){
    return n<10 ? "0"+n : n;
}
        
function updateClock() {
    var weekday = ["Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"];
    var d = new Date();

    clock.innerHTML = "<span class='clocksTime'>" +
        format(d.getHours()) + ":" + format(d.getMinutes()) + ":" + format(d.getSeconds()) + "</span><br />" +
        "<span class='clocksDate'>" +
        weekday[d.getDay()] + " " + format(d.getDate()) + "." + format(d.getMonth() + 1) + "." + d.getFullYear() + "</span>";
}
