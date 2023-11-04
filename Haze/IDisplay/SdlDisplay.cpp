#include "SdlDisplay.hpp"


Haze::IDisplay *createDisplay()
{
    return new Haze::SdlDisplay();
}

namespace Haze
{
    static SDL_Renderer *renderer = nullptr;
    static int Width = 800;
    static int Height = 600;
}

namespace Haze
{
    SdlTexture::SdlTexture(std::string path)
    {
        _texture = IMG_LoadTexture(renderer, path.c_str());
        if (_texture == nullptr)
            std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

namespace Haze
{
    static AssetManager<SdlTexture> assetManager;
    SdlSprite::SdlSprite(std::string path)
    {
        _texture = assetManager.loadAsset(path);
        SDL_QueryTexture(_texture->getTexture(), NULL, NULL, &_srcRect.w, &_srcRect.h);
    }

    void SdlSprite::setPosition(int x, int y)
    {
        _destRect.x = x;
        _destRect.y = y;
    }

    void SdlSprite::setScale(float x, float y)
    {
        if (x < 0) {
            _flipX = true;
            x *= -1;
        }
        if (y < 0) {
            _flipY = true;
            y *= -1;
        }
        _scaleX = x;
        _scaleY = y;
    }

    void SdlSprite::setOrigin(float x, float y)
    {
        _origin.x = x;
        _origin.y = y;
    }

    void SdlSprite::setRotation(float angle)
    {
        _angle = angle;
    }

    void SdlSprite::setTextureRect(int x, int y, int width, int height)
    {
        _srcRect.x = x;
        _srcRect.y = y;
        _srcRect.w = width;
        _srcRect.h = height;
    }
}

namespace Haze
{
    AssetManager<SdlAudioBuffer> audioBufferManager;
    SdlAudio::SdlAudio(std::string path)
    {
        _audioBuffer = audioBufferManager.loadAsset(path);
        _channel = -1;
    }

    void SdlAudio::play()
    {
        _channel = Mix_PlayChannel(-1, _audioBuffer->getBuffer(), 0);
    }

    void SdlAudio::stop()
    {
        Mix_HaltChannel(_channel);
    }

    void SdlAudio::setLoop(bool loop)
    {
        if (loop)
            Mix_PlayChannel(-1, _audioBuffer->getBuffer(), -1);
    }

    bool SdlAudio::isPlaying() const
    {
        return Mix_Playing(_channel);
    }

    bool SdlAudio::isStopped() const
    {
        return Mix_Paused(_channel);
    }
}

namespace Haze
{
    SdlAudioBuffer::SdlAudioBuffer(std::string path)
    {
        _buffer = Mix_LoadWAV(path.c_str());
        if (_buffer == nullptr)
            std::cout << "Error: " << SDL_GetError() << std::endl;
    }
}

namespace Haze
{
    SdlWindow::SdlWindow(int width, int height, std::string title)
    {
        Width = width;
        Height = height;
        _window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        _renderer = renderer;
        _event = SDL_Event();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
        SDL_RenderSetLogicalSize(renderer, width, height);
        SDL_SetWindowResizable(_window, SDL_TRUE);
        SDL_SetWindowMinimumSize(_window, 800, 600);
        SDL_SetWindowMaximumSize(_window, 1920, 1080);
        SDL_GetWindowSize(_window, &width, &height);
    }

    void SdlWindow::clear()
    {
        SDL_RenderClear(renderer);
    }

    void SdlWindow::display()
    {
        SDL_RenderPresent(renderer);
    }

    void SdlWindow::draw(ISprite *sprite)
    {
        SdlSprite *sdlSprite = dynamic_cast<SdlSprite *>(sprite);
        sdlSprite->getDestRect()->w = sdlSprite->getSrcRect()->w * sdlSprite->getScaleX();
        sdlSprite->getDestRect()->h = sdlSprite->getSrcRect()->h * sdlSprite->getScaleY();
        int flip = SDL_FLIP_NONE;
        SDL_Rect tmpDestRect = *sdlSprite->getDestRect();
        tmpDestRect.x = sdlSprite->getDestRect()->x;
        tmpDestRect.y = sdlSprite->getDestRect()->y;
        tmpDestRect.w = sdlSprite->getDestRect()->w;
        tmpDestRect.h = sdlSprite->getDestRect()->h;
        if (sdlSprite->getFlipX() && sdlSprite->getFlipY()) {
            flip = SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
            tmpDestRect.x = sdlSprite->getDestRect()->x - sdlSprite->getDestRect()->w;
            tmpDestRect.y = sdlSprite->getDestRect()->y - sdlSprite->getDestRect()->h;
        } else if (sdlSprite->getFlipX()) {
            flip = SDL_FLIP_HORIZONTAL;
            tmpDestRect.x = sdlSprite->getDestRect()->x - sdlSprite->getDestRect()->w;
        } else if (sdlSprite->getFlipY()) {
            flip = SDL_FLIP_VERTICAL;
            tmpDestRect.y = sdlSprite->getDestRect()->y - sdlSprite->getDestRect()->h;
        }
        if (SDL_RenderCopyEx(renderer, sdlSprite->getTexture(), sdlSprite->getSrcRect(), &tmpDestRect, sdlSprite->getAngle(), sdlSprite->getOrigin(), SDL_RendererFlip(flip)) != 0)
            std::cout << "Error: " << SDL_GetError() << std::endl;
    }

    void SdlWindow::draw(IRect *rect)
    {
        SdlRect *sdlRect = dynamic_cast<SdlRect *>(rect);
        SDL_SetRenderDrawColor(renderer, sdlRect->getFillColor().r, sdlRect->getFillColor().g, sdlRect->getFillColor().b, sdlRect->getFillColor().a);
        SDL_RenderFillRect(renderer, sdlRect->getRect());
        SDL_SetRenderDrawColor(renderer, sdlRect->getOutlineColor().r, sdlRect->getOutlineColor().g, sdlRect->getOutlineColor().b, sdlRect->getOutlineColor().a);
        SDL_RenderDrawRect(renderer, sdlRect->getRect());
    }

    void SdlWindow::draw(IText *text)
    {
        SdlText *sdlText = dynamic_cast<SdlText *>(text);
        SDL_RenderCopy(renderer, sdlText->getTexture(), NULL, sdlText->getRect());
    }

    bool SdlWindow::isOpen() const
    {
        if (_closed) {
            return false;
        }
        return true;
    }

    void SdlWindow::close()
    {
        if (_event.type == SDL_QUIT) {
            SDL_DestroyWindow(_window);
            _closed = true;
        }
    }

    void SdlWindow::fillKeyPressed(std::vector<InputType> *inputsPressed)
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        (keystate[SDL_SCANCODE_A]) ? inputsPressed->push_back(InputType::KEY_Q) : void();
        (keystate[SDL_SCANCODE_B]) ? inputsPressed->push_back(InputType::KEY_B) : void();
        (keystate[SDL_SCANCODE_C]) ? inputsPressed->push_back(InputType::KEY_C) : void();
        (keystate[SDL_SCANCODE_D]) ? inputsPressed->push_back(InputType::KEY_D) : void();
        (keystate[SDL_SCANCODE_E]) ? inputsPressed->push_back(InputType::KEY_E) : void();
        (keystate[SDL_SCANCODE_F]) ? inputsPressed->push_back(InputType::KEY_F) : void();
        (keystate[SDL_SCANCODE_G]) ? inputsPressed->push_back(InputType::KEY_G) : void();
        (keystate[SDL_SCANCODE_H]) ? inputsPressed->push_back(InputType::KEY_H) : void();
        (keystate[SDL_SCANCODE_I]) ? inputsPressed->push_back(InputType::KEY_I) : void();
        (keystate[SDL_SCANCODE_J]) ? inputsPressed->push_back(InputType::KEY_J) : void();
        (keystate[SDL_SCANCODE_K]) ? inputsPressed->push_back(InputType::KEY_K) : void();
        (keystate[SDL_SCANCODE_L]) ? inputsPressed->push_back(InputType::KEY_L) : void();
        (keystate[SDL_SCANCODE_SEMICOLON]) ? inputsPressed->push_back(InputType::KEY_M) : void();
        (keystate[SDL_SCANCODE_N]) ? inputsPressed->push_back(InputType::KEY_N) : void();
        (keystate[SDL_SCANCODE_O]) ? inputsPressed->push_back(InputType::KEY_O) : void();
        (keystate[SDL_SCANCODE_P]) ? inputsPressed->push_back(InputType::KEY_P) : void();
        (keystate[SDL_SCANCODE_Q]) ? inputsPressed->push_back(InputType::KEY_A) : void();
        (keystate[SDL_SCANCODE_R]) ? inputsPressed->push_back(InputType::KEY_R) : void();
        (keystate[SDL_SCANCODE_S]) ? inputsPressed->push_back(InputType::KEY_S) : void();
        (keystate[SDL_SCANCODE_T]) ? inputsPressed->push_back(InputType::KEY_T) : void();
        (keystate[SDL_SCANCODE_U]) ? inputsPressed->push_back(InputType::KEY_U) : void();
        (keystate[SDL_SCANCODE_V]) ? inputsPressed->push_back(InputType::KEY_V) : void();
        (keystate[SDL_SCANCODE_W]) ? inputsPressed->push_back(InputType::KEY_Z) : void();
        (keystate[SDL_SCANCODE_X]) ? inputsPressed->push_back(InputType::KEY_X) : void();
        (keystate[SDL_SCANCODE_Y]) ? inputsPressed->push_back(InputType::KEY_Y) : void();
        (keystate[SDL_SCANCODE_Z]) ? inputsPressed->push_back(InputType::KEY_W) : void();
        (keystate[SDL_SCANCODE_0]) ? inputsPressed->push_back(InputType::NUMKEY_0) : void();
        (keystate[SDL_SCANCODE_1]) ? inputsPressed->push_back(InputType::NUMKEY_1) : void();
        (keystate[SDL_SCANCODE_2]) ? inputsPressed->push_back(InputType::NUMKEY_2) : void();
        (keystate[SDL_SCANCODE_3]) ? inputsPressed->push_back(InputType::NUMKEY_3) : void();
        (keystate[SDL_SCANCODE_4]) ? inputsPressed->push_back(InputType::NUMKEY_4) : void();
        (keystate[SDL_SCANCODE_5]) ? inputsPressed->push_back(InputType::NUMKEY_5) : void();
        (keystate[SDL_SCANCODE_6]) ? inputsPressed->push_back(InputType::NUMKEY_6) : void();
        (keystate[SDL_SCANCODE_7]) ? inputsPressed->push_back(InputType::NUMKEY_7) : void();
        (keystate[SDL_SCANCODE_8]) ? inputsPressed->push_back(InputType::NUMKEY_8) : void();
        (keystate[SDL_SCANCODE_9]) ? inputsPressed->push_back(InputType::NUMKEY_9) : void();
        (keystate[SDL_SCANCODE_ESCAPE]) ? inputsPressed->push_back(InputType::KEY_ESC) : void();
        (keystate[SDL_SCANCODE_KP_ENTER]) ? inputsPressed->push_back(InputType::KEY_ENTER_INPUT) : void();
        (keystate[SDL_SCANCODE_RETURN]) ? inputsPressed->push_back(InputType::KEY_ENTER_INPUT) : void();
        (keystate[SDL_SCANCODE_SPACE]) ? inputsPressed->push_back(InputType::KEY_SPACE) : void();
        (keystate[SDL_SCANCODE_BACKSPACE]) ? inputsPressed->push_back(InputType::KEY_BACK) : void();
        (keystate[SDL_SCANCODE_TAB]) ? inputsPressed->push_back(InputType::KEY_TAB) : void();
        (keystate[SDL_SCANCODE_UP]) ? inputsPressed->push_back(InputType::KEY_UP_ARROW) : void();
        (keystate[SDL_SCANCODE_DOWN]) ? inputsPressed->push_back(InputType::KEY_DOWN_ARROW) : void();
        (keystate[SDL_SCANCODE_LEFT]) ? inputsPressed->push_back(InputType::KEY_LEFT_ARROW) : void();
        (keystate[SDL_SCANCODE_RIGHT]) ? inputsPressed->push_back(InputType::KEY_RIGHT_ARROW) : void();
        (keystate[SDL_SCANCODE_F1]) ? inputsPressed->push_back(InputType::KEY_F1) : void();
        (keystate[SDL_SCANCODE_F2]) ? inputsPressed->push_back(InputType::KEY_F2) : void();
        (keystate[SDL_SCANCODE_F3]) ? inputsPressed->push_back(InputType::KEY_F3) : void();
        (keystate[SDL_SCANCODE_F4]) ? inputsPressed->push_back(InputType::KEY_F4) : void();
        (keystate[SDL_SCANCODE_F5]) ? inputsPressed->push_back(InputType::KEY_F5) : void();
        (keystate[SDL_SCANCODE_F6]) ? inputsPressed->push_back(InputType::KEY_F6) : void();
        (keystate[SDL_SCANCODE_F7]) ? inputsPressed->push_back(InputType::KEY_F7) : void();
        (keystate[SDL_SCANCODE_F8]) ? inputsPressed->push_back(InputType::KEY_F8) : void();
        (keystate[SDL_SCANCODE_F9]) ? inputsPressed->push_back(InputType::KEY_F9) : void();
        (keystate[SDL_SCANCODE_F10]) ? inputsPressed->push_back(InputType::KEY_F10) : void();
        (keystate[SDL_SCANCODE_F11]) ? inputsPressed->push_back(InputType::KEY_F11) : void();
        (keystate[SDL_SCANCODE_F12]) ? inputsPressed->push_back(InputType::KEY_F12) : void();
        (keystate[SDL_SCANCODE_PERIOD]) ? inputsPressed->push_back(InputType::KEY_DOT) : void();
    }

    void SdlWindow::fillKeyReleased(std::vector<InputType> *inputsReleased)
    {
        if (_event.type == SDL_KEYUP)
        {
            std::cout << "UPPPP" << std::endl;
            switch (_event.key.keysym.sym)
            {
            case SDLK_a:
                inputsReleased->push_back(Haze::InputType::KEY_A);
                break;
            case SDLK_b:
                inputsReleased->push_back(Haze::InputType::KEY_B);
                break;
            case SDLK_c:
                inputsReleased->push_back(Haze::InputType::KEY_C);
                break;
            case SDLK_d:
                inputsReleased->push_back(Haze::InputType::KEY_D);
                break;
            case SDLK_e:
                inputsReleased->push_back(Haze::InputType::KEY_E);
                break;
            case SDLK_f:
                inputsReleased->push_back(Haze::InputType::KEY_F);
                break;
            case SDLK_g:
                inputsReleased->push_back(Haze::InputType::KEY_G);
                break;
            case SDLK_h:
                inputsReleased->push_back(Haze::InputType::KEY_H);
                break;
            case SDLK_i:
                inputsReleased->push_back(Haze::InputType::KEY_I);
                break;
            case SDLK_j:
                inputsReleased->push_back(Haze::InputType::KEY_J);
                break;
            case SDLK_k:
                inputsReleased->push_back(Haze::InputType::KEY_K);
                break;
            case SDLK_l:
                inputsReleased->push_back(Haze::InputType::KEY_L);
                break;
            case SDLK_m:
                inputsReleased->push_back(Haze::InputType::KEY_M);
                break;
            case SDLK_n:
                inputsReleased->push_back(Haze::InputType::KEY_N);
                break;
            case SDLK_o:
                inputsReleased->push_back(Haze::InputType::KEY_O);
                break;
            case SDLK_p:
                inputsReleased->push_back(Haze::InputType::KEY_P);
                break;
            case SDLK_q:
                inputsReleased->push_back(Haze::InputType::KEY_Q);
                break;
            case SDLK_r:
                inputsReleased->push_back(Haze::InputType::KEY_R);
                break;
            case SDLK_s:
                inputsReleased->push_back(Haze::InputType::KEY_S);
                break;
            case SDLK_t:
                inputsReleased->push_back(Haze::InputType::KEY_T);
                break;
            case SDLK_u:
                inputsReleased->push_back(Haze::InputType::KEY_U);
                break;
            case SDLK_v:
                inputsReleased->push_back(Haze::InputType::KEY_V);
                break;
            case SDLK_w:
                inputsReleased->push_back(Haze::InputType::KEY_W);
                break;
            case SDLK_x:
                inputsReleased->push_back(Haze::InputType::KEY_X);
                break;
            case SDLK_y:
                inputsReleased->push_back(Haze::InputType::KEY_Y);
                break;
            case SDLK_z:
                inputsReleased->push_back(Haze::InputType::KEY_Z);
                break;
            case SDLK_0:
                inputsReleased->push_back(Haze::InputType::NUMKEY_0);
                break;
            case SDLK_1:
                inputsReleased->push_back(Haze::InputType::NUMKEY_1);
                break;
            case SDLK_2:
                inputsReleased->push_back(Haze::InputType::NUMKEY_2);
                break;
            case SDLK_3:
                inputsReleased->push_back(Haze::InputType::NUMKEY_3);
                break;
            case SDLK_4:
                inputsReleased->push_back(Haze::InputType::NUMKEY_4);
                break;
            case SDLK_5:
                inputsReleased->push_back(Haze::InputType::NUMKEY_5);
                break;
            case SDLK_6:
                inputsReleased->push_back(Haze::InputType::NUMKEY_6);
                break;
            case SDLK_7:
                inputsReleased->push_back(Haze::InputType::NUMKEY_7);
                break;
            case SDLK_8:
                inputsReleased->push_back(Haze::InputType::NUMKEY_8);
                break;
            case SDLK_9:
                inputsReleased->push_back(Haze::InputType::NUMKEY_9);
                break;
            case SDLK_ESCAPE:
                inputsReleased->push_back(Haze::InputType::KEY_ESC);
                break;
            case SDLK_KP_ENTER:
                inputsReleased->push_back(Haze::InputType::KEY_ENTER_INPUT);
                break;
            case SDLK_RETURN:
                inputsReleased->push_back(Haze::InputType::KEY_ENTER_INPUT);
                break;
            case SDLK_SPACE:
                inputsReleased->push_back(Haze::InputType::KEY_SPACE);
                break;
            case SDLK_BACKSPACE:
                inputsReleased->push_back(Haze::InputType::KEY_BACK);
                break;
            case SDLK_TAB:
                inputsReleased->push_back(Haze::InputType::KEY_TAB);
                break;
            case SDLK_UP:
                inputsReleased->push_back(Haze::InputType::KEY_UP_ARROW);
                break;
            case SDLK_DOWN:
                inputsReleased->push_back(Haze::InputType::KEY_DOWN_ARROW);
                break;
            case SDLK_LEFT:
                inputsReleased->push_back(Haze::InputType::KEY_LEFT_ARROW);
                break;
            case SDLK_RIGHT:
                inputsReleased->push_back(Haze::InputType::KEY_RIGHT_ARROW);
                break;
            case SDLK_F1:
                inputsReleased->push_back(Haze::InputType::KEY_F1);
                break;
            case SDLK_F2:
                inputsReleased->push_back(Haze::InputType::KEY_F2);
                break;
            case SDLK_F3:
                inputsReleased->push_back(Haze::InputType::KEY_F3);
                break;
            case SDLK_F4:
                inputsReleased->push_back(Haze::InputType::KEY_F4);
                break;
            case SDLK_F5:
                inputsReleased->push_back(Haze::InputType::KEY_F5);
                break;
            case SDLK_F6:
                inputsReleased->push_back(Haze::InputType::KEY_F6);
                break;
            case SDLK_F7:
                inputsReleased->push_back(Haze::InputType::KEY_F7);
                break;
            case SDLK_F8:
                inputsReleased->push_back(Haze::InputType::KEY_F8);
                break;
            case SDLK_F9:
                inputsReleased->push_back(Haze::InputType::KEY_F9);
                break;
            case SDLK_F10:
                inputsReleased->push_back(Haze::InputType::KEY_F10);
                break;
            case SDLK_F11:
                inputsReleased->push_back(Haze::InputType::KEY_F11);
                break;
            case SDLK_F12:
                inputsReleased->push_back(Haze::InputType::KEY_F12);
                break;
            case SDLK_PERIOD:
                inputsReleased->push_back(Haze::InputType::KEY_DOT);
                break;
            default:
                break;
            }
        }
    }

    void SdlWindow::fillMousePressed(MouseType *mouseType)
    {
        if (_event.type == SDL_MOUSEBUTTONDOWN)
        {
            *mouseType = PRESSED;
        }
    }

    void SdlWindow::fillMouseReleased(MouseType *mouseType)
    {
        if (_event.type == SDL_MOUSEBUTTONUP)
        {
            *mouseType = RELEASED;
        }
    }

    void SdlWindow::fillFocus(bool *focus)
    {
        if (_event.type == SDL_WINDOWEVENT_FOCUS_GAINED)
            *focus = true;
        else if (_event.type == SDL_WINDOWEVENT_FOCUS_LOST)
            *focus = false;
        *focus = true;
    }

    void SdlWindow::fillMousePosition(int *x, int *y)
    {
        SDL_GetMouseState(x, y);
    }

    bool SdlWindow::pollEvent()
    {
        return SDL_PollEvent(&_event);
    }
}

namespace Haze
{
    SDL_Color SdlColor::getColor(IColor::colorEnum color)
    {
        switch (color)
        {
        case IColor::colorEnum::BLACK:
            return SDL_Color{0, 0, 0, 255};
        case IColor::colorEnum::WHITE:
            return SDL_Color{255, 255, 255, 255};
        case IColor::colorEnum::RED:
            return SDL_Color{255, 0, 0, 255};
        case IColor::colorEnum::GREEN:
            return SDL_Color{0, 255, 0, 255};
        case IColor::colorEnum::BLUE:
            return SDL_Color{0, 0, 255, 255};
        case IColor::colorEnum::YELLOW:
            return SDL_Color{255, 255, 0, 255};
        case IColor::colorEnum::MAGENTA:
            return SDL_Color{255, 0, 255, 255};
        case IColor::colorEnum::CYAN:
            return SDL_Color{0, 255, 255, 255};
        case IColor::colorEnum::TRANSPARENT:
            return SDL_Color{0, 0, 0, 0};
        default:
            return SDL_Color{0, 0, 0, 0};
        }
    }

    SDL_Color SdlColor::getColor(int r, int g, int b, int a)
    {
        return SDL_Color{Uint8(r), Uint8(g), Uint8(b), Uint8(a)};
    }
}

namespace Haze
{
    SdlRect::SdlRect(int x, int y, int width, int height, IColor::colorEnum color)
    {
        _rect.x = x;
        _rect.y = y;
        _rect.w = width;
        _rect.h = height;
        _fillColor = SdlColor::getColor(color);
    }

    void SdlRect::setPosition(int x, int y)
    {
        _rect.x = x;
        _rect.y = y;
    }

    void SdlRect::setFillColor(IColor::colorEnum color)
    {
        _fillColor = SdlColor::getColor(color);
    }

    void SdlRect::setOutlineColor(IColor::colorEnum color)
    {
        _outlineColor = SdlColor::getColor(color);
    }

    void SdlRect::setOutlineThickness(float thickness)
    {
        _outlineThickness = thickness;
    }

    void SdlRect::setSize(int width, int height)
    {
        _rect.w = width;
        _rect.h = height;
    }
}

namespace Haze
{
    AssetManager<SdlFont> fontManager;
    SdlText::SdlText(const std::string &text, IColor::colorEnum color, std::string path)
    {
        _font = fontManager.loadAsset("assets/fonts/" + path);
        _string = text;
        _color = SdlColor::getColor(color);
        if (_string == "")
            _string = " ";
        SDL_Surface *surface = TTF_RenderText_Solid(_font->getFont(), _string.c_str(), _color);
        if (surface == nullptr)
            std::cout << "ErrorSurface text: " << SDL_GetError() << std::endl;
        _texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (_texture == nullptr)
            std::cout << "ErrorTexture text: " << SDL_GetError() << std::endl;
        TTF_SizeText(_font->getFont(), _string.c_str(), &_rect.w, &_rect.h);
    }

    void SdlText::setPosition(int x, int y)
    {
        _rect.x = x;
        _rect.y = y;
    }

    void SdlText::setColor(IColor::colorEnum color)
    {
        _color = SdlColor::getColor(color);
        _texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(_font->getFont(), _string.c_str(), _color));
    }

    void SdlText::setColor(int r, int g, int b, int a)
    {
        _color = SdlColor::getColor(r, g, b, a);
        _texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(_font->getFont(), _string.c_str(), _color));
    }

    void SdlText::setString(std::string string)
    {
        _string = string;
        _texture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(_font->getFont(), _string.c_str(), _color));
        TTF_SizeText(_font->getFont(), _string.c_str(), &_rect.w, &_rect.h);

    }

    void SdlText::setScale(float x, float y)
    {
        _scaleX = x;
        _scaleY = y;
    }

}

namespace Haze
{
    SdlFont::SdlFont(std::string path)
    {
        _font = TTF_OpenFont(path.c_str(), 30);
    }
}

namespace Haze
{
    ITexture *SdlDisplay::createTexture(std::string path)
    {
        return new SdlTexture(path);
    }

    ISprite *SdlDisplay::createSprite(std::string path)
    {
        return new SdlSprite(path);
    }

    IAudio *SdlDisplay::createAudio(std::string path)
    {
        return new SdlAudio(path);
    }

    IWindow *SdlDisplay::createWindow(int width, int height, std::string title)
    {
        return new SdlWindow(width, height, title);
    }

    IText *SdlDisplay::createText(const std::string &text, IColor::colorEnum color, const std::string &fontname)
    {
        return new SdlText(text, color, fontname);
    }

    IRect *SdlDisplay::createRect(int x, int y, int width, int height, IColor::colorEnum color)
    {
        return new SdlRect(x, y, width, height, color);
    }

    SdlDisplay::SdlDisplay()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        }

        if (TTF_Init() != 0) {
            SDL_Log("Unable to initialize SDL_ttf: %s", TTF_GetError());
            SDL_Quit();
        }

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
            SDL_Quit();
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            SDL_Log("Unable to initialize SDL_mixer: %s", Mix_GetError());
            SDL_Quit();
        }
    }

    SdlDisplay::~SdlDisplay()
    {
        SDL_Quit();
    }
}