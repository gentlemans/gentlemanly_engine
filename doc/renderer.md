#Renderer classes
The renderer defines a lot of classes, and their names aren't super intuitive at first, but they are very simple. 

##[`shader`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1shader.html)
A shader just represents a GLSL shader. This shader exposes parameters that are set (by the material). These are not movable and not copyable because shaders are expensive to compile. This can be thought of as the general type of rendering on a material, like textured, solid color, etc.


##[`material`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1material.html) 
A material is one level of abstraction above a shader, and it's whole purpose is to set parameters that the shader exposes. For example, all textured assets share the same shader, but will have different materials to set which texture is used. Materials are meant to be stored as a raw object because they are small and easily copyable. 

##[`mesh`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1mesh.html)
A mesh defines the raw verticies (location, texture coordinates, etc) of a mesh. This isn't a copyable or movable class because there is no point in copying it or moving it, just share it using a `shared_ptr`

##[`mesh_settings`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1mesh_settings.html)
The [`mesh_settings`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1mesh__settings.html) object just holds a material and a `shared_ptr` to a mesh, combining them. This is the highest level of rendering object, and is passed to [`mesh_actor`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1mesh__actor.html) to create something that can actually be drawn on the screen. 
