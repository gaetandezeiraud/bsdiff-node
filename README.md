# bsdiff-nodejs
An binary diff and patch library based on bsdiff algorithm for NodeJS (Windows, Mac, Linux)

## INSTALLATION

Install as a dependency for your project:

```bash
npm install --save bsdiff-nodejs
```

## USAGE

Use as a command-line tool:
```bash
bsdiff-nodejs diff oldfile newfile patchfile
bsdiff-nodejs patch oldfile newfile patchfile
```

or as a lib:

```javascript
const bsdiff = require('bsdiff-nodejs');

bsdiff.diff(oldfile, newfile, patchfile);
bsdiff.patch(oldfile, newfile, patchfile);
```

For example:

```javascript
const bsdiff = require('bsdiff-nodejs');
const path = require('path');

const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
const patchFile = path.join(__dirname, 'resources/react.patch');
const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

bsdiff.diff(oldFile, newFile, patchFile);
bsdiff.patch(oldFile, generatedFile, patchFile);
```

## License
Copyright 2003-2005 Colin Percival

Inspiration from:

- https://github.com/tsyeyuanfeng/bsdp
- https://github.com/GankLun/bsdiff-cross-platform