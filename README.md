# File resource compiler (fresco)

The file resource compiler (fresco) is a simple command line tool used for parsing resource files into c++ source file 
defined byte arrays. Fresco generates one source(.cpp) file and one header(.h) file. These generated files can then be
included in any c++ project. This program aims to be a simple solution for compiling static resources into a c++ executable.

## Example 

```asm
# fresco in /usr/local/bin
.
├── example
│    ├── encryption_keys.txt
│    ├── firmware_rev2a.bin
│    └── log.config
```
The following command compiles the above resources into a `resource.h` file and `resource.cpp` file. The name of the 
output files is designated by the `-n` flag. The `-d` indicates the output directory to be the current directory. Lastly,
the `-f` flag takes an arbitrary number of key values arguments. Each pair is comprises a string ID (left) and a file 
path (right). The data for each file can be accessed through the header files interface using the defined string ID.

```bash
cd example 
fresco -n resource -d . -f firmware firmware_rev2a.bin logConfig log.config keys encryption_keys.txt
```

The following is a simple hello world example. The code below shows how to access one of the resources compiled using 
the command above in a C++ project. The `initResources()` function must be called before any resources can be accessed.
This allocates the heap memory to store the resource data. The resource data will remain in memory until `freeResources()` 
is called. Resource data can be accessed using `getResourceData()`. The string ID passed into the command line tool is 
what is used to access each data resource. 

```cpp
#include "resource.h"

int main()
{
    Fresco::initResources(); 
    
    Fresco::ResourceData data = Fresco::getResourceData("firmware");
    for (int i = 0; i < data.dataLength; i++)
    {
        data.data[i]; // Do something with the data 
    }
    
    Fresco::freeResources();
    
    return 0;
}
```

## Build Instructions 

Build rhc requires the commonpp utilities library. The following commands will allow you to build fresco. 

```bash
git clone https://github.com/patrickTumulty/fresco.git
cd fresco/libs
git clone https://github.com/patrickTumulty/commonpp.git # Git clone commonpp utilities library 
cd ..
./build.sh 
```
