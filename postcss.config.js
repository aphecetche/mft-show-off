module.exports = {
    plugins: [
        require('postcss-easy-import')({
            'path': ['themes/mft/css/'],
            'prefix': '_',
            'extension': 'css'
        }),
        require('postcss-simple-vars'),
        require('postcss-css-variables'),
        require('postcss-cssnext'),
        require('postcss-font-magician'),
    ]
};