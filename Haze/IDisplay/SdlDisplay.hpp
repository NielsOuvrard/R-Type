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
    class SdlAudioBuffer;
    class SdlAudio;
    class SdlRect;
    class SdlFont;
    class SdlDisplay;
}

namespace Haze
{
    class SdlDisplay : public IDisplay
    {
    private:
    public:
        SdlDisplay();
        ~SdlDisplay();
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
        std::shared_ptr<SdlAudioBuffer> _audioBuffer;
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

    class SdlAudioBuffer : public IAudioBuffer
    {
    private:
        Mix_Chunk *_buffer;
    public:
        SdlAudioBuffer(std::string path);
        ~SdlAudioBuffer() = default;
        Mix_Chunk *getBuffer() { return _buffer; }
    };

    class SdlTexture : public ITexture
    {
    private:
        SDL_Texture *_texture;
    public:
        SdlTexture(std::string path);
        ~SdlTexture() = default;
        SDL_Texture *getTexture() { return _texture; }
    };

    class SdlSprite : public ISprite
    {
    private:
        std::shared_ptr<SdlTexture> _texture;
        SDL_Rect _srcRect = {0, 0, 0, 0};
        SDL_Rect _destRect = {0, 0, 0, 0};
        SDL_Point _origin = {0, 0};
        float _scaleX = 1;
        float _scaleY = 1;
        float _angle = 0;
        bool _flipX = false;
        bool _flipY = false;
    public:
        SdlSprite(std::string path);
        ~SdlSprite() = default;
        void setPosition(int x, int y) override;
        void setScale(float x, float y) override;
        void setRotation(float angle) override;
        void setOrigin(float x, float y) override;
        void setTextureRect(int x, int y, int width, int height) override;
        SDL_Rect *getDestRect() { return &_destRect; }
        SDL_Rect *getSrcRect() { return &_srcRect; }
        SDL_Texture *getTexture() { return _texture->getTexture(); }
        SDL_Point *getOrigin() { return &_origin; }
        float getAngle() { return _angle; }
        float getScaleX() { return _scaleX; }
        float getScaleY() { return _scaleY; }
        bool getFlipX() { return _flipX; }
        bool getFlipY() { return _flipY; }
    };

    class SdlWindow : public IWindow
    {
    private:
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        bool _closed = false;
    public:
        SdlWindow(int width, int height, std::string title);
        ~SdlWindow() = default;
        void clear() override;
        void display() override;
        void draw(ISprite *sprite) override;
        void draw(IText *text) override;
        void draw(IRect *rect) override;
        bool isOpen() const override;
        void close() override;
        void fillKeyPressed(std::vector<InputType> *inputsPressed) override;
        void fillKeyReleased(std::vector<InputType> *inputsReleased) override;
        void fillMousePressed(MouseType *mouseType) override;
        void fillMouseReleased(MouseType *mouseType) override;
        void fillFocus(bool *focus) override;
        void fillMousePosition(int *x, int *y) override;
        bool pollEvent() override;
    };

    class SdlText : public IText
    {
    private:
        std::shared_ptr<SdlFont> _font;
        SDL_Texture *_texture;
        SDL_Rect _rect = {0, 0, 0, 0};
        std::string _string;
        SDL_Color _color;
        float _scaleX = 1;
        float _scaleY = 1;
    public:
        SdlText(const std::string &text, IColor::colorEnum color, std::string path = "arial.ttf");
        ~SdlText() = default;
        void setPosition(int x, int y) override;
        void setColor(IColor::colorEnum color) override;
        void setColor(int r, int g, int b, int a) override;
        void setString(std::string string) override;
        void setScale(float x, float y) override;
        SDL_Texture *getTexture() { return _texture; }
        SDL_Rect *getRect() { return &_rect; }
        float getScaleX() { return _scaleX; }
        float getScaleY() { return _scaleY; }
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
        SDL_Rect _rect = {0, 0, 0, 0};
        SDL_Color _fillColor;
        SDL_Color _outlineColor;
        float _outlineThickness;
    public:
        SdlRect(int x, int y, int width, int height, IColor::colorEnum color);
        ~SdlRect() = default;
        void setPosition(int x, int y) override;
        void setSize(int width, int height) override;
        void setFillColor(IColor::colorEnum color) override;
        void setOutlineColor(IColor::colorEnum color) override;
        void setOutlineThickness(float thickness) override;
        SDL_Rect *getRect() { return &_rect; }
        SDL_Color getFillColor() { return _fillColor; }
        SDL_Color getOutlineColor() { return _outlineColor; }
        float getOutlineThickness() { return _outlineThickness; }
    };

    class SdlFont : public IFont
    {
    private:
        TTF_Font *_font;
    public:
        SdlFont(std::string path = "arial.ttf");
        ~SdlFont() = default;
        TTF_Font *getFont() { return _font; }
    };
}