# Contributor Guide

This document has the following sections:

- [Setup](#setup)
- [Build](#build)
- [Test](#test)
- [Develop](#develop)


## Setup

To build and test the code, you must have a working installation of [Bazel](https://www.bazel.build/). Bazel is an open-source build and test tool similar to Make, Maven, and Gradle. See the [Bazel Installation Instructions](https://docs.bazel.build/versions/master/install.html) for more information on installing Bazel on your system.

## Build

From the root of the repository, you can run the following to build all Alpaca libraries and tests:

```
bazel build //alpaca/...
```

To build a specific target in a more minimal way, you can specify an individual build target:

```
bazel build //alpaca:alpaca
```

## Test

From the root of the repository, you can run the following to run all of the tests:

```
bazel test //alpaca/...
```

To run a specific test in a more minimal way, you can specify an individual test target:

```
bazel test //alpaca:status_test
```

## Develop

### Formatting C++ Files

To format all C++ source files using [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html), run the following:

```
find . -name "*.h" -or -name "*.cpp" | xargs clang-format -i
```
