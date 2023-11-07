# Rtype

## Organization

[schema](./schema.png)



### WALL

- void build(uint16_t frameIndex = 0);
- void send();
- void stopVelocity();
- void destroy();
- [[nodiscard]] float get_x_position() const;

### Shot

- void build(float x, float y);
- void send();
- void stopVelocity();

### Player

- void build();
- void update();
- void send();
- void sendUpdate();

### Parallax

- void build(std::string parallax_path);
- void update();
- void send();
- void sendUpdate();

### Map

- void update();
- void build();
- void loadMaps();
- void createMap();

### Explosion

- void build();
- void send();
- void destroy();

### Enemy

- void build(EnemyData data, nlohmann::json mapData);
- void send();
- void shot();
- void update();
- void stopVelocity();

### Cooldown

- void setDuration(std::chrono::milliseconds duration);
- bool IsReady();
- void Activate();
- void Reset();

### Boss

- void build(std::string path);
- void send();
- void shot();
- void update();
- void stopVelocity();

