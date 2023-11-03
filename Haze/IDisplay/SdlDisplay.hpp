#include "IDisplay.hpp"
#include <iostream>
#include <memory>
#include "AssetManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>


extern "C" {
    Haze::IDisplay *createDisplay();
}

namespace Haze
{
    class SdlTexture;
    class SdlSprite;
    class SdlWindow;
    class SdlText;
    class SdlColor;
    class SdlIAudio;
    class SdlRect;
    class SdlDisplay;
}

namespace Haze
{
    class SdlDisplay : public IDisplay
    {
    private:
    public:
        SdlDisplay() = default;
        ~SdlDisplay() = default;
        ITexture *createTexture(std::string path) override;
        ISprite *createSprite(std::string path) override;
        IWindow *createWindow(int width, int height, std::string title) override;
        IText *createText(const std::string &text, IColor::colorEnum color, const std::string &fontname = "arial.ttf") override;
        IAudio *createAudio(std::string path) override;
        IRect *createRect(int x, int y, int width, int height, IColor::colorEnum color) override;
    };
}

namespace Haze
{
    class SdlAudio : public IAudio
    {
    private:
        Mix_Chunk *_sound;
        int _channel;
    public:
        SdlAudio(std::string path);
        ~SdlAudio() = default;
        void play() override;
        void stop() override;
        void setLoop(bool loop) override;
        bool isPlaying() const override;
        bool isStopped() const override;
    };

    class SdlTexture : public ITexture
    {
    private:
        SDL_Texture *_texture;
    public:
        SdlTexture(std::string path);
        ~SdlTexture() = default;
        SDL_Texture *getTexture() const;
    };

    class SdlSprite : public ISprite
    {
    private:
        std::shared_ptr<SdlTexture> _texture;
        SDL_Rect _rect;
        SDL_Rect _textureRect;
        float _scaleX = 1;
        float _scaleY = 1;
        float originX = 0;
        float originY = 0;
    public:
        SdlSprite(std::string path);
        ~SdlSprite() = default;
        void setPosition(int x, int y) override;
        void setScale(float x, float y) override;
        void setRotation(float angle) override;
        void setOrigin(float x, float y) override;
        void setTextureRect(int x, int y, int width, int height) override;
        SDL_Rect *getRect();
        SDL_Texture *getTexture();
    };

    class SdlWindow : public IWindow
    {
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
    public:
        SdlWindow(int width, int height, std::string title);
        ~SdlWindow() = default;
        void clear() override;
        void display() override;
        void draw(ISprite *sprite) override;
        void draw(IText *text) override;
        void draw(IRect *rect) override;
        bool isOpen() const override;
        SDL_Renderer *getRenderer() const;
    };

    class SdlText : public IText
    {
    private:
        SDL_Texture *_texture;
        SDL_Rect _rect;
        std::string _text;
        std::string _fontname;
        int _size;
        IColor::colorEnum _color;
    public:
        SdlText(const std::string &text, IColor::colorEnum color, const std::string &fontname = "arial.ttf");
        ~SdlText() = default;
        void setPosition(int x, int y) override;
        void setScale(float x, float y) override;
        void setString(std::string string) override;
        void setColor(IColor::colorEnum color) override;
        void setColor(int r, int g, int b, int a) override;
        SDL_Texture *getTexture() const;
        SDL_Rect *getRect();
    };

    class SdlColor : public IColor
    {
    private:
        SDL_Color _color;
    public:
        ~SdlColor() = default;
        static SDL_Color getColor(colorEnum color);
        static SDL_Color getColor(int r, int g, int b, int a);
    };

    class SdlRect : public IRect
    {
    private:
        SDL_Rect _rect;
        SDL_Color _color;
    public:
        SdlRect(int x, int y, int width, int height, IColor::colorEnum color);
        ~SdlRect() = default;
        SDL_Rect *getRect();
        SDL_Color getColor();
    };
}