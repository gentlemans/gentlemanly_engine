#Compiling with Emscripten

Emscripten lets you run gentlemanly_engine in a web browser natively using WebGL and asm.js technologies. Here's how to set it up:

1. Follow the instructions [http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html](here) to install emscripten
2. Clone each of the dependencies seperately--you can't use /usr/include because that will override some of emscripten's special include paths.
3. Export the EMSCRIPTEN_DIR environment varialbe to the path which hold emscripten (the one with emcc in it)
4. Run build_emscripten.sh, which accepts extra compile arguments after that. Use this to add the include direcotories to the dependencies you cloned.
  Example: 
  `./build_emscripten.sh -I ~/boost -I ~/glm -I ~/Box2D`
5. Check that a libgentlemanly_engine.bc file was created in the build directory
6. `cd` to your game directory
7. run build_emscripten_game.sh from your game directory, again passing extra arguments, _including the C++ source files that are part of your game. and any [https://kripken.github.io/emscripten-site/docs/porting/files/packaging_files.html](--preload-file) direcives you need_
  Example: 
  `~/gentlemanly_engine/build_emscripten.sh main.cpp source1.cpp -I ~/boost -I ~/glm --preload-file data
8. Use some sort of webserver to test that it works.
