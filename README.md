# K9ngine v1

K9ngine v1 is a C++ game engine composed of several Visual Studio projects. The engine is an experimental playground for rendering, asset management and game development.

## Projects

- **K9ngineCore** – core engine library containing math utilities, resource management and world objects.
- **K9ngineApp** – Windows application shell that hosts the engine and provides a runtime environment.
- **K9GameApp** – sample game built on top of the engine to demonstrate usage.
- **Game** – lightweight project stub used for experimentation.
- **K9ngineCore_Test** – unit tests targeting the core engine components.
- **K9ngineApp_Tests** – tests for the application layer.
- **K9ngine_v1_editor** – C# asset editor for creating and modifying resources.
- **Doc** – Doxygen configuration and generated documentation for the engine.
- **OpenGL** and **glad.c** – third‑party dependencies and loaders for OpenGL.

## Building

Open `K9ngine_v1.sln` in Visual Studio 2022 or later. Choose the desired configuration (Debug/Release) and build the solution. Tests can be built and executed from Visual Studio as part of the solution.

## Documentation

A Doxygen configuration is provided at `Doc/K9ngineCoreDoxyFile`. Run the following from the repository root to generate HTML documentation:

```bash
doxygen Doc/K9ngineCoreDoxyFile
```

## License

This project does not currently specify a license.

