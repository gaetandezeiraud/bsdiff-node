'use strict';

const bsdiff = require('./build/Release/bsdiff.node');

function promisify (fnName) {
  const fn = bsdiff[fnName];
  bsdiff[fnName] = function () {
    var args = Array.from(arguments);
    var callback;
    if (typeof args[args.length - 1] === 'function') {
      callback = args.pop();
    }
    return new Promise(function (resolve, reject) {
      args.push(function (result, err) {
        if (err) {
          reject(err);
        } else if (result >= 100) {
          process.nextTick(resolve);
        }
        if (callback) {
          callback(result, err);
        }
      });
      fn.apply(bsdiff, args);
    });
  };
}

promisify('diff');
promisify('patch');

module.exports = bsdiff;
