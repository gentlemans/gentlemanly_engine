#Assets

##What is an asset?

Assets are just a streamlined way to load things from disk, like textures, shaders, or whatever you want. The system is designed to be very flexible and easy to make new assets.

##The [`asset_manager`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1asset__manager.html) Class

The class that manages all the loading and caching of assets is the `asset_manager` class It's very simple, if you aren't familiar check out [the docs](https://gentlemans.github.io/gentlemanly_engine/classge_1_1asset__manager.html).

##The [`Asset` Concept](https://gentlemans.github.io/gentlemanly_engine/structge_1_1concept_1_1Asset.html) 
Because assets aren't made with runtime polymorphism, they need to satisify a [Concept](http://www.boost.org/doc/libs/1_61_0/libs/concept_check/concept_check.htm). To check this, use
```C++
#include <ge/concept/asset.hpp>

....

BOOST_CONCEPT_ASSERT((ge::concept::Asset<my_asset_class>));
```

##Asset structure
Assets are just folders that have all the needed data for whatever is being loaded. The only part which is required is an `asset.json` file in that folder. For example, [shader_assets](https://gentlemans.github.io/gentlemanly_engine/classge_1_1shader__asset.html) has a file structure that looks like this:

```
myshader.shader/
 | asset.json
 | frag.glsl
 | vert.glsl
```

##Loading assets
Loading assets is as easy as acquiring a [`asset_manager`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1asset__manager.html) object, usually through a [`runtime`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html) object, then using the [`get_asset<>`](https://gentlemans.github.io/classge_1_1asset__manager.html#a2c93eaf5f2069a394a41cf973b3c8241) function:

```C++
#include <ge/asset_manager.hpp> 
#include <ge/mesh_asset.hpp>

....

auto& asset_man = m_runtime->m_asset_manager; // or something like this
auto mesh = asset_man.get_asset<ge::mesh_asset>("myfavoritemesh");

```

Once an asset has been loaded once successfully, it is cached and will not be loaded again, and `get_asset` will return a copy of the same `shared_ptr` object. 

##The `asset.json`  file
This file defines all the settings for your asset. Each asset has it's own specification living in it's documentation and C++ file. 

There is only one required field in `asset.json` files is the `asset_type` field. This field is checked by `asset_manager` to make sure it is the same as the string returned by the `asset_type` static function in asset classes. This is to avoid errors in asset loading classes that are due to user error. 

##Building your own asset

###Writing a JSON specification

When defining a new asset, it is helpful to first write an JSON asset specification. This way, it is possible for other developers to write assets without reading your entire implementation. A basic specification just has to include a example with descriptions of each field in the JSON. See [`texture_asset`](https://gentlemans.github.io/structge_1_1texture__asset.html#details) for a good simple example. 

###Writing the loader class

First, start by opening a new `struct` or `class`. This class is pretty much never going to be instantiated, so all of the functions are static. There are a few settings aliases that are needed so `asset_manager` knows how to load your class. 

####The  `loaded_type` alias
This is the type that is loaded. There is a intentional disconnect between the engine primitives and the loading classes because in general the primitives are more general than the loaders so people could theoretically write their own loaders easily. 

```C++
using loaded_type =  <your primitive type here>;
```

####The `asset_name` function
Because each `asset.json` file is required to have an `asset_type` field, it is required that assets provide a short name for their asset to be checked against the `asset.json` file. This should just be a static function that return a `const char*`:

```C++
static const char* asset_name() noexcept { return "material"; }
```

####The `load_asset` function
This is the function that does all the heavy lifting for loading assets. The signature is either:

```C++
static std::shared_ptr<loaded_type> load_asset(ge::asset_manager manager, const char* asset_name, const char* absolute_filepath, const  nlohmann::json& json_data);
```


