# XLang and XLanger

## Overview

### XLang

XLang is a simple C-like programming language.

XLang compiler invoked from command line as `xlang` is built on the XLanger parser library.

### XLanger

XLanger is a C++ header only compile time library for generation of RL context-free grammar parsers. 

## Installation

### Requirements

cmake 3.14 or higher, a recent version of gcc or clang with proper c++17 support

### Getting the source

Current sources are available on github:

```shell script
git clone git@github.com:xgallom/xlang.git
```

### Preparations

```shell script
mkdir xlang-build
cd xlang-build
cmake ../xlang
```

### Installing the XLang compiler

```shell script
make all
cd xlang
make install
```

### Installing the XLanger library

```shell script
cd xlanger
make install
```

### Installing Everything

```shell script
make all
make install
```

## License

XLanger library and the XLang compiler are distributed under the GPLv2 license available [here](LICENSE.md)
