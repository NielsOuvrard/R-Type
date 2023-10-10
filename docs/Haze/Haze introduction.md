> [!abstract] Haze for
> **H**aze
> **A**tomic
> **Z**izi
> **E**ngine
## Getting Started
To get started with the Haze Engine, follow these steps:

1. Include the necessary header files:
```cpp
#include <haze-core>
#include <haze-graphics> //Only if you want to display something
```

2. Create an instance of the Haze::Engine class:
```cpp
Haze::Engine engine;
```

3. Initialize the engine:
```cpp
engine.init();
```

4. Create entities using the Haze::Entity class:
```cpp
Haze::Entity *entity1 = engine.createEntity();
Haze::Entity *entity2 = engine.createEntity();
```

5. Add components to the entities. Here are some examples:
```cpp
//Add a Haze::Position component:
entity1->addComponent(new Haze::Position(0, 0));

//Add a Haze::Sprite component:
entity1->addComponent(new Haze::Sprite("assets/ship.png"));

//Add a Haze::Animation component:
entity1->addComponent(new Haze::Animation("assets/r-typesheet30a.gif", 34, 34, 3, 1));

//Add a Haze::Window component:
entity2->addComponent(new Haze::Window(800, 600));
```

6. Start the game loop by checking if the engine is open:
```cpp
while (engine.isOpen())
{
    engine.update();
}
```

## Components
Component of the **haze-core** lib are at:
[[Component]]

Component of the **haze-graphics** lib are at:
[[ComponentGfx]]

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