## Data used to build a component
```cpp
namespace Haze
{
	struct PositionData {
		float x;
		float y;
	};
	
	struct ScaleData {
		float x;
		float y;
	};
	
	struct VelocityData {
		float x;
		float y;
	};
	
	struct MoveData {
		float x;
		float y;
	};
	
	struct HealthData {
		int health;
	};
	
	struct DamageData {
		int damage;
	};
	
	struct CollisionData {
		std::string scene;
		std::map<std::string, Collision::CollisionInfo> behavior;
	};
	
	struct HitboxData {
		std::vector<Hitbox::intRect> hitbox;
	};
	
	struct LifeTimeData {
		int lifeTime;
	};
	
	struct SpriteData {
		std::string path;
	};
	
	struct WindowData {
		int width;
		int height;
	};
	
	struct AnimationData {
		std::vector<Animation::intRect> frames;
		Animation::AnimationType type;
		bool direction;
		double tics;
	};
	
	struct TextData {
		std::string text;
		sf::Color color;
	};
}
```