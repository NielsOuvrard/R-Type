#include "SfDisplay.hpp"

namespace Haze {
    static AssetManager<SfTexture> assetManager;

    SfSprite::SfSprite(std::string path)
    {
        _texture = assetManager.loadAsset(path);
        _sprite.setTexture(*_texture->getTexture());
    }

    void SfSprite::setPosition(int x, int y)
    {
        _sprite.setPosition(x, y);
    }

    void SfSprite::setScale(float x, float y)
    {
        _sprite.setScale(x, y);
    }

    void SfSprite::setOrigin(float x, float y)
    {
        _sprite.setOrigin(x, y);
    }

    void SfSprite::setRotation(float angle)
    {
        _sprite.setRotation(angle);
    }

    void SfSprite::setTextureRect(int x, int y, int width, int height)
    {
        _sprite.setTextureRect(sf::IntRect(x, y, width, height));
    }
}// namespace Haze

namespace Haze {

    ITexture *SfDisplay::createTexture(std::string path)
    {
        return new SfTexture(path);
    }

    ISprite *SfDisplay::createSprite(std::string path)
    {
        return new SfSprite(path);
    }

    IWindow *SfDisplay::createWindow(int width, int height, std::string title)
    {
        return new SfWindow(width, height, title);
    }

    IText *SfDisplay::createText(const std::string &text, IColor::colorEnum color, const std::string &fontname)
    {
        return new SfText(text, color, fontname);
    }

    IAudio *SfDisplay::createAudio(std::string path)
    {
        return new SfAudio(path);
    }

    IRect *SfDisplay::createRect(int x, int y, int width, int height, IColor::colorEnum color)
    {
        return new SfRect(x, y, width, height, color);
    }
}// namespace Haze

namespace Haze {
    SfAudioBuffer::SfAudioBuffer(std::string path)
    {
        if (!_buffer.loadFromFile(path))
            std::cerr << "Error: could not load audio" << std::endl;
    }
}// namespace Haze

namespace Haze {
    AssetManager<SfAudioBuffer> assetManagerAudioBuffer;
    SfAudio::SfAudio(std::string path)
    {
        _audioBuffer = assetManagerAudioBuffer.loadAsset(path);
        _sound.setBuffer(*_audioBuffer->getBuffer());
    }

    void SfAudio::play()
    {
        _sound.play();
    }

    void SfAudio::stop()
    {
        _sound.stop();
    }

    void SfAudio::setLoop(bool loop)
    {
        _sound.setLoop(loop);
    }

    bool SfAudio::isPlaying() const
    {
        return _sound.getStatus() == sf::Sound::Playing;
    }

    bool SfAudio::isStopped() const
    {
        return _sound.getStatus() == sf::Sound::Stopped;
    }
}// namespace Haze

namespace Haze {
    SfTexture::SfTexture(std::string path)
    {
        if (!_texture.loadFromFile(path))
            std::cerr << "Error: could not load texture" << std::endl;
    }
}// namespace Haze

namespace Haze {
    SfFont::SfFont(std::string path)
    {
        if (!_font.loadFromFile(path))
            std::cerr << "Error: could not load font" << std::endl;
        else
            std::cout << "Font loaded" << std::endl;
    }
}// namespace Haze

namespace Haze {
    SfWindow::SfWindow(int width, int height, std::string title)
    {
        _window.create(sf::VideoMode(width, height), title);
        _window.setKeyRepeatEnabled(true);
        _view.reset(sf::FloatRect(0, 0, width, height));
        _view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
        _window.setView(_view);
    }

    void SfWindow::clear()
    {
        _window.clear();
    }

    void SfWindow::display()
    {
        _window.display();
    }

    void SfWindow::draw(ISprite *sprite)
    {
        _window.draw(dynamic_cast<SfSprite *>(sprite)->getSprite());
    }

    void SfWindow::draw(IText *text)
    {
        _window.draw(dynamic_cast<SfText *>(text)->getText());
    }

    void SfWindow::draw(IRect *rect)
    {
        _window.draw(dynamic_cast<SfRect *>(rect)->getRect());
    }

    bool SfWindow::isOpen() const
    {
        return _window.isOpen();
    }

    void SfWindow::close()
    {
        if (_event.type == sf::Event::Closed)
            _window.close();
    }

    void SfWindow::fillKeyPressed(std::vector<Haze::InputType> *inputsPressed)
    {
        (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ? (inputsPressed->push_back(InputType::KEY_A)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) ? (inputsPressed->push_back(InputType::KEY_B)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) ? (inputsPressed->push_back(InputType::KEY_C)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ? (inputsPressed->push_back(InputType::KEY_D)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) ? (inputsPressed->push_back(InputType::KEY_E)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) ? (inputsPressed->push_back(InputType::KEY_F)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) ? (inputsPressed->push_back(InputType::KEY_G)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::H)) ? (inputsPressed->push_back(InputType::KEY_H)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) ? (inputsPressed->push_back(InputType::KEY_I)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) ? (inputsPressed->push_back(InputType::KEY_J)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) ? (inputsPressed->push_back(InputType::KEY_K)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) ? (inputsPressed->push_back(InputType::KEY_L)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) ? (inputsPressed->push_back(InputType::KEY_M)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) ? (inputsPressed->push_back(InputType::KEY_N)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) ? (inputsPressed->push_back(InputType::KEY_O)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) ? (inputsPressed->push_back(InputType::KEY_P)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) ? (inputsPressed->push_back(InputType::KEY_Q)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) ? (inputsPressed->push_back(InputType::KEY_R)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ? (inputsPressed->push_back(InputType::KEY_S)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) ? (inputsPressed->push_back(InputType::KEY_T)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) ? (inputsPressed->push_back(InputType::KEY_U)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::V)) ? (inputsPressed->push_back(InputType::KEY_V)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ? (inputsPressed->push_back(InputType::KEY_W)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) ? (inputsPressed->push_back(InputType::KEY_X)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) ? (inputsPressed->push_back(InputType::KEY_Y)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) ? (inputsPressed->push_back(InputType::KEY_Z)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) ? (inputsPressed->push_back(InputType::NUMKEY_0)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) ? (inputsPressed->push_back(InputType::NUMKEY_1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) ? (inputsPressed->push_back(InputType::NUMKEY_2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) ? (inputsPressed->push_back(InputType::NUMKEY_3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) ? (inputsPressed->push_back(InputType::NUMKEY_4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) ? (inputsPressed->push_back(InputType::NUMKEY_5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) ? (inputsPressed->push_back(InputType::NUMKEY_6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) ? (inputsPressed->push_back(InputType::NUMKEY_7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) ? (inputsPressed->push_back(InputType::NUMKEY_8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) ? (inputsPressed->push_back(InputType::NUMKEY_9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) ? (inputsPressed->push_back(InputType::KEY_ESC)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) ? (inputsPressed->push_back(InputType::KEY_ENTER_INPUT)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) ? (inputsPressed->push_back(InputType::KEY_BACK)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) ? (inputsPressed->push_back(InputType::KEY_TAB)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ? (inputsPressed->push_back(InputType::KEY_SPACE)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) ? (inputsPressed->push_back(InputType::KEY_F1)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) ? (inputsPressed->push_back(InputType::KEY_F2)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) ? (inputsPressed->push_back(InputType::KEY_F3)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) ? (inputsPressed->push_back(InputType::KEY_F4)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) ? (inputsPressed->push_back(InputType::KEY_F5)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F6)) ? (inputsPressed->push_back(InputType::KEY_F6)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F7)) ? (inputsPressed->push_back(InputType::KEY_F7)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F8)) ? (inputsPressed->push_back(InputType::KEY_F8)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F9)) ? (inputsPressed->push_back(InputType::KEY_F9)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F10)) ? (inputsPressed->push_back(InputType::KEY_F10)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) ? (inputsPressed->push_back(InputType::KEY_F11)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::F12)) ? (inputsPressed->push_back(InputType::KEY_F12)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ? (inputsPressed->push_back(InputType::KEY_UP_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ? (inputsPressed->push_back(InputType::KEY_DOWN_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ? (inputsPressed->push_back(InputType::KEY_LEFT_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ? (inputsPressed->push_back(InputType::KEY_RIGHT_ARROW)) : void();
        (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)) ? (inputsPressed->push_back(InputType::KEY_DOT)) : void();
    }

    void SfWindow::fillKeyReleased(std::vector<Haze::InputType> *inputsReleased)
    {
        if (_event.type == sf::Event::KeyReleased) {
            switch (_event.key.code) {
                case sf::Keyboard::A:
                    inputsReleased->push_back(InputType::KEY_A);
                    break;
                case sf::Keyboard::B:
                    inputsReleased->push_back(InputType::KEY_B);
                    break;
                case sf::Keyboard::C:
                    inputsReleased->push_back(InputType::KEY_C);
                    break;
                case sf::Keyboard::D:
                    inputsReleased->push_back(InputType::KEY_D);
                    break;
                case sf::Keyboard::E:
                    inputsReleased->push_back(InputType::KEY_E);
                    break;
                case sf::Keyboard::F:
                    inputsReleased->push_back(InputType::KEY_F);
                    break;
                case sf::Keyboard::G:
                    inputsReleased->push_back(InputType::KEY_G);
                    break;
                case sf::Keyboard::H:
                    inputsReleased->push_back(InputType::KEY_H);
                    break;
                case sf::Keyboard::I:
                    inputsReleased->push_back(InputType::KEY_I);
                    break;
                case sf::Keyboard::J:
                    inputsReleased->push_back(InputType::KEY_J);
                    break;
                case sf::Keyboard::K:
                    inputsReleased->push_back(InputType::KEY_K);
                    break;
                case sf::Keyboard::L:
                    inputsReleased->push_back(InputType::KEY_L);
                    break;
                case sf::Keyboard::M:
                    inputsReleased->push_back(InputType::KEY_M);
                    break;
                case sf::Keyboard::N:
                    inputsReleased->push_back(InputType::KEY_N);
                    break;
                case sf::Keyboard::O:
                    inputsReleased->push_back(InputType::KEY_O);
                    break;
                case sf::Keyboard::P:
                    inputsReleased->push_back(InputType::KEY_P);
                    break;
                case sf::Keyboard::Q:
                    inputsReleased->push_back(InputType::KEY_Q);
                    break;
                case sf::Keyboard::R:
                    inputsReleased->push_back(InputType::KEY_R);
                    break;
                case sf::Keyboard::S:
                    inputsReleased->push_back(InputType::KEY_S);
                    break;
                case sf::Keyboard::T:
                    inputsReleased->push_back(InputType::KEY_T);
                    break;
                case sf::Keyboard::U:
                    inputsReleased->push_back(InputType::KEY_U);
                    break;
                case sf::Keyboard::V:
                    inputsReleased->push_back(InputType::KEY_V);
                    break;
                case sf::Keyboard::W:
                    inputsReleased->push_back(InputType::KEY_W);
                    break;
                case sf::Keyboard::X:
                    inputsReleased->push_back(InputType::KEY_X);
                    break;
                case sf::Keyboard::Y:
                    inputsReleased->push_back(InputType::KEY_Y);
                    break;
                case sf::Keyboard::Z:
                    inputsReleased->push_back(InputType::KEY_Z);
                    break;
                case sf::Keyboard::Num0:
                    inputsReleased->push_back(InputType::NUMKEY_0);
                    break;
                case sf::Keyboard::Num1:
                    inputsReleased->push_back(InputType::NUMKEY_1);
                    break;
                case sf::Keyboard::Num2:
                    inputsReleased->push_back(InputType::NUMKEY_2);
                    break;
                case sf::Keyboard::Num3:
                    inputsReleased->push_back(InputType::NUMKEY_3);
                    break;
                case sf::Keyboard::Num4:
                    inputsReleased->push_back(InputType::NUMKEY_4);
                    break;
                case sf::Keyboard::Num5:
                    inputsReleased->push_back(InputType::NUMKEY_5);
                    break;
                case sf::Keyboard::Num6:
                    inputsReleased->push_back(InputType::NUMKEY_6);
                    break;
                case sf::Keyboard::Num7:
                    inputsReleased->push_back(InputType::NUMKEY_7);
                    break;
                case sf::Keyboard::Num8:
                    inputsReleased->push_back(InputType::NUMKEY_8);
                    break;
                case sf::Keyboard::Num9:
                    inputsReleased->push_back(InputType::NUMKEY_9);
                    break;
                case sf::Keyboard::Escape:
                    inputsReleased->push_back(InputType::KEY_ESC);
                    break;
                case sf::Keyboard::Enter:
                    inputsReleased->push_back(InputType::KEY_ENTER_INPUT);
                    break;
                case sf::Keyboard::Backspace:
                    inputsReleased->push_back(InputType::KEY_BACK);
                    break;
                case sf::Keyboard::Tab:
                    inputsReleased->push_back(InputType::KEY_TAB);
                    break;
                case sf::Keyboard::Space:
                    inputsReleased->push_back(InputType::KEY_SPACE);
                    break;
                case sf::Keyboard::F1:
                    inputsReleased->push_back(InputType::KEY_F1);
                    break;
                case sf::Keyboard::F2:
                    inputsReleased->push_back(InputType::KEY_F2);
                    break;
                case sf::Keyboard::F3:
                    inputsReleased->push_back(InputType::KEY_F3);
                    break;
                case sf::Keyboard::F4:
                    inputsReleased->push_back(InputType::KEY_F4);
                    break;
                case sf::Keyboard::F5:
                    inputsReleased->push_back(InputType::KEY_F5);
                    break;
                case sf::Keyboard::F6:
                    inputsReleased->push_back(InputType::KEY_F6);
                    break;
                case sf::Keyboard::F7:
                    inputsReleased->push_back(InputType::KEY_F7);
                    break;
                case sf::Keyboard::F8:
                    inputsReleased->push_back(InputType::KEY_F8);
                    break;
                case sf::Keyboard::F9:
                    inputsReleased->push_back(InputType::KEY_F9);
                    break;
                case sf::Keyboard::F10:
                    inputsReleased->push_back(InputType::KEY_F10);
                    break;
                case sf::Keyboard::F11:
                    inputsReleased->push_back(InputType::KEY_F11);
                    break;
                case sf::Keyboard::F12:
                    inputsReleased->push_back(InputType::KEY_F12);
                    break;
                case sf::Keyboard::Up:
                    inputsReleased->push_back(InputType::KEY_UP_ARROW);
                    break;
                case sf::Keyboard::Down:
                    inputsReleased->push_back(InputType::KEY_DOWN_ARROW);
                    break;
                case sf::Keyboard::Left:
                    inputsReleased->push_back(InputType::KEY_LEFT_ARROW);
                    break;
                case sf::Keyboard::Right:
                    inputsReleased->push_back(InputType::KEY_RIGHT_ARROW);
                    break;
                case sf::Keyboard::Period:
                    inputsReleased->push_back(InputType::KEY_DOT);
                    break;
                default:
                    break;
            }
        }
    }

    void SfWindow::fillMousePressed(Haze::MouseType *mouseType)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            *mouseType = PRESSED;
        }
    }

    void SfWindow::fillMouseReleased(Haze::MouseType *mouseType)
    {
        if (_event.type == sf::Event::MouseButtonReleased) {
            *mouseType = RELEASED;
        }
    }

    void SfWindow::fillFocus(bool *focus)
    {
        if (_event.type == sf::Event::GainedFocus)
            *focus = true;
        if (_event.type == sf::Event::LostFocus)
            *focus = false;
    }

    void SfWindow::fillMousePosition(int *x, int *y)
    {
        *x = (int) _window.mapPixelToCoords(sf::Mouse::getPosition(_window)).x;
        *y = (int) _window.mapPixelToCoords(sf::Mouse::getPosition(_window)).y;
    }

    bool SfWindow::pollEvent()
    {
        return _window.pollEvent(_event);
    }
}// namespace Haze

namespace Haze {
    sf::Color SfColor::getColor(colorEnum color)
    {
        switch (color) {
            case RED:
                return sf::Color::Red;
            case GREEN:
                return sf::Color::Green;
            case BLUE:
                return sf::Color::Blue;
            case YELLOW:
                return sf::Color::Yellow;
            case MAGENTA:
                return sf::Color::Magenta;
            case CYAN:
                return sf::Color::Cyan;
            case WHITE:
                return sf::Color::White;
            case BLACK:
                return sf::Color::Black;
            case TRANSPARENT:
                return sf::Color::Transparent;
            default:
                return sf::Color::White;
        }
    }

    sf::Color SfColor::getColor(int r, int g, int b, int a)
    {
        return sf::Color(r, g, b, a);
    }
}// namespace Haze

namespace Haze {
    static AssetManager<SfFont> assetManagerFont;

    SfText::SfText(const std::string &text, IColor::colorEnum color, std::string path)
    {
        _font = assetManagerFont.loadAsset("assets/fonts/" + path);
        _text.setFont(*_font->getFont());
        _text.setString(text);
        _text.setFillColor(SfColor::getColor(color));
    }

    void SfText::setPosition(int x, int y)
    {
        _text.setPosition(x, y);
    }

    void SfText::setScale(float x, float y)
    {
        _text.setScale(x, y);
    }

    void SfText::setString(std::string string)
    {
        _text.setString(string);
    }

    void SfText::setColor(IColor::colorEnum color)
    {
        _text.setFillColor(SfColor::getColor(color));
    }

    void SfText::setColor(int r, int g, int b, int a)
    {
        _text.setFillColor(SfColor::getColor(r, g, b, a));
    }

    // void SfText::setFont(IFont *font)
    // {
    //     _text.setFont(*dynamic_cast<SfFont *>(font)->getFont());
    // }
}// namespace Haze

namespace Haze {
    SfRect::SfRect(int x, int y, int width, int height, IColor::colorEnum color)
    {
        _rect.setPosition(x, y);
        _rect.setSize(sf::Vector2f(width, height));
        _rect.setFillColor(SfColor::getColor(color));
    }

    void SfRect::setPosition(int x, int y)
    {
        _rect.setPosition(x, y);
    }

    void SfRect::setSize(int width, int height)
    {
        _rect.setSize(sf::Vector2f(width, height));
    }

    void SfRect::setFillColor(IColor::colorEnum color)
    {
        _rect.setFillColor(SfColor::getColor(color));
    }

    void SfRect::setOutlineColor(IColor::colorEnum color)
    {
        _rect.setOutlineColor(SfColor::getColor(color));
    }

    void SfRect::setOutlineThickness(float thickness)
    {
        _rect.setOutlineThickness(thickness);
    }
}// namespace Haze

Haze::IDisplay *createDisplay()
{
    return new Haze::SfDisplay();
}
