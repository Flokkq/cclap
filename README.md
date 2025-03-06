## Design

cclap tries to reimplement the popular [clap](https://github.com/clap-rs/clap) in a [stb](https://github.com/nothings/stb) style for C.

## Build strategy

cclap utilizes [nob.h](https://github.com/tsoding/nob.h.git) for a "native" build system that does not rely on a third party build system like cmake, ninja etc.

### Building the source

```console
$ cc -o nob nob.c
$ ./nob
```

The `nob` automatically rebuilds itself if `nob.c` is modified thanks to
the `NOB_GO_REBUILD_URSELF` macro (don't forget to check out how it works below)
