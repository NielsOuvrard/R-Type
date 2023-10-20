#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

namespace Haze
{
    class SfTexture;
    class SfSprite;
    class SfWindow;
    class SfText;
    class SfColor;
}

namespace Haze
{
    class SfTexture : public ITexture
    {
    private:
        sf::Texture _texture;
    public:
        SfTexture(std::string path);
        ~SfTexture() = default;
        sf::Texture *getTexture() { return &_texture; }
    };

    class SfSprite : public ISprite
    {
    private:
        sf::Sprite _sprite;
        std::shared_ptr<SfTexture> _texture;
    public:
        SfSprite(std::string path);
        ~SfSprite() = default;
        void setPosition(int x, int y) override;
        void setScale(float x, float y) override;
        void setOrigin(float x, float y) override;
        void setRotation(float angle) override;
        void setTextureRect(int x, int y, int width, int height) override;
        sf::Sprite getSprite() const { return _sprite; }
    };

    class SfWindow : public IWindow
    {
    private:
        sf::RenderWindow _window;
        sf::View _view;
        sf::Event _event;

    public:
        SfWindow(int width, int height, std::string title);
        ~SfWindow() = default;
        void clear() override;
        void display() override;
        void draw(ISprite *sprite) override;
        void draw(IText *text) override;
        void draw(IRect *rect) override;
        bool isOpen() const override;
        void close() override;
        void fillKeyPressed(std::vector<Haze::InputType> *inputsPressed) override;
        void fillKeyReleased(std::vector<Haze::InputType> *inputsReleased) override;
        void fillMousePressed(Haze::MouseType *mouseType) override;
        void fillMouseReleased(Haze::MouseType *mouseType) override;
        void fillFocus(bool *focus) override;
        void fillMousePosition(int *x, int *y) override;
        bool pollEvent() override;
    };

    class SfColor : public IColor
    {
    public:
        enum colorEnum {
            RED,
            GREEN,
            BLUE,
            YELLOW,
            BLACK,
            WHITE,
            MAGENTA,
            CYAN,
            TRANSPARENT,
            COLOR_COUNT
        };
    private:
        sf::Color _color;
    public:
        ~SfColor() = default;
        static sf::Color getColor(colorEnum ccolor);
    };

    class SfText : public IText
    {
    private:
        sf::Text _text;
        sf::Font _font;
    public:
        SfText(const std::string &text, SfColor::colorEnum color, const std::string &fontname = "arial.ttf");
        ~SfText() = default;
        void setPosition(int x, int y) override;
        void setColor(SfColor::colorEnum color);
        sf::Text getText() const { return _text; }
        void setString(std::string string) override;
        void setScale(float x, float y) override;
    };

    class SfRect : public IRect
    {
    private:
        sf::RectangleShape _rect;
    public:
        SfRect(int x, int y, int width, int height, SfColor::colorEnum color);
        ~SfRect() = default;
        sf::RectangleShape getRect() const { return _rect; }
        void setPosition(int x, int y) override;
        void setSize(int width, int height) override;
        void setFillColor(SfColor::colorEnum color);
        void setOutlineColor(SfColor::colorEnum color);
        void setOutlineThickness(float thickness);
    };
}
