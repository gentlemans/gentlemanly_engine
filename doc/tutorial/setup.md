#Setup

##Linux/MacOS

Setup on linux is relatively easy. Just install dependencies, and compile. 

Dependencies for each platform:
//TODO: see if this is actually real
####Ubuntu
```bash
apt-get update
apt-get install cmake git libsdl2-dev libboost-all-dev libassimp-dev libfreetype6-dev
```

####Arch Linux
```bash
pacman -Sy
pacman -S git cmake boost sdl2 assimp freetype2
```

####MacOS with brew
```bash
brew update
brew install boost sdl2 assimp freetype
```

###Building:
```bash
git clone https://github.com/gentlemans/gentlemanly_engine --recursive #Recursive because it has submodules 
mkdir gentlemanly_engine/build
cd gentlemanly_engine/build
cmake .. # Plus whatever other flags you want, maybe -G "Xcode" if you want an xcode project
make 
```

##Windows
Windows is a bit more of a pain to setup. There are a few manual steps, but for the most part the dependencies are in submodules. 

###Installing SDL2
Download SDL from //TODO the SDL website and extract it and place it either `C:/`, `C:/Program Files` or `C:/Program Files (x86)`, or anywhere else if you pass the `-DSDL2_PATH=/path/to/sdl` flag to cmake. 