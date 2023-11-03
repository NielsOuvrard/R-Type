## Component graphics:
```cpp
#include "Component.hpp"
#include "inputs.hpp"
namespace Haze
{
	struct Sprite;
	struct Animation;
	struct Window;
	struct HitboxDisplay;
	struct Text;
}
```

```cpp
struct Sprite : public Component
{
	Sprite(std::string path) : path(path)
	{
		std::cout << "path " << path << std::endl;
		texture.loadFromFile(path);
		sprite.setTexture(texture);
	}
	std::string path;
	sf::Sprite sprite;
	sf::Texture texture;
	std::string getType() const override{return "Sprite";}
	void show() const override { std::cout << "flm" << path << std::endl; }
};
```
`Sprite` is used to set a sprite with a texture to an entity.
It just takes a **path** for the texture.

```cpp
struct Animation : public Component
{
	enum AnimationType
	{
		LOOP,
		BOOMERANG,
		ONCE
	};
	struct intRect
	{
		int x;
		int y;
		int width;
		int height;
	};
	Animation(std::vector<intRect> frames, AnimationType type, bool direction, double tics) : frames(frames), type(type), tics(tics), direction(direction) {}
	std::vector<intRect> frames;
	AnimationType type = AnimationType::LOOP;
	double tics;
	size_t currentFrame = 0;
	bool direction = true;
	std::chrono::time_point<std::chrono::high_resolution_clock> lastAnimation = std::chrono::high_resolution_clock::now();
	std::string getType() const override { return "Animation"; }
	void show() const override { std::cout << "Animation: " << std::endl; }
};
```
`Animation` is the component that will define how a sprite is animated.
It takes:
- a **vector** of `IntRect` that will define the position and the size of every frame of the animation
- an `AnimationType` that will define id the animation is a `LOOP`, a `BOOMERANG` or simply a static image (note that you can still have multiple frames and change by hand the `currentFrame`)
- a **direction** that will define the direction of the animation (**1** for left to right and **2** for right to left).
- and a **tics** that will set the time between the updates of the animation.

```cpp
struct Window : public Component
{
	Window(int width, int height) : width(width), height(height)
	{
		window.create(sf::VideoMode(width, height), "R-Type");
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(true);
		view.reset(sf::FloatRect(0, 0, width, height));
		view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
		window.setView(view);
	}
	int width;
	int height;
	sf::RenderWindow window;
	sf::View view;
	sf::Event event;
	std::string getType() const override{return "Window";}
	void show() const override { std::cout << "Window: " << width << ", " << height << std::endl; }
};
```
`Window` is the component that can set the window for your game.
A **strong advice** is that the entity who has the component window doesn't have any other component. 

```cpp
struct HitboxDisplay : public Component
{
	HitboxDisplay()
	{
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(5);
	}
	sf::Color color = sf::Color::Red;
	sf::RectangleShape rect;
	  
	std::string getType() const override{return "HitboxDisplay";}
	void show() const override { std::cout << "HitboxDisplay: " << std::endl; }
};
```
`HitboxDisplay` is a debug tool to see the `Hitbox` of your entity

```cpp
struct Text : public Component {
	Text(const std::string &text, sf::Color color, const std::string &fontname = "arial.ttf") : text(text), color(color) {
		font.loadFromFile("../assets/fonts/" + fontname);
		textObj.setFont(font);
		textObj.setString(text);
		textObj.setFillColor(color);
	}
	std::string text;
	sf::Color color;
	sf::Font font;
	sf::Text textObj;
	std::string getType() const override {return "Text";}
	void show() const override { std::cout << "Text: " << text << std::endl; }
};
```
`Text` is used to create a text component to your entity.
It takes:
- the **text** you want to display
- a **color**
- and a **font name**