## Component core:
```cpp
#include "inputs.hpp"

namespace Haze
{
	class Component;
	struct Position;
	struct Scale;
	struct Velocity;
	struct Move;
	struct Health;
	struct Damage;
	struct Collision;
	struct Hitbox;
	struct LifeTime;
	struct OnKeyPressed;
	struct OnKeyReleased;
	struct OnMousePressed;
	struct OnMouseReleased;
	struct Hide;
}
```

```cpp 
struct Position : public Component
{
	Position(float x, float y) : x(x), y(y) {}
	float x;
	float y;
	std::string getType() const override { return "Position"; }
	void show() const override { std::cout << "Position: " << x << ", " << y << std::endl; }
};
```
`Position` is used to set the position of the entity

```cpp
struct Scale : public Component
{
	Scale(float x, float y) : x(x), y(y) {}
	float x;
	float y;
	std::string getType() const override { return "Scale"; }
	void show() const override { std::cout << "Scale: " << x << ", " << y << std::endl; }
};
```
`Scale` sets the scale of the entity. This is applied to the `Hitbox` 

```cpp
struct Velocity : public Component
{
	Velocity(float x, float y) : x(x), y(y) {}
	float x;
	float y;
	std::string getType() const override { return "Velocity"; }
	void show() const override { std::cout << "Velocity: " << x << ", " << y << std::endl; }
};
```
`Velocity` is the movement applied to the entity every frame

```cpp
struct Move : public Component
{
	Move(float x, float y) : x(x), y(y) {}
	float x;
	float y;
	std::string getType() const override { return "Move"; }
	void show() const override { std::cout << "Move: " << x << ", " << y << std::endl; }
};
```
`Move` is a movement applied only once to the entity, it is automatically destroyed after use

```cpp
struct Health : public Component
{
	Health(int health) : health(health) {}
	int health;
	std::string getType() const override { return "Health"; }
	void show() const override { std::cout << "Health: " << health << std::endl; }
};
```
`Health` can be use to setup the health of an entity

```cpp
struct Damage : public Component
{
	Damage(int damage) : damage(damage) {}
	int damage;
	std::string getType() const override { return "Damage"; }
	void show() const override { std::cout << "Damage: " << damage << std::endl; }
};
```
`Damage` can be used to setup the damage of an entity

```cpp
struct Collision : public Component
{
	enum CollisionType
	{
		NONE = 0,
		LAMBDA = 1,
		WALL = 2,
	};
	struct CollisionInfo
	{
		CollisionType type;
		double tics;
		std::function<void(int, int)> onCollision = [](int i, int j) {};
		std::chrono::time_point<std::chrono::high_resolution_clock> lastCollision = std::chrono::high_resolution_clock::now();
	};
	Collision(std::string scene, std::map<std::string, CollisionInfo> behavior)
	: scene(scene), behavior(behavior) {}
	  
	std::string scene;
	std::map<std::string, CollisionInfo> behavior;
	  
	std::string getType() const override { return "Collision"; }
	void show() const override { std::cout << "Collision: " << scene << std::endl; }
};
```
`Collision` is the component that will define the collision behavior of an entity.
It takes :
- a **scene** that will be use as an identification tag for a group of entity
- and a map of **behavior** that will define what happens on collision between two entity of certain scene.

```cpp
struct Hitbox : public Component
{
	struct intRect
	{
		int x;
		int y;
		int width;
		int height;
	};
	Hitbox(std::vector<intRect> hitbox) : hitbox(hitbox) {}
	std::vector<intRect> hitbox;
	std::string getType() const override { return "Hitbox"; }
	void show() const override { std::cout << "Hitbox: " << std::endl; }
};
```
`Hitbox` is used to set the hitbox of an entity
it is defined as a vector of `intRect` which allows to have a hitbox composed of multiples rectangles.

```cpp
struct LifeTime : public Component
{
	LifeTime(int lifeTime) : lifeTime(lifeTime) {}
	int lifeTime;
	int tics = 0;
	std::string getType() const override { return "LifeTime"; }
	void show() const override { std::cout << "LifeTime: " << lifeTime << std::endl; }
};
```
`LifeTime` can be used to set a lifetime limit for an entity
This lifetime is expressed in tics.

```cpp
struct OnKeyPressed : public Component
{
	OnKeyPressed(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}
	std::function<void(int, std::vector<InputType>)> callback;
	size_t player;
	std::string getType() const override {return "OnKeyPressed";}
	void show() const override { std::cout << "OnKeyPressed" << std::endl; }
};
```
`OnKeyPressed` can be used to set a **callback** to execute, with as an argument every simultaneous key pressed in the engine.
The `size_t` **player** is the id of the inputs.
The engine can have multiple list of inputs if used as a server.

```cpp
struct OnKeyReleased : public Component
{
	OnKeyReleased(std::function<void(int, std::vector<InputType>)> callback, size_t player = 0) : callback(callback), player(player) {}
	std::function<void(int, std::vector<InputType>)> callback;
	size_t player;
	std::string getType() const override{return "OnKeyReleased";}
	void show() const override { std::cout << "OnKeyReleased" << std::endl; }
};
```
`OnKeyReleased` can be used to set a **callback** to execute, with as an argument every simultaneous key released in the engine.
The `size_t` **player** is the id of the inputs.
The engine can have multiple list of inputs if used as a server.

```cpp
struct OnMousePressed : public Component
{
	OnMousePressed(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}
	std::function<void(int)> callback;
	size_t player;
	std::string getType() const override{return "OnMousePressed";}
	void show() const override { std::cout << "OnMousePressed" << std::endl; }
};
```
`OnMousePressed` can be used to set a **callback** to execute every time the mouse is pressed and is intersecting the **hitbox** of the entity.
The `size_t` **player** is the id of the inputs.
The engine can have multiple list of inputs if used as a server.

```cpp
struct OnMouseReleased : public Component
{
	OnMouseReleased(std::function<void(int)> callback, size_t player = 0) : callback(callback), player(player) {}
	std::function<void(int)> callback;
	size_t player;
	std::string getType() const override{return "OnMouseReleased";}
	void show() const override { std::cout << "OnMouseReleased" << std::endl; }
};
```
`OnMouseReleased` can be used to set a **callback** to execute every time the mouse is released and is intersecting the **hitbox** of the entity.
The `size_t` **player** is the id of the inputs.
The engine can have multiple list of inputs if used as a server.

```cpp
struct Hide : public Component
{
	Hide() {}
	std::string getType() const override { return "Hide"; }
	void show() const override { std::cout << "Hide" << std::endl; }
};
```
`Hide` is used to disable an entity.
When in this state, the entity in not displayed nor can receive inputs or move. 