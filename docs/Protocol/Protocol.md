## Header

Each message should have a header with:

- A **timestamp**
- An **id**
- A **body size**

### ID Client -> Server

| ID            | Body         | Response ID    |
|---------------|--------------|----------------|
| INPUT         | info_inputs  | NONE           |
| GET_ENTITY    | id_entity    | INFO_ENTITY    |
| GET_ENTITIES  | NONE         | INFO_ENTITIES  |
| GET_COMPONENT | id_component | INFO_COMPONENT |
| ALIVE         | NONE         | NONE           |

### ID Server -> Client

| ID               | Body           | Response ID |
|------------------|----------------|-------------|
| CREATE_ENTITY    | id_entity      | NONE        |
| DELETE_ENTITY    | id_entity      | NONE        |
| ADD_COMPONENT    | info_component | NONE        |
| REMOVE_COMPONENT | id_component   | NONE        |
| INFO_COMPONENT   | info_component | NONE        |
| INFO_ENTITY      | info_entity    | NONE        |
| INFO_ENTITIES    | info_entities  | NONE        |
| DEAD             | NONE           | NONE        |

## Body

The body of a message is just raw data that can be interpreted thanks to the header.

* **info_inputs**

```cpp
struct info_inputs {
	std::vector<InputType> inputsPressed;
	std::vector<InputType> inputsReleased;
	MouseType mouseType;
	int x;
	int y;
};
```

InputType at [[R-Type/Documentation/Protocol/Inputs|Inputs]]
MouseType at [[R-Type/Documentation/Protocol/Inputs|Inputs]]

- **id_entity**

```cpp
struct id_entity {
	int id;
};
```

- **id_component**

```cpp
struct id_component {
	id_entity id;
	std::string component;
};
```

- **info_entity**

```cpp
struct info_entity {
	id_entity id;
	std::vector<std::string> components;
};
```

- **info_component**

```cpp
struct info_component {
	std::string component;
	std::vector<uint8_t> data = std::vector<uint8_t>(128);
};
```

Data at [[Component Data]]

- **info_entities**

```cpp
struct info_entities {
	std::vector<id_entity> id;
};
```
