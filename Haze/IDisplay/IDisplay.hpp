#pragma once
#include "inputs.hpp"
#include <vector>
#include <string>

namespace Haze
{
    class ISprite;
    class ITexture;
    class IText;
    class IAudio;
    class IWindow;
    class IRect;
    class IColor;
}

namespace Haze
{
    class ISprite
    {
    private:
    public:
        virtual ~ISprite() = default;
        virtual void setPosition(int x, int y) = 0;
        virtual void setScale(float x, float y) = 0;
        virtual void setOrigin(float x, float y) = 0;
        virtual void setRotation(float angle) = 0;
        virtual void setTextureRect(int x, int y, int width, int height) = 0;
    };

    class ITexture
    {
    private:
    public:
        virtual ~ITexture() = default;
    };

    class IText
    {
    private:
    public:
        virtual ~IText() = default;
        virtual void setPosition(int x, int y) = 0;
        virtual void setScale(float x, float y) = 0;
        virtual void setString(std::string string) = 0;
    };

    class IAudio
    {
    private:
    public:
        virtual ~IAudio() = default;
        virtual void play() = 0;
        virtual void stop() = 0;
        virtual void setLoop(bool loop) = 0;
        virtual bool isPlaying() const = 0;
        virtual bool isStopped() const = 0;
    };

    class IWindow
    {
    private:
    public:
        virtual ~IWindow() = default;
        virtual void clear() = 0;
        virtual void display() = 0;
        virtual void draw(ISprite *sprite) = 0;
        virtual void draw(IText *text) = 0;
        virtual void draw(IRect *rect) = 0;
        virtual bool isOpen() const = 0;
        virtual void close() = 0;
        virtual void fillKeyPressed(std::vector<Haze::InputType> *inputsPressed) = 0;
        virtual void fillKeyReleased(std::vector<Haze::InputType> *inputsReleased) = 0;
        virtual void fillMousePressed(Haze::MouseType *mouseType) = 0;
        virtual void fillMouseReleased(Haze::MouseType *mouseType) = 0;
        virtual void fillFocus(bool *focus) = 0;
        virtual void fillMousePosition(int *x, int *y) = 0;
        virtual bool pollEvent() = 0;
    };

    class IRect
    {
    private:
    public:
        virtual ~IRect() = default;
        virtual void setPosition(int x, int y) = 0;
        virtual void setSize(int width, int height) = 0;
    };

    class IColor
    {
    private:
    public:
        virtual ~IColor() = default;
    };
}