module.exports = {
  'extends': 'standard',
  'rules': {
    'semi': [
      'error',
      'always'
    ]
  },
  'overrides': [
    {
      'files': [
        'test/**/*',
        '*-test.js',
        '*.spec.js'
      ],
      'env': {
        'mocha': true
      }
    }
  ]
};
