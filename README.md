# Resource Header Compiler (rhc)

The resource header compiler is a simple command line tool used for parsing byte information from
various files into header file defined byte arrays. The resulting header file can then be included
in any C or C++ project.

Each input file will be written in the resulting header file as a `uint8_t` byte array. The length of which will be 
stored in a length variable; the name of the variable with `_length` appended to it. 

## Input Arguments:
```bash
$ rhc <output-filename> <var-name> <file-path> ...
```
`output-filename` - The name of the output header file.

`<var-name> <file-path>` - The `<var-name>` is the name that the byte array will be saved as in the resulting header 
file. The `<file-path>` is the path to read the byte data from. The `<var-name> <file-path>` pattern can be repeated to
include multiple files.

## Example:
```bash
$ rhc data_header.h animals animals.txt trees trees.csv photo sunset.png
```
    
The above example will output `data_header.h`. This header will have variables `animals`, `animals_length`, 
`trees`, `trees_length`, `photo` and `photo_length` defined. 