    
function format (n){
    return n<10 ? "0"+n : n;
}
        
function updateClock() {
    var weekday = [];
    weekday[0] = "Sun";
    weekday[1] = "Mon";
    weekday[2] = "Tue";
    weekday[3] = "Wed";
    weekday[4] = "Thu";
    weekday[5] = "Fri";
    weekday[6] = "Sat";

    var d = new Date ();
    clock.innerHTML = "<span class='clocksTime'>" + format(d.getHours()) + ":" + format(d.getMinutes()) + ":" + format(d.getSeconds()) +"</span>"+
        "<br /><span class='clocksDate'>" + weekday[d.getDay()] + " " + format(d.getDate()) + "." + format(d.getMonth() + 1) + "." + d.getFullYear() + "</span>";
}
