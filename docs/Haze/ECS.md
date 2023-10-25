# Understanding the Entity-Component-System (ECS) Architecture

The Entity-Component-System (ECS) architecture is a design pattern commonly used in game development and simulation systems. It separates the game logic into three distinct parts: entities, components, and systems. This separation promotes modularity, flexibility, and performance in managing complex systems.

## Components

Components are the building blocks of an ECS. They are small, reusable pieces of data that define the attributes or behaviors of an entity. Each component typically contains only the necessary data and functions required for a specific aspect of the entity. For example, in a game, you might have components like:

- `Position`: Contains position of the entity
- `Sprite`: Contains information about the entity's visual representation.
- `Scale`: Stores information about the entity's scale

Components are often represented as simple data structures and do not contain logic or methods.
For more information about components in Haze:
[ComponentsGfx](ComponentGfx%20Technical.md)
[ComponentsCore](ComponentCore%20Technical.md)

## Entities

Entities are the game objects themselves. An entity is essentially a container that groups together one or more components. Entities don't have behavior on their own but gain behavior by having the appropriate components attached. For example, a player character entity might consist of a `Position`, a `Sprite`, and an `Input`.

Entities are typically identified by a unique ID or a name to make them easy to reference.

## Systems

Systems are responsible for updating and processing entities and their components. Each system has a specific role, such as rendering, physics simulation, or input handling. Systems iterate over the entities that contain the necessary components they are designed to operate on. For example:

- The `RenderSystem` processes entities with `SpriteComponent` to render them on the screen.
- The `PhysicsSystem` handles entities with `PhysicsComponent` to simulate physics interactions.
- The `InputSystem` listens for input events and updates entities with `InputComponent`.

Systems are crucial for managing the flow of game logic and keeping it organized.

## Benefits of ECS

- **Modularity**: Components and systems can be added or removed without affecting the rest of the system.
- **Performance**: Data locality and cache-friendliness are often optimized in ECS, leading to efficient processing.
- **Scalability**: ECS scales well for large and complex systems.
- **Code Reusability**: Components are highly reusable, reducing redundant code.
