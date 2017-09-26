#pragma once

class Scene;

class CircleTarget {
	
public:
	CircleTarget(std::weak_ptr<Scene> scene);
	~CircleTarget();
	
	void Draw();
	void Update(float dt);
	
	void SetTextureName(const std::string& textureName);
	
	void SetPosition(const FPoint& position);
	const FPoint& GetPosition() const;
	
	void SetRadius(float radius);
	float GetRadius() const;
	
	void SetDirection(const math::Vector3& direction);
	const math::Vector3& GetDirection() const;
	
private:
	void CheckAndProcessBoarderCollision(float& position, float& direction,
										 float boarderMin, float boarderMax);
	
private:
	FPoint  _position;
	float   _radius;
	math::Vector3 _direction;
	
	Render::Texture* _texture;
	
	std::weak_ptr<Scene> _scene;

};

typedef std::shared_ptr<CircleTarget> CircleTargetPtr;
