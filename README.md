
# **SFML + ImGui** CMake Project

This project demonstrates the use of ImGui and SFML for creating graphical user interfaces in C++.

## Prerequisites

Before you begin, ensure you have the following installed:

- **C++ Compiler**: (e.g., GCC, Clang, MSVC). 
   Download [Visual Studio Build Tools 17 2022][1]
- **CMake**: from 3.12 version.
   Download [CMake](https://cmake.org/download/). Add its path. 

## Compilation

1. **Clone the Repository**:
   ```bash
   git clone -recursive https://github.com/tlchoque/gateway.git 
   ```
2. ```bash
   cd gateway
   ```

3. ```bash
   cmake --preset "win-base"
   ```

4. ```bash
   cmake --build ./build
   ```
  Finally look for Editor.exe within build/Debug folder

 
[1]: https://aka.ms/vs/17/release/vs_BuildTools.exe 
