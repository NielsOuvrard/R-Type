#include "ComponentGfx.hpp"

namespace Haze {
    static std::vector<IDisplay *> loadDisplay()
    {
        typedef IDisplay *(*createDisplay_t)();
        std::vector<DynLib *> displayLib;
        std::vector<IDisplay *> displayss;
        fs::path libpath = "Haze/lib/";
        for (const auto &entry: fs::directory_iterator(libpath)) {
            //            if (entry.path().extension() == ".so") {
            if (entry.path().extension() == ".so" || entry.path().extension().string() == ".dylib") {

                displayLib.push_back(new DynLib(entry.path()));
            }
        }

        createDisplay_t createDisplay;
        for (int i = 0; i < displayLib.size(); i++) {
            createDisplay = (createDisplay_t) displayLib[i]->sym("createDisplay");
            if (createDisplay != nullptr) {
                displayss.push_back((IDisplay *) createDisplay());
            }
        }
        return displayss;
    }

    static std::vector<IDisplay *> displays = loadDisplay();
    static int GFX_LIB = 0;

    void setGfxLib(int lib)
    {
        GFX_LIB = lib;
    }

    Sprite::Sprite(std::string path) : path(path)
    {
        sprite = displays[GFX_LIB]->createSprite(path);
    }

    Audio::Audio(std::string path) : path(path)
    {
        audio = displays[GFX_LIB]->createAudio(path);
        audio->play();
    }

    Window::Window(int width, int height) : width(width), height(height), active(false)
    {
        window = displays[GFX_LIB]->createWindow(width, height, "R-Type");
    }

    HitboxDisplay::HitboxDisplay()
    {
        rect = displays[GFX_LIB]->createRect(0, 0, 0, 0, IColor::RED);
        rect->setFillColor(IColor::TRANSPARENT);
        rect->setOutlineColor(IColor::RED);
        rect->setOutlineThickness(5);
    }

    Sound::Sound(std::string path, bool loop) : path(path)
    {
        sound = displays[GFX_LIB]->createAudio(path);
        sound->setLoop(loop);
    }

    Text::Text(const std::string &text, colorHaze color, const std::string &fontname) : text(text)
    {
        textObj = displays[GFX_LIB]->createText(text, IColor::RED, fontname);
        switch (color) {
            case RED:
                textObj->setColor(IColor::RED);
                break;
            case GREEN:
                textObj->setColor(IColor::GREEN);
                break;
            case BLUE:
                textObj->setColor(IColor::BLUE);
                break;
            case YELLOW:
                textObj->setColor(IColor::YELLOW);
                break;
            case BLACK:
                textObj->setColor(IColor::BLACK);
                break;
            case WHITE:
                textObj->setColor(IColor::WHITE);
                break;
            case MAGENTA:
                textObj->setColor(IColor::MAGENTA);
                break;
            case CYAN:
                textObj->setColor(IColor::CYAN);
                break;
        }
    }

    Text::Text(const std::string &text, int r, int g, int b, int a, const std::string &fontname) : text(text)
    {
        textObj = displays[GFX_LIB]->createText(text, IColor::RED, fontname);
        textObj->setColor(r, g, b, a);
    }

}// namespace Haze