#include "AssetManager.hpp"
#include "IDisplay.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

extern "C" {
    Haze::IDisplay *createDisplay();
}

namespace Haze {
    class SfTexture;
    class SfSprite;
    class SfWindow;
    class SfText;
    class SfColor;
    class SfAudioBuffer;
    class SfAudio;
    class SfRect;
    class SfFont;
    class SfDisplay;
}// namespace Haze

namespace Haze {
    class SfDisplay : public IDisplay {
    private:
    public:
        SfDisplay() = default;
        ~SfDisplay() = default;
        ITexture *createTexture(std::string path) override;
        ISprite *createSprite(std::string path) override;
        IWindow *createWindow(int width, int height, std::string title) override;
        IText *createText(const std::string &text, IColor::colorEnum color, const std::string &fontname = "arial.ttf") override;
        IAudio *createAudio(std::string path) override;
        IRect *createRect(int x, int y, int width, int height, IColor::colorEnum color) override;
    };
}// namespace Haze

namespace Haze {
    class SfAudio : public IAudio {
    private:
        std::shared_ptr<SfAudioBuffer> _audioBuffer;
        sf::Sound _sound;

    public:
        SfAudio(std::string path);
        ~SfAudio() = default;
        void play() override;
        void stop() override;
        void setLoop(bool loop) override;
        bool isPlaying() const override;
        bool isStopped() const override;
    };

    class SfAudioBuffer : public IAudioBuffer {
    private:
        sf::SoundBuffer _buffer;

    public:
        SfAudioBuffer(std::string path);
        ~SfAudioBuffer() = default;
        sf::SoundBuffer *getBuffer() { return &_buffer; }
    };

    class SfTexture : public ITexture {
    private:
        sf::Texture _texture;

    public:
        SfTexture(std::string path);
        ~SfTexture() = default;

        sf::Texture *getTexture() { return &_texture; }
    };

    class SfSprite : public ISprite {
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

    class SfWindow : public IWindow {
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

    class SfColor : public IColor {
    private:
        sf::Color _color;

    public:
        ~SfColor() = default;
        static sf::Color getColor(colorEnum color);
        static sf::Color getColor(int r, int g, int b, int a);
    };

    class SfText : public IText {
    private:
        sf::Text _text;
        std::shared_ptr<SfFont> _font;

    public:
        SfText(const std::string &text, IColor::colorEnum color, std::string path = "arial.ttf");
        ~SfText() = default;
        void setPosition(int x, int y) override;
        void setColor(IColor::colorEnum color) override;
        void setColor(int r, int g, int b, int a) override;
        void setString(std::string string) override;
        void setScale(float x, float y) override;
        // void setFont(IFont *font) override;

        sf::Text getText() const { return _text; }
    };

    class SfFont : public IFont {
    private:
        sf::Font _font;
    public:
        SfFont(std::string path = "arial.ttf");
        ~SfFont() = default;
        sf::Font *getFont() { return &_font; }
    };

    class SfRect : public IRect {
    private:
        sf::RectangleShape _rect;

    public:
        SfRect(int x, int y, int width, int height, IColor::colorEnum color);
        ~SfRect() = default;

        sf::RectangleShape getRect() const { return _rect; }

        void setPosition(int x, int y) override;
        void setSize(int width, int height) override;
        void setFillColor(IColor::colorEnum color) override;
        void setOutlineColor(IColor::colorEnum color) override;
        void setOutlineThickness(float thickness) override;
    };
}// namespace Haze
