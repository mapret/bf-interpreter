# Brainfuck interpreter

Yet another implementation of the [brainfuck](https://esolangs.org/wiki/brainfuck) esotheric programming language, developed in C++.

## Building

This project is built using [CMake](https://cmake.org/).

### Requirements

* cmake >= 3.0.2
* A C++ compiler with support for the C++17 standard

### Example

To build the project with the default CMake generator, use the following commands:
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

## Tests

The tests can executed by running
```
build/test/bf-test
```
from the repository root directory.

## Running

The interpreter can be run by typing
```
build/bf <path-to-source>
```
from the repository root directory, whereas `<path-to-source>` is the path to the Brainfuck source file that should be run.
For example, running
```
build/bf test/data/Hello.b
```
should yield "Hello World".

# License

This project, with the exception of the test/data directory, uses the [**BSD 3-Clause License**](LICENSE.txt).

The files in the test/data directory have their own licensing.
