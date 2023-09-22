# Haze Engine Documentation

The Haze Engine is a game engine built on top of the Simple and Fast Multimedia Library (SFML).
It provides an interface for creating 2D games and multimedia applications optimized for desktop computers.

## Getting Started

To get started with the Haze Engine, follow these steps:

1. Include the necessary header files:


2. Create an instance of the Haze::Engine class:
```cpp
Haze::Engine engine;
```

1. Initialize the engine:
```cpp
engine.init();
```

3. Create entities using the Haze::Entity class:
```cpp
Haze::Entity *entity1 = engine.createEntity();
Haze::Entity *entity2 = engine.createEntity();
```

3. Add components to the entities. Here are some examples:
Add a Haze::Position component:

```cpp
entity1->addComponent(new Haze::Position(0, 0));
```
Add a Haze::Sprite component:

```cpp
entity1->addComponent(new Haze::Sprite("assets/ship.png"));
```
Add a Haze::Animation component:

```cpp
entity1->addComponent(new Haze::Animation("assets/r-typesheet30a.gif", 34, 34, 3, 1));
```
Add a Haze::Window component:

```cpp
entity2->addComponent(new Haze::Window(800, 600));
```
Start the game loop by checking if the engine is open:

```cpp
while (engine.isOpen())
{
    engine.update();
}
```

## Components
**Haze::Position**
The **Haze::Position** component represents the position of an entity in the game world. It takes two arguments: the X and Y coordinates.

**Haze::Sprite**
The **Haze::Sprite** component allows you to display a sprite for an entity. It takes the path to the sprite image as an argument.

**Haze::Animation**
The **Haze::Animation** component enables you to create animations for entities. It takes the following arguments:

The **Haze::Window** component is used to create a window for your game. It takes the width and height of the window as arguments.

## Example Usage
Here's an example of how to use the Haze Engine to create a simple game loop:

```cpp
#include <Haze>

int main()
{
    Haze::Engine engine;
    engine.init();

    Haze::Entity *entity1 = engine.createEntity();
    Haze::Entity *entity2 = engine.createEntity();

    entity1->addComponent(new Haze::Position(0, 0));
    entity1->addComponent(new Haze::Sprite("assets/ship.png"));
    entity1->addComponent(new Haze::Animation("assets/r-typesheet30a.gif", 34, 34, 3, 1));

    entity2->addComponent(new Haze::Window(800, 600));

    while (engine.isOpen())
    {
        engine.update();
    }

    return 0;
}
```
