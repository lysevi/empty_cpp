# empty_cpp

template of empty C++ project

[![Build Status](https://travis-ci.org/lysevi/empty_cpp.svg?branch=master)](https://travis-ci.org/lysevi/empty_cpp) [![codecov](https://codecov.io/gh/lysevi/dqueue/branch/master/graph/badge.svg)](https://codecov.io/gh/lysevi/empty_cpp)

## Build
---

### Git submodules
```shell
$ cd empty_cpp
$ git submodules init 
$ git submodules update
```

### Available build options
- **EMPTYCPP_ENABLE_TESTS** - Enable testing.
- **EMPTYCPP_ENABLE_DOUBLECHECKS** - More checks in code.
- **EMPTYCPP_ENABLE_BENCHMARKS** - Enable benchmarks.
- **EMPTYCPP_ASAN_UBSAN** - Enable address & undefined behavior sanitizer for binary.
- **EMPTYCPP_MSAN** - Enable memory sanitizer for binary.
