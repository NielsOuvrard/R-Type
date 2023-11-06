## How does the graphic encapsulation work in Haze ?

The graphic encapsulation exists to allows to change easily the graphic library of the engine.

Multiples virtual class exits in this encapsulation those are:
- **IDisplay**
- ISprite
- ITexture
- IText
- IAudio
- IWindow
- IInput
- IRect
- IColor
- IAudioBuffer
- IFont

Each of these class needs to be inherited to allows for full support of a graphic lib.

## How do dynamic libraries are used in Haze ?

Since graphic libraries are loaded from dynamic libraries in Haze, it's very easy to add or change graphic libraries. The compilation of these libraries are done using cmake and the `.so` are put into the `Haze/lib` directory.
These `.so` files are then loaded into the engine depending of which library you want to use.
