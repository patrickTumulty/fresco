# File resource compiler (fresco)

The file resource compiler is a simple command line tool used for parsing byte information from
various files into source code byte arrays. The resulting source and header files can then be included
in any C++ project. This program aims to be a simple solution for compiling static resources into a C++ executable.

## Build Instructions 

Build rhc requires the commonpp utilities library. The following commands will allow you to build rhc. 

```bash
git clone https://github.com/patrickTumulty/rhc.git
cd rhc/libs
git clone https://github.com/patrickTumulty/commonpp.git # Git clone commonpp utilities library 
cd ..
mkdir build
cd build
cmake ..
make
```
