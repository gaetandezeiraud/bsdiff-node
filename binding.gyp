{
  "targets": [
    {
      "target_name": "bsdiff",
      "sources": [
        "src/main.cc",
        "src/bsdiff/bsdiff.c",
        "src/bspatch/bspatch.c",
        "src/bzip2/bzlib.c",
        "src/bzip2/compress.c",
        "src/bzip2/crctable.c",
        "src/bzip2/randtable.c",
        "src/bzip2/blocksort.c",
        "src/bzip2/huffman.c",
        "src/bzip2/decompress.c"
      ],      
      "include_dirs": [
        "include", "./src/bzip2"
      ]      
    }
  ]
}