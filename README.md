# ARP Third Assignment Server file 

Base repository for the **ARP Third Assignment Server**.
The three processes involved in the simulation of the vision system, namely **processAs**, **processAc** and **processB**, are implemented as simple *ncurses windows*. The development of the inter-process communication pipeline, that is the shared memory and one more thing to mention it is the server and client when you enter 1 it actually run the Server process which is ProcessAs and if you choose 2 the client will run.

You find a **master** process, responsible of spawning the entire simulation for the server.

## *libbitmap* installation and usage
To work with the bitmap library, you need to follow these steps:
1. Download the source code from [this GitHub repo](https://github.com/draekko/libbitmap.git) in your file system.
2. Navigate to the root directory of the downloaded repo and run the configuration through command ```./configure```. Configuration might take a while.  While running, it prints some messages telling which features it is checking for.

if the *./configure* is giving you error you just need to check if you have extracted the downloaded files and also you should be in the respected folder and check if you can see the configure by the ```ls``` again if gives error use these commands to update ubuntu. 
```
sudo apt-get update 
sudo apt-get install build-essential
``` 
then you can use to find out build GNU type
```
./configure --build=$(dpkg-architecture -qDEB_BUILD_GNU_TYPE)
```

3. Type ```make``` to compile the package.
4. Run ```make install``` to install the programs and any data files and documentation.
5. Upon completing the installation, check that the files have been properly installed by navigating to ```/usr/local/lib```, where you should find the ```libbmp.so``` shared library ready for use.
6. In order to properly compile programs which use the *libbitmap* library, you first need to notify the **linker** about the location of the shared library. To do that, you can simply add the following line at the end of your ```.bashrc``` file:      
```export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"```

## Compiling and running all project
The three processes are implemented as UIs through *ncurses* library, therefore you need to compile their source files by linking the shared library via ```-lncurses```. 

```
clear
gcc ./src/master.c -lm -lrt  -o ./bin/master
gcc ./src/processAs.c -lbmp -lncurses -lm -lrt -o ./bin/processAs
gcc ./src/processAc.c -lbmp -lncurses -lm -lrt -o ./bin/processAc
gcc ./src/processB.c -lbmp -lncurses -lm -lrt -o ./bin/processB
./bin/master
```


