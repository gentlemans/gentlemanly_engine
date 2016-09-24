#Tutorial 02: Actors

The  [`actor`](https://gentlemans.github.com/gentlemanly_engine/classge_1_1actor.html) class is a generic class, that is placable in the world. All actors have a positition, rotation, scale, and can have a parent or children. 

##Actor Parenting
Parenting actors is effectively attaching them. All child actors will rotate around the parent, move with it, and scale with it.  

> TODO: find image

##Spawning actors
You cannot just use `operator new` to spawn an actor, but it's almost as easy. Just use the 