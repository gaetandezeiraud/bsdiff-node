'use strict';
const path = require('path');
const fs = require('fs');
const bsdiff = require('../index');

describe('bsdiff', () => {
  const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
  const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
  const patchFile = path.join(__dirname, 'resources/react.patch');
  const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

  afterEach(() => {
    fs.unlinkSync(patchFile);
    fs.unlinkSync(generatedFile);
  });

  describe('#diff() + #patch() async', () => {
    it('should generate an file identical to original file after appling a patch to an old file', async () => {
      await bsdiff.diff(oldFile, newFile, patchFile, function (result) {
        console.log('diff:' + String(result).padStart(4) + '%');
      });
      await bsdiff.patch(oldFile, generatedFile, patchFile, function (result) {
        console.log('patch:' + String(result).padStart(4) + '%');
      });
    });
  });
  describe('#diff() + #patch() sync', () => {
    it('should generate an file identical to original file after appling a patch to an old file', () => {
      bsdiff.diffSync(oldFile, newFile, patchFile);
      bsdiff.patchSync(oldFile, generatedFile, patchFile);
    });
  });
});
