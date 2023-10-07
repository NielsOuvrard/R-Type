
## Name

`Haze::Core` - a class representing the entities used in the haze engine. 

## Synopsys

```cpp
#include "Component.hpp"
namespace Haze {
	class Entity {
		public:
			Entity();
			~Entity();
			void setComponentList(ComponentList *componentList);
			void setId(size_t id);
			void addComponent(Component *component);
			void removeComponent(std::string type);
			Component *getComponent(std::string type);
			void showComponents();
			size_t getId() const { return _id; };

		private:
			size_t _id;
			ComponentList *_componentList;
	};
}
```

## Description
Their purpose of the `Entity` class is to encapsulate a vector of **Components** that will define an element in the engine.

