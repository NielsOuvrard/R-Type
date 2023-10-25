# R-Type Documentation
The R-Type project aims at developing a clone of the classic side-scrolling shoot 'em up arcade game called "R-Type." The project involves creating a server that will run the game, and a client that will be able to display the game. This version of R-Type is multiplayer and the game is developed using a custom engine of our own called Haze.

## Prerequisites
Before you begin, ensure you have met the following requirements:
- SFML
- Asio

## Getting Started
To install and launch R-Type, follow these steps:

1. Clone the github project
```
git clone https://github.com/votre-utilisateur/haze-engine.git
```

2. Create the build directory
```
cmake -S . -B build
```

3. Compile the project
```
cmake --build build
```

4. Execute the binaries
Server:
```
./build/r-type-server
```

Client:
```
./build/r-type-client
```

## Doc
[[How to use]]
[[Protocol/Protocol]]
