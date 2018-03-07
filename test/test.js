const path = require('path');
const bsdiff = require('../index');

describe('bsdiff', () => {
  describe('#diff() + #patch()', () => {
    it('should generate an file identical to original file after appling a patch to an old file', () => {
      const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
      const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
      const patchFile = path.join(__dirname, 'resources/react.patch');
      const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

      bsdiff.diff(oldFile, newFile, patchFile);
      bsdiff.patch(oldFile, generatedFile, patchFile);
    });
  });
});