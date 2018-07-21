# bsdiff-nodejs
An binary diff and patch library based on bsdiff algorithm for NodeJS (Windows, Mac, Linux)

## INSTALLATION

Install as a dependency for your project:

```bash
npm install --save bsdiff-nodejs
```

## USAGE

```javascript
const bsdiff = require('bsdiff-nodejs');
bsdiff.diff(oldFile, newFile, patchFile, function(result, err) {}); // Async
bsdiff.patch(oldfile, newfile, patchfile, function(result, err) {}); // Async
```

For example:

```javascript
const bsdiff = require('bsdiff-nodejs');
const path = require('path');

const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
const patchFile = path.join(__dirname, 'resources/react.patch');
const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

bsdiff.diff(oldFile, newFile, patchFile, function(result, err) {
    if(err) return console.log('Error:', err);
    console.log(result + "%");

    if(result === 100) {
        console.log("Patch");
        bsdiff.patch(oldFile, generatedFile, patchFile, function(result, err) {
            if(err) return console.log('Error:', err)
            console.log(result + "%");
        });
    }
});
```

## License
Copyright 2003-2005 Colin Percival