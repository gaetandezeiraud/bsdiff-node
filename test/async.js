const path = require('path');
const bsdiff = require('../index');

/*let interval = setInterval(function() {
    console.log(bsdiff.getPercentage() + '%');

    if(bsdiff.getPercentage() >= 99)
        clearInterval(interval);
}, 1);

const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
const patchFile = path.join(__dirname, 'resources/react.patch');
const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

bsdiff.diff(oldFile, newFile, patchFile, function(err) {
    if(err) return console.log('Error:', err)

    console.log('bsdiff.diff end!')
});
bsdiff.patch(oldFile, generatedFile, patchFile); */

const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
const patchFile = path.join(__dirname, 'resources/react.patch');
const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

bsdiff.diff(oldFile, newFile, patchFile, function(result, err) {
    if(err) return console.log('Error:', err)
    console.log(result + "%")
});
