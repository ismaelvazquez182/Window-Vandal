# Window-Vandal
x64 window title changing application for Windows Operating Systems.

![Screenshot](https://raw.githubusercontent.com/ismaelvazquez182/Window-Vandal/refs/heads/main/Window%20Vandal%20Screenshot.png)

### Dependency Information
Raylib (https://www.raylib.com/)
\
Raygui (https://github.com/raysan5/raygui)
\
(Recommended) VCPKG (https://github.com/microsoft/vcpkg)

### Installation Guide
1. Download and run the raylib installer from the raylib website.

2. Use vcpkg to integrate Raylib into your development environment.
```
git clone https://github.com/microsoft/vcpkg 
cd vcpkg 
.\bootstrap-vcpkg.bat 
.\vcpkg.exe integrate install
vcpkg install raylib:x64-windows
```
3. Download the raygui.h header file.
4. Place raylib.dll in the same path as your project.

I don't actually know if you need raylib installed. I have it for game programming but you might be able to get away with just compiling this using steps 3 and 4.

![Screenshot](https://raw.githubusercontent.com/ismaelvazquez182/Window-Vandal/refs/heads/main/Window%20Vandal%20Demo.gif)
