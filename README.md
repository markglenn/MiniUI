



# MiniUI

A small XML/Lua-driven UI framework aimed at embedded devices, rendered with
OpenGL and SDL.

<video src="https://github.com/user-attachments/assets/244c27db-537f-4901-a13e-e17a26352bcb" controls muted width="640">
  Your browser does not support the video tag —
  <a href="docs/demo.mp4">download the demo</a> instead.
</video>

> **2026 update:** the 2007-era code in this repository was modernized in
> April 2026 with the help of an AI coding assistant so it builds and runs
> on current macOS. The change set is limited to what was needed to get the
> project compiling and linking again — the runtime design, XML/Lua schema,
> widget system, and demo applications are unchanged from the original.
>
> Summary of modernization changes:
> - Replaced the SCons build with a single top-level `CMakeLists.txt`.
> - Swapped the abandoned `sdl_image` package for a vendored copy of
>   [`stb_image`](https://github.com/nothings/stb) (used only by
>   `OpenGLRenderer/ResourceLoader.cpp`).
> - SDL 1.2 API is now satisfied by `sdl12-compat` layered on top of SDL2.
> - Patched the vendored luabind 0.7 to compile against Boost 1.89 and
>   C++17 (explicit preprocessor includes, `std::auto_ptr` →
>   `std::unique_ptr`, obsolete ADL workarounds removed,
>   `boost::placeholders` handling, etc.).
> - Conditional `<OpenGL/gl.h>` / `<GL/gl.h>` includes so the code is
>   portable to macOS's framework path.
> - Incidental C++17 cleanups (`register` keyword, a couple of
>   `char*` → `const char*` for `strchr`).

## About this project

MiniUI was my graduate design project for my Master's in Software Engineering
at **DePaul University**. At the time I was working at **Motorola**, in an
R&D group in the mobile devices division, and the project was motivated by
the class of problems that showed up there: building rich, themable user
interfaces for embedded hardware without dragging in a full desktop UI
toolkit.

The goals were:

- **Declarative layout.** Screens are described in XML so that designers
  can iterate without touching C++.
- **Skinnable.** Widget appearance (layout regions, source images, slicing)
  is separated from per-screen layout via a `skin.xml` / `skin.lua` pair.
- **Scriptable behaviour.** Per-widget logic — animations, hover effects,
  list selection, etc. — is written in Lua and dispatched from the native
  widget core through luabind.
- **Small, portable runtime.** A handful of static libraries (Lua, luabind,
  an OpenGL renderer, an SDL input layer, and the MiniUI core) link into
  one binary with no desktop-UI dependencies.

The full graduate design report is archived alongside the code:
[`docs/MiniUI-thesis.pdf`](docs/MiniUI-thesis.pdf).

## Repository layout

```
Lua/                — vendored Lua 5.1 interpreter
luabind/            — vendored luabind 0.7 (C++ ↔ Lua glue)
include/luabind/    — luabind public headers
MiniUI/             — core library: widgets, animation, XML/XPath,
                      Lua system, UI manager, graphics, event system
OpenGLRenderer/     — OpenGL-backed renderer + image resource loader
SDLInput/           — SDL input manager
src/                — executable entry point, application shell,
                      demo applications (MainMenu, PhoneBook, ImageViewer)
third_party/        — vendored third-party headers (stb_image)
build/              — runtime assets (ui/, test.xml) — the built
                      executable is dropped here at link time
```

## Building

Requires CMake ≥ 3.20, a C++17 compiler, and Homebrew packages
`sdl12-compat` and `boost`.

```sh
brew install cmake sdl12-compat boost
cmake -S . -B cmake-build
cmake --build cmake-build -j
```

The binary lands in `build/miniui`, alongside the runtime assets.

## Running

```sh
cd build && ./miniui
```

The demo opens with a `MainMenu` screen; clicking **Phonebook** or
**Imageviewer** transitions into the corresponding sub-application.

## Demo applications

- **MainMenu** — sliding, fading entry screen showing the two demos.
- **PhoneBook** — a scrollable contact list with per-entry detail view,
  demonstrating the `SelectableList` widget and inter-screen navigation.
- **ImageViewer** — a fading slideshow with hover-revealed chrome,
  demonstrating the animation system and image loading.

## License

Original project source headers reference the LGPL 2.1+. Third-party
components retain their own licenses: Lua (MIT), luabind (MIT),
stb_image (public domain / MIT).
