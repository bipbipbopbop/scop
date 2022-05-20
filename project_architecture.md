# Project Architecture

- A OBJParser class that parse the 3D elements and feed it to the SceneMaker
- A SceneMaker class that will populate the scene with 3D objects
- A Renderer class that will use the 3D rendering library(-ies?) to render the scene
- (maybe) A Window class that will print out the rendered result

---

### OBJParser class
- Parse the .obj file
- Follow a standard for the obj object in the program
- nothing else ??

### SceneMaker class
- Transform a obj object in a "scene" format
- a scene is the raw data of the elements to render
  - Must be compatible with the Renderer, maybe included in the renderer ?
  - Maybe the raw data part is in the renderer, and the SceneMaker is just a program-level abstraction to populate the scene

### Renderer class
- Feed scene data to the 3D library
- return the render result (a 2D picture)
- I'd like to use at least 2 renderer (vulkan & OpenGL). Let's do a dynamic thing, nibbler-style (or maybe no dynamic libary because that sucks)

### Window class
- basically print out a 2D picture
- Decorelated from the Renderer for ease of use (SoC!!)