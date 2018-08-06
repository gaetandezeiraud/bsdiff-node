{
  "targets": [
    {
      "target_name": "bsdiff",
      "sources": [
        "src/Main.cc",
        "src/DiffWorkerCallback.cc",
        "src/PatchWorkerCallback.cc",
        "src/c/bsdiff/bsdiff.c",
        "src/c/bspatch/bspatch.c",
        "src/c/bzip2/bzlib.c",
        "src/c/bzip2/compress.c",
        "src/c/bzip2/crctable.c",
        "src/c/bzip2/randtable.c",
        "src/c/bzip2/blocksort.c",
        "src/c/bzip2/huffman.c",
        "src/c/bzip2/decompress.c"
      ],      
      "include_dirs": [
        "include", "./src/bzip2",
        "<!(node -e \"require('nan')\")"
      ]      
    }
  ]
}