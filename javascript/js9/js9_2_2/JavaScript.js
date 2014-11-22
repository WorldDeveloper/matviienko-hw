
function Rollover(paths) {
    this.mPaths = paths;
    this.mLoadedImgCount = 0;

    this.OnMouseOver = onMouseOver;
    this.OnMouseOut = onMouseOut;
    this.CountImages = function () { this.mLoadedImgCount++; }

    this.mImages = new Array();
    for (var i = 0; i < this.mPaths.length; ++i) {
        this.mImages[i] = new Image(160, 110);
        this.mImages[i].onload = this.CountImages();
        this.mImages[i].src = "rollovers/" + this.mPaths[i];
    }
}

function onMouseOver(elem, index) {
    if (this.mLoadedImgCount == this.mPaths.length)
        elem.src = this.mImages[index].src;
}

function onMouseOut(elem, index) {
    if (this.mLoadedImgCount == this.mPaths.length)
        elem.src = "images/" + this.mPaths[index];
    document.getElementById("description").innerHTML = "";
}
