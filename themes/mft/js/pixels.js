var gaussian = require('gaussian');

var updateFrequency = "500"; //ms

function getRandomColor(x, y) {
    var mean = x / 500;
    var variance = 70;
    var distribution = gaussian(20 + mean * 200, variance);
    // Take a random sample using inverse transform sampling method. 
    var hue = distribution.ppf(Math.random());

    if (y < 100 || y > 320) {
        if (Math.random() > 0.5) {
            return "white";
        }
    }

    var saturation = "100";
    var luminance = "50";
    saturation = 80 + Math.random() * 20;
    return "hsl(" + hue + "," + saturation + "%," + luminance + "%)";
}

function fillPixels(pixels) {
    var pixels = document.getElementById('pixels');
    var c = pixels.children;
    for (i = 0; i < c.length; ++i) {
        var x = c[i].getAttributeNS(null, 'x');
        var y = c[i].getAttributeNS(null, 'y');
        c[i].setAttributeNS(null, 'fill', getRandomColor(x, y));
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
    setInterval(fillPixels, updateFrequency);
}

function pixels() {
    var pixels = document.getElementById('pixels');
    var npixels = pixels.childElementCount;
    if (npixels == 0) {
        createPixels(pixels);
    }
}

// document ready
// version without jQuery (FIXME: doesn't work in older IEs)
document.addEventListener('DOMContentLoaded', function () {
    pixels();
}, false);