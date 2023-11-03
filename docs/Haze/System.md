## What is a System?

In an ECS architecture, a system is a modular component responsible for processing entities that contain specific
components. Each system is designed to handle a specific aspect of the game logic, such as rendering, physics, input, or
AI. Systems are used to update the state of entities, implement game rules, and perform various operations.

## How does a system work

A system in Haze will iterate trough the [ComponentArray](ComponentArray.md) to modify the components stored inside. By
selecting entities with specific components, a system can act on a selected portion of the entities.

## Types of Systems and Pipelines

In an ECS architecture, various types of systems are commonly used to manage different aspects of a game. We have
decided to group these different system types in Pipelines. To lean more about pipeline [Pipeline](Pipeline.md).
