## Design

cclap tries to somewhat reimplement the popular [clap-rs](https://github.com/clap-rs/clap) crate as a [stb](https://github.com/nothings/stb) style library for C.

## Installation

> [!WARNING]
> :red_circle: **IMPORTANT**: `cclap` is still in early development and not stable. Use at your own risk.

As mentioned above `cclap` is a stb style library. All you need to do is <a href="https://raw.githubusercontent.com/Flokkq/cclap/main/cclap.h" download>download</a> [cclap.h](cclap.h) and import it.

```c
#define CCLAP_IMPLEMENTATION // include the implementation code for cclap
#include "cclap.h"
```

## Examples

Usage examples are located in the `examples/` directory. You can also build these examples by following the instructions in the [Build Strategy](#build-strategy) section.

## Build Strategy

cclap uses the [`nob.h`](https://github.com/tsoding/nob.h) header to provide a "native" build system that eliminates the need for third-party systems like CMake or Ninja.

### Building the source

```console
$ cc -o nob nob.c
$ ./nob
```

The build script automatically rebuilds itself if it is modified.
