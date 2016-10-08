#Building gentlemanly_engine
The first thing you are going to want to do after you `git clone` gentlemanly engine is to compile it. We use a fairly standard [CMake](https://cmake.org) build system, that doesn't requrie any dependencies except cmake and some OpenGL library (you usually don't have to install this). All of the  dependencies are stored in the [deps](https://github.com/gentlemans/gentlemanly_engine/blob/master/deps) directory and are automatically built by cmake. 

##Linux
ge works wonderfully on linux, and was actually first designed there. Just install cmake then build it.


###Ubuntu
```
apt-get install cmake
```

###Arch
```
pacman -S cmake
```

Then just run

```bash
mkdir build && cd build
cmake ..
make
```


##OSX
It also works great on OSX. Just install [homebrew](brew.sh) and install cmake with it:
```
brew install cmake
```

Then run the same build commands:

```bash
mkdir build && cd build
cmake ..
make 
```

##Windows
As windows is the main desktop gaming platform today, it's important that windows is supported.

First, you must [install CMake]().

###Visual Studio 2015 
Visual Studio doesn't have native CMake support, so you must generate msbuild files for it using CMake. These generated files will automatically run cmake again when the build files change so you shouldn't have to regenerate the build files that often. 

Using the CLI:
```bash
mkdir build
cd build
cmake .. -G"Visual Studio 14 Win64"
```

Or using cmake-gui:

Set `/path/to/gentlemanly_engine/build` as the build directory and `/path/to/gentlemanly_engine` as the source  directory and click generate. Select Visual Studio 14 Win64 as a generator and wait for it to finish (it'll take a minute). Click configure then generate and then open up gentlemanly_engine.sln that is in the build directory. 

###Qt Creator
Just open  up the CMakeLists.txt file in Qt creator. Should work like a charm.
