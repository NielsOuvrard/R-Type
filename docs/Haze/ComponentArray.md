## What is a ComponentArray

The component array in Haze is where is stored all of the data of the engine.
It contains all of the components in a two dimensional sparse array. Each entity being a simple id in this array. (for
more details about entity: [Entity](Entity%20Technical.md))
Each column in the component array being an entity and each line a component.

If an **Entity** doesn't posses a component this field will simply be **null**. If this entity have this component, it
will contain the pointer to it.
