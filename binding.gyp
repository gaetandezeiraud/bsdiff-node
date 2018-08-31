{
  "targets": [
    {
      "target_name": "bsdiff",
      "sources": [
        "src/Main.cpp",
        "src/DiffWorkerCallback.cpp",
        "src/PatchWorkerCallback.cpp",
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
        "include", "./src/c/bzip2",
        "<!(node -e \"require('nan')\")"
      ]      
    }
  ]
}