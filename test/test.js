const path = require('path');
const bsdiff = require('../index');

describe('bsdiff', () => {
  describe('#diff() + #patch() async', () => {
    it('should generate an file identical to original file after appling a patch to an old file', () => {
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
                if(err) return console.log('Error:', err);
                console.log(result + "%");
            });
          }
      });
    });
  });
  describe('#diff() + #patch() sync', () => {
    it('should generate an file identical to original file after appling a patch to an old file', () => {
      const oldFile = path.join(__dirname, 'resources/react-0.3-stable.zip');
      const newFile = path.join(__dirname, 'resources/react-0.4-stable.zip');
      const patchFile = path.join(__dirname, 'resources/react.patch');
      const generatedFile = path.join(__dirname, 'resources/react-generated.zip');

      bsdiff.diffSync(oldFile, newFile, patchFile);
      bsdiff.patchSync(oldFile, generatedFile, patchFile);
    });
  });
});