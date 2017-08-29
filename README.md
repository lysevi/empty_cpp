# empty_cpp

template of empty C++ project

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