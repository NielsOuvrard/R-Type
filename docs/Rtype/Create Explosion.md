# explosion Creation Documentation

This documentation outlines the process of creating explosion for the game.

## explosion Data Structure

The `explosion` files should contain the following attributes for each explosion:

- `type`: An integer representing the type of shot.
- `path_sprite`: A string representing the file path to the shot's sprite image.

- `animation_tics`: A float representing the time between animation frames. **default 0.1**
- `animation_type`: A string representing the type of animation. **default "loop"**
    - `"loop"`: The animation will loop.
    - `"boomerang"`: The animation will play forward and then in reverse.
    - `"once"`: The animation will play once and then stop.
    - `"loop_once"`: The animation will loop until the end and then stop.
- `animation`: An object specifying the animation dimensions with the following properties:
    - `x`: The x-coordinate of the animation's top-left corner.
    - `y`: The y-coordinate of the animation's top-left corner.
    - `width`: The width of the animation.
    - `height`: The height of the animation.

### Here's an example JSON data structure for an explosion:

```json
{
  "type": 1,
  "path_sprite": "assets/sprites/spaceship.gif",
  "animation_tics": 0.2,
  "animation_type": "loop_once",
  "animation": [
    {
      "x": 0
      // Additional animation properties...
    }
  ]
}
```