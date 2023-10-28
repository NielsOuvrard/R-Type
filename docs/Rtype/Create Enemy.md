# Enemy Creation Documentation

This documentation outlines the process of creating enemies for your enemies inside Rtype. You can customize various attributes of your enemies using this data.
Store your enemy data in a JSON file and save it in the `assets/enemies` directory.

## Enemy Data Structure

The `enemies` files should contain the following attributes for each enemy:

- `type`: An integer representing the type of enemy.
- `damage`: An integer representing the damage the enemy deals.
- `life`: An integer representing the enemy's life or health points.
- `path_sprite`: A string representing the file path to the enemy's sprite image.
- `hitbox`: An object specifying the hitbox dimensions with the following properties:
  - `x`: The x-coordinate of the hitbox's top-left corner.
  - `y`: The y-coordinate of the hitbox's top-left corner.
  - `width`: The width of the hitbox.
  - `height`: The height of the hitbox.
- `animation`: An object specifying the animation dimensions with the following properties:
  - `x`: The x-coordinate of the animation's top-left corner.
  - `y`: The y-coordinate of the animation's top-left corner.
  - `width`: The width of the animation.
  - `height`: The height of the animation.

### Here's an example JSON data structure for an enemy:

```json
{
  "type": 1,
  "damage": 20,
  "life": 50,
  "path_sprite": "assets/sprites/enemy.gif",
  "hitbox": {
    "x": 5,
    "y": 5,
    "width": 23,
    "height": 26
  },
  "animation_tics": 0.1,
  "animation_type": "loop",
  "animation": [
    {
      "x": 0,
      // Additional animation properties...
    }
  ]
}
```