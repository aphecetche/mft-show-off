module.exports = {
    plugins: [
        require('postcss-easy-import')({
            'path': ['themes/mft/static/css/'],
            'prefix': '_',
            'extension': 'css'
        }),
        require('postcss-cssnext'),
        require('postcss-font-magician')
    ]
};