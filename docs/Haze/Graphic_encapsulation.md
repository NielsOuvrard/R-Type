## How does the graphic encapsulation work in Haze ?

The graphic encapsulation exists to allows to change easily the graphic library of the engine.

Multiples virtual class exits in this encapsulation those are:

- ISprite
- ITexture
- IText
- IAudio
- IWindow
- IInput
- IRect
- IColor

Each of these class needs to be inherited to allows for full support of a graphic lib.

For now Haze support **SFML** with

- SfSprite
- SfTexture
- SfText
- SfAudio
- SfWindow
- SfInput
- SfRect
- SfColor
