#include "SdlDisplay.hpp"

Haze::IDisplay *createDisplay()
{
    return new Haze::SdlDisplay();
}

namespace Haze
{
    static AssetManager<SdlTexture> assetManager;
    SdlSprite::SdlSprite(std::string path)
    {
        _texture = assetManager.loadTexture(path);
    }

    void SdlSprite::setPosition(int x, int y)
    {
        _rect.x = x + originX;
        _rect.y = y + originY;
    }

    void SdlSprite::setScale(float x, float y)
    {
        _scaleX = x;
        _scaleY = y;
    }

    void SdlSprite::setOrigin(float x, float y)
    {
        originX = x;
        originY = y;
    }

    void SdlSprite::setRotation(float angle)
    {
        
    }
}
