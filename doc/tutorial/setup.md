#Setup

##Linux

Setup on linux is relatively easy. Just install dependencies, and compile. 

Dependencies for each platform:
//TODO: see if this is actually real
####Ubuntu
```bash
apt-get update
apt-get install sdl2-dev libboost-all-dev assimp-dev freetype2-dev
```

####Arch Linux
```bash
pacman -Sy
pacman -S boost sdl2 assimp freetype2
```

###Building:
```bash
git clone https://github.com/gentlemans/gentlemanly_engine --recursive
mkdir gentlemanly_engine/build
cd gentlemanly_engine/build
cmake .. # Plus whatever other flags you want
make 
```

