# Adding Enemies to the Game Map

This documentation explains how to add enemies to your game map in Rtype using JSON data. Customize the behavior of each enemy by specifying various attributes. Ensure that you store your enemy data in a JSON file and save it in the `assets/enemies` directory.

## JSON Enemy Data Structure

The JSON enemy data should include the following attributes for each enemy:

- `type`: An integer representing the type of enemy. All enemies have a unique type, you can find the type of an enemy inside the directory `assets/enemies`.
- `x`: The x-coordinate of the enemy's initial position, from the position of the tile.
- `y`: The y-coordinate of the enemy's initial position. 0 is the top of the screen.
- `velocity_x`: The horizontal velocity of the enemy.
- `velocity_y`: The vertical velocity of the enemy.
- `move`: A string indicating the movement pattern of the enemy ("**linear**," "**circular**," "**sinusoidal**").
- `move_radius`: An integer representing the movement radius for circular or sinusoidal movement.
- `move_frequency`: A floating-point number specifying the movement frequency for **sinusoidal** movement.
- `move_amplitude`: An integer indicating the movement amplitude for **sinusoidal** movement.
- `move_time`: A floating-point number representing the time duration of the movement pattern.
- `move_x`: A floating-point number specifying the movement in the x-direction.

### Examples JSON Data for an Enemy:

#### Circular movement
```json
{
  "type": 1,
  "x": 24,
  "y": 200,
  "velocity_x": -2,
  "move": "circular",
  "move_radius": 100,
  "move_x": 0.2,
  "move_time": 0.1
}
```
#### Sinusoidal movement
```json
{
  "type": 2,
  "x": 24,
  "y": 200,
  "velocity_x": -2,
  "move": "sinusoidal",
  "move_frequency": 0.1,
  "move_amplitude": 50,
  "move_time": 0.1
}
```
#### Linear movement
```json
{
  "type": 3,
  "x": 24,
  "y": 200,
  "velocity_x": -2,
  "move": "linear",
  "move_time": 0.1
}
```