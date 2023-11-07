# R-Type Documentation

The R-Type project aims at developing a clone of the classic side-scrolling shoot 'em up arcade game called "R-Type."
The project involves creating a server that will start the game, and a client that will be able to display the game.
This version of R-Type is multiplayer and the game is developed using a custom engine of our own called Haze.

## Prerequisites

Before you begin, ensure you have met the following requirements:

- cmake
- git

## 🚀 Getting Started

To install and launch R-Type, follow these steps:

1. Clone the github project

```
git clone https://github.com/votre-utilisateur/haze-engine.git
```

2. Download the dependenties

> ## Linux/MacOS
> ```
> git clone https://github.com/Microsoft/vcpkg.git
> ./vcpkg/bootstrap-vcpkg.sh
> ./vcpkg/vcpkg install
> ```

> ## Windows
> ```
> git clone https://github.com/Microsoft/vcpkg.git
> .\vcpkg\bootstrap-vcpkg.bat
> .\vcpkg\vcpkg install
> ```

> [!warning]
> These commands must be executed at the root of this project

3. Create the build directory

```
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake
```

4. Compile the project

```
cmake --build build
```

5. Execute the binaries
```
./build/r-type-server
```
```
./build/r-type-client [sfml/sdl]
```

## 📋 Documentation

[Haze introduction](https://rclovis.github.io/R-Type-Documentation/)

[Game Engine](https://rclovis.github.io/R-Type-Documentation/Haze/Getting%20Started/)

[Protocol](https://rclovis.github.io/R-Type-Documentation/Protocol/Protocol/)

[Rtype](https://rclovis.github.io/R-Type-Documentation/Rtype/Create%20Enemy/)

## 👤 Credits

Click on the images below to visit the GitHub profiles of our awesome contributors:

<div style="display: flex; justify-content: space-between;">
    <a href="https://github.com/EstusSipper">
        <img src="https://media.licdn.com/dms/image/C4E03AQF6AIitN8q7cg/profile-displayphoto-shrink_400_400/0/1651531289334?e=1703721600&v=beta&t=nCsDz0wBgls-nLvLAzpAZqELOfTItPVJtoWJwRtmSGk" width="150" height="150">
    </a>
    <a href="https://github.com/rclovis">
        <img src="https://avatars.githubusercontent.com/u/91875893?v=4" width="150" height="150">
    </a>
    <a href="https://github.com/NielsOuvrard">
        <img src="https://avatars.githubusercontent.com/u/91876336?v=4" width="150" height="150">
    </a>
    <a href="https://github.com/CorentinFortes">
        <img src="https://avatars.githubusercontent.com/u/91876233?v=4" width="150" height="150">
    </a>
    <a href="https://github.com/AngeloZhou22">
        <img src="https://avatars.githubusercontent.com/u/91876442?s=400&u=e17541db376ba488505351104ee598772dbe67a2&v=4" width="150" height="150">
    </a>
</div>

## 🛠️ Tools

[![Built with CMake](https://img.shields.io/badge/Built%20with-CMake-1f425f.svg)](https://cmake.org/) [![Made with C++](https://img.shields.io/badge/Made%20with-C%2B%2B-9683EC.svg)](https://en.cppreference.com/w/cpp/17) [![Made with SFML](https://img.shields.io/badge/Made%20with-SFML-009688.svg)](https://www.sfml-dev.org/) [![Made with SDL2](https://img.shields.io/badge/Made%20with-SDL2-orange.svg)](https://libsdl.org/) [![Made with ASIO](https://img.shields.io/badge/Made%20with-ASIO-yellow.svg)](https://think-async.com/Asio/) [![Made with Vcpkg](https://img.shields.io/badge/Made%20with-Vcpkg-7056bf.svg)](https://vcpkg.io/)
[![Linux](https://img.shields.io/badge/Linux-Supported-brightgreen.svg)](https://www.linux.org/) [![Windows](https://img.shields.io/badge/Windows-Supported-brightgreen.svg)](https://www.microsoft.com/en-us/windows) [![macOS](https://img.shields.io/badge/macOS-Supported-brightgreen.svg)](https://www.apple.com/macos) [![Documentation](https://img.shields.io/badge/Documentation-Yes-brightgreen.svg)](https://rclovis.github.io/R-Type-Documentation/)
