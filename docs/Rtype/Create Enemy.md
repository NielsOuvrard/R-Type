# Enemy Creation Documentation

This documentation outlines the process of creating enemies for your enemies inside Rtype. You can customize various
attributes of your enemies using this data.
Store your enemy data in a JSON file and save it in the `assets/enemies` directory.

## Enemy Data Structure

The `enemies` files should contain the following attributes for each enemy:

- `type`: An integer representing the type of enemy.
- `damage`: An integer representing the damage the enemy deals when he shots. **default 0**
- `life`: An integer representing the enemy's life or health points. **-1** if immortal. **default 1**
- `shot_type`: An integer representing the type of shot the enemy fires.**-1** if the enemy does not fire. **default -1
  **
- `explosion_type`: An integer representing the type of explosion the enemy makes when he dies. **-1** if the enemy does
  not explode. **default -1**
- `path_sprite`: A string representing the file path to the enemy's sprite image.
- `hitbox`: An object specifying the hitbox dimensions with the following properties:
    - `x`: The x-coordinate of the hitbox's top-left corner.
    - `y`: The y-coordinate of the hitbox's top-left corner.
    - `width`: The width of the hitbox.
    - `height`: The height of the hitbox.
- `fly`: A boolean indicating if the enemy can fly. If false, the enemy will be fixed to the ground or the ceiling. *
  *default false**

- `animation_tics`: A float representing the time between animation frames. **default 0.1**
- `animation_type`: A string representing the type of animation. **default "loop"**
- `animation`: An object specifying the animation dimensions with the following properties:
    - `x`: The x-coordinate of the animation's top-left corner.
    - `y`: The y-coordinate of the animation's top-left corner.
    - `width`: The width of the animation.
    - `height`: The height of the animation.

### Here's an example JSON data structure for an enemy:

```json
{
  "type": 3,
  "damage": 20,
  "life": 50,
  "shot_type": 2,
  "explosion_type": 2,
  "path_sprite": "assets/sprites/r-typesheet12.gif",
  "hitbox": {
    "x": 2,
    "y": 2,
    "height": 14,
    "width": 13
  },
  "fly": false,
  "animation_tics": 0.1,
  "animation_type": "loop",
  "animation": [
    {
      "x": 0
      // Additional animation properties...
    }
  ]
}
```
