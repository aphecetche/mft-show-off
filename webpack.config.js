const path = require('path');
const webpack = require('webpack');
module.exports = {
    entry: ['./themes/mft/js/pixels.js',
        './themes/mft/js/imageSlider.js'
    ],
    output: {
        filename: 'bundle.js',
        path: path.resolve(path.join(__dirname, 'themes/mft/static/js'))
    },
    plugins: [
        new webpack.ProvidePlugin({
            $: 'jquery',
            jQuery: 'jquery'
        })
    ]
};