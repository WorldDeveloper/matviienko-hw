
function Animation(elem) {
    this.obj = elem;
    this.pointerX = 0;
    this.pointerY = 0;
    this.R = 30;
    this.a = 0;
    this.da = 3 * Math.PI / 180;
    this.delay = 30;
    var self = this;

    this.setCursorXY = function (e) {
        self.pointerX = (window.Event) ? e.pageX : event.clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);
        self.pointerY = (window.Event) ? e.pageY : event.clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);
       
    }
    document.onmousemove = this.setCursorXY;
   
    this.moveElement = function () {
        this.obj.style.left = (this.pointerX + this.R * Math.cos(this.a)) + "px";
        this.obj.style.top = (this.pointerY + this.R * Math.sin(this.a)) + "px";
        this.a += this.da;
    }   
    setInterval(function () { return self.moveElement(); }, this.delay);
}