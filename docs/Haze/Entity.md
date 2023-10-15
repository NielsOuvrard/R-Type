## Name

`Haze::Core` - a class representing the entities used in the haze engine.

## Synopsis

```cpp
#include "Component.hpp"
namespace Haze {
	class Entity {
	public:
		Entity(ComponentList *componentList, size_t _id);
		~Entity();
		void addComponent(Component *component);
		void removeComponent(std::string type);
		Component *getComponent(std::string type);
		size_t getId() const { return _id; };

	private:
		size_t _id;
		ComponentList *_componentList;
	};
}
```

## Description

The purpose of the `Entity` class is to allow the user of Haze to manipulate the components of the system.

The concept of `Entity` in Haze is only an _id that points toward a list of components

## Methods

```cpp
void addComponent(Component *component);
```

`addComponent` is used to add a **component** to an **_entity**

```cpp
void removeComponent(std::string type);
```

`removeComponent` is used to remove a **component** from an **_entity**

```cpp
Component *getComponent(std::string type);
```

`getComponent` is used to get and modify a **component** of an **_entity**

```cpp
size_t getId() const { return _id; };
```

`getId` is used to get the _id of an **_entity**
