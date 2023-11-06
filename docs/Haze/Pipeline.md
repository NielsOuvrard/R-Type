## What is a Pipeline in Haze

A pipeline is a way to group systems in Haze. It allows to group systems hence allowing to differentiate easily systems that need additional libraries such as **SFML** from others that don't need it.

## How to build your Pipeline

A pipeline need the inherit from the virtual class `IPipeline` and only needs to add its systems when constructed.

Currently there are two existing pipelines in Haze: 
### GfxPipeline

This pipeline gather every system that needs to use **SFML** and is only used un **haze-graphic**.

### CorePipeline

This pipeline gather every system that rules basic Haze functionalities like positions, velocity or collisions.
