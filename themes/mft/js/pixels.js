function getRandomColor() {
    var letters = '123456789ABCDEF';
    //var letters = '789ABCD';
    var color = '#';
    for (var i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 15)];
    }
    return color;
}

function fillPixels(pixels) {
    console.log("in fillPixels function");
    var pixels = document.getElementById('pixels');
    var c = pixels.children;
  for ( i = 0; i< c.length; ++i ) {
      c[i].setAttributeNS(null,'fill',getRandomColor());
  }
}

function createPixels(pixels) {
    var svgns = "http://www.w3.org/2000/svg";
    var w = 15;
    var h = 15;
    for (var x = 0; x < 500; x += w + 1) {
        for (var y = 0; y < 500; y += h + 1) {
            var rect = document.createElementNS(svgns, "rect");
            rect.setAttributeNS(null, 'x', x);
            rect.setAttributeNS(null, 'y', y);
            rect.setAttributeNS(null, 'width', w);
            rect.setAttributeNS(null, 'height', h);
            rect.setAttributeNS(null, 'fill', '#000');
            pixels.appendChild(rect);
        }
    }
    setInterval(fillPixels,1000);
}

function pixels() {
    var pixels = document.getElementById('pixels');
    var npixels = pixels.childElementCount;
    if (npixels==0) {
        createPixels(pixels);
    }
}

// document ready
// version without jQuery (FIXME: doesn't work in older IEs)
document.addEventListener('DOMContentLoaded', function () {
    pixels();
}, false);