# GameEngine
A basic game engine (which has been scrapped and re-started due to improved knowledge base: https://github.com/jcnast/EngineCore)

This was the start of a game engine using FreeGlut and OpenGL (with the GLM math library). The main goal of this was to learn
the in-depth details of how things go in, and primarily learn the basics of the rendering pipeline. In this regard, it succeded.

Due to this brief project, I have a better understanding of the various pieces that go into a game engine (albeit a bare-bones one).
However, as I progressed I was not happy with the starting path due to it being centered around getting this working and building
a functional knowledge base on which to progress.

I was able to progress to the point where I had a functional camera (could move/position it anywhere and the models would adjust),
and some really basic sprite and model rendering. Although reading the images was not working 100% correctly.
As I was starting on writing a collision system, I noticed how connected things were and that I was programming myself into a rather
deep hole.

So, given my new knowledge an experience since starting this, I have decided to restart (see https://github.com/jcnast/EngineCore), and build it in a much more dynamic and
flexible way. For more details on this, please see the new reposity - however I am leaving this here as a window into what I was going
about learning, and to compare with the new start.

I have also decided that the next iteration will have SDL2 as a basis as I am much more familiar with it, and I would rather rely on a
single external library than several (as would have been the case here).
