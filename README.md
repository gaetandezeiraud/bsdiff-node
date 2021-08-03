[![CI](https://github.com/Brouilles/bsdiff-node/actions/workflows/main.yml/badge.svg)](https://github.com/Brouilles/bsdiff-node/actions/workflows/main.yml)
![NpmLicense](https://img.shields.io/npm/l/express.svg)

# bsdiff-node
> An binary diff and patch library based on bsdiff algorithm for NodeJS (Windows, Mac, Linux)

<br>
<hr>
<p align="center">
If you find this package useful, please don't forget to star ⭐️ the repo, as this will help to promote the project.<br>
</p>
<hr>


## Installation

Install as a dependency for your project (need python 3.x):

```bash
npm i bsdiff-node
```

## Usage

```javascript
const bsdiff = require('bsdiff-node');
bsdiff.diff(oldFile, newFile, patchFile, function(result, err) {}); // Async
bsdiff.patch(oldfile, newfile, patchfile, function(result, err) {}); // Async

bsdiff.diffSync(oldFile, newFile, patchFile); // Sync
bsdiff.patchSync(oldfile, newfile, patchfile); // Sync
```

For example:

```javascript
const path = require('path');

const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
const patchFile = path.join(__dirname, 'resources/react.patch');
const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

async function asyncCall() {
    await bsdiff.diff(oldFile, newFile, patchFile, function (result) {
        console.log('diff:' + String(result).padStart(4) + '%');
    });

    await bsdiff.patch(oldFile, generatedFile, patchFile, function (result) {
        console.log('patch:' + String(result).padStart(4) + '%');
    });
}
  
asyncCall();
```

## License
The original algorithm and implementation was developed by Colin Percival.  The
algorithm is detailed in his paper, [Naïve Differences of Executable Code](http://www.daemonology.net/papers/bsdiff.pdf).  For more information, visit his
website at <http://www.daemonology.net/bsdiff/>.  

Copyright 2003-2005 Colin Percival  
MIT © Dezeiraud
