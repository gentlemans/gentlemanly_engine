
![Gentlemanly Engine](logo.png)

[![Build Status](https://travis-ci.org/gentlemans/gentlemanly_engine.svg?branch=master)](https://travis-ci.org/gentlemans/gentlemanly-engine) [![Build status](https://ci.appveyor.com/api/projects/status/mhru5cnay31dx9k2?svg=true)](https://ci.appveyor.com/project/GuapoTaco/gentlemanly-engine-pbbow)
 [![Trello](https://img.shields.io/badge/trello-online-green.svg)](https://trello.com/b/PyLZzMbi/gentlemanly-engine) [ ![Documentation](https://img.shields.io/badge/documentation-online-green.svg)](doc/README.md) 

A super standard C++ game engine

#Abstract
The gentlemanly_engine is meant to provide a easy to learn, standard, well documented, extensible object-oriented 2D game engine written purely in C++.

##Open source
We make sure to make this library totally free--and that's free as in freedom and not just free beer. We license under the MIT license, and we make sure that all of your dependencies are MIT compatible libraries, so feel free to go out there and make millions.

##High-level to low-level control
Want to just get started quickly and get some `actor`s on the screen? No problem, gentlemanly_engine is for you. But what if you want to write your own custom shaders, with some complex rendering logic? No problem! Make your own [`shader_asset`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1shader__asset.html) and create your own [`actor`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1actor.html) with a custom [`render`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1actor.html#acfbb095d71e6348c57cc56d121a1b643) function. 

##Modern C++
Written entirely in modern C++, we use modern strategies like `std::shared_ptr`, `auto`, move semantics, etc to make the developing experience better.

##No large confusing hierarchies
We use the unix philosophy here and thing that each component should do one thing and do it well, so all of the classes are very simple but together they fit to make a well-oiled machine.

##Use of preexisting libraries
We don't think that you should ever have to reinvent the wheel, so we use lots of defaco standard libraries, like [GLM](https://github.com/g-truc/glm) for math, [Boost](http://www.boost.org) for filesystem and much more, [`nlohamn::json`](https://github.com/nlohmann/json) for json, etc.

##HTML5 support
Even though the build system support is pretty rudimentary for now, all of our libraries support the [`Emscripten`](https://kripken.github.io/emscripten-site/#) LLVM backend. See [the docs.](doc/COMPILING_WITH_EMSCRIPTEN.md)

##Extensible, powerful asset system
It is totally impractical to load all you assets (textures, models, animations, etc) by hand by hard-coding paths in your source code. The idea is `asset` classes create primitives like `shader`, `material`, `model`, etc using the asset system. More more information, see [the docs](doc/tutorial/asset.md). 
