#Asset Creation

##What is an asset?

Assets are just a streamlined way to load things from disk, like textures, shaders, or whatever you want. The system is designed to be very flexible and easy to make new assets.

##The `asset_manager` class

The class that manages all the loading and caching of assets is the asset_manager class (ge/asset_manager.hpp). It is very simple, there are only three notable functions:

###`add_asset_path(std::string path, uint_8 priority = 0)`

Adds a search path for assets, with the priority given. 255 is the highest priority and 0 is the lowest


