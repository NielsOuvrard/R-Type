## Name

`Haze::Engine` - a the main engine class.

## Synopsis

```cpp
#include "Entity.hpp"
#include "ComponentList.hpp"
#include "IPipeline.hpp"
#include "protocol.hpp"

namespace Haze
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		void init();
		void update();
		Entity *createEntity();
		Entity *getEntity(size_t _id);
		void removeEntity(size_t _id);
		void removeEntity(Entity *_entity);
		bool isOpen();
		void setInfoInputs(info_inputs info, size_t _id);
		ComponentList *getComponentList();
		std::vector<info_inputs> *getInfoInputs();

	private:
		std::vector<std::unique_ptr<Entity>> _entities;
		std::vector<std::unique_ptr<IPipeline>> _pipelines;
		ComponentList *_componentList;
		std::vector<info_inputs> _infoInputs;
	};
}
```

## Description

The purpose of the `Engine` class is to encapsulate the entire Haze ecosystem so it can be easily used and extended.

## Methods

```cpp
void init();
```

`init` is used just after the creation of the **engine** and and is used to setup everything in the class

```cpp
void update();
```

`update` is used to compute one tic of the game. It launches every [[Pipelines]] in the engine

```cpp
Entity *createEntity();
```

`createEntity` is used to add an **_entity** to the engine

```cpp
Entity *getEntity(size_t _id);
```

`getEntity` is used to get an **_entity** from the engine. Returns `nullptr` if the _entity doesn't exits.

```cpp
void removeEntity(size_t _id);
void removeEntity(Entity *_entity);
```

`removeEntity` deletes an **_entity** from the engine

```cpp
bool isOpen();
```

`isOpen` tells if the engine is still running

```cpp
void setInfoInputs(info_inputs info, size_t _id);
```

`setInfoInputs` is used to simulate input into the engine. Useful if the engine is running without **`haze-graphics`**
in a server. It takes an info_inputs defined at [[Protocol]] and an _id which is the number of the Player how has sent
this input.

> [!warning]
> Here _id 0 is where is stored the global inputs.
> It is filled automatically by the `pullEvent` system from **haze-graphics**
> If you are not taking inputs from other players you should not use this method.

```cpp
ComponentList *getComponentList();
```

`getComponentList` gives the `ComponentList` of the program *(mainly internal use)**

```cpp
std::vector<info_inputs> *getInfoInputs();
```

`getInfoInputs` gives the list of all of the inputs registered in the engine  *(mainly internal use)**
