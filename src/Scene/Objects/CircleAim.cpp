#include "CircleAim.h"

#include "Scene.h"

CircleAim::CircleAim(std::weak_ptr<Scene> scene)
: _position()
, _radius(0.f)
, _direction()
, _texture(nullptr)
, _scene(scene)
{

}

CircleAim::~CircleAim()
{
}

void CircleAim::Draw()
{
	if(_texture) {
		
		const IRect& textureRect = _texture->getBitmapRect();
		assert(textureRect.Height() == textureRect.Width());
		
		float textureRadius = static_cast<float>(textureRect.Height()) / 2.f;
		
		float scaleFactor(_radius / textureRadius);
		
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_position.x,
									   _position.y, 0);
		Render::device.MatrixScale(scaleFactor, scaleFactor, 1.f);
		Render::device.MatrixTranslate(-textureRadius,
									   -textureRadius, 0);
		_texture->Draw();
		
		Render::device.PopMatrix();
	}
}

void CircleAim::Update(float dt)
{
	_position += FPoint(_direction.x * dt, _direction.y * dt);
	
	std::shared_ptr<Scene> scenePtr = _scene.lock();
	if(scenePtr) {
		const IRect& playgroundRect = scenePtr->getPlaygroundRect();
		
		CheckAndProcessBoarderCollision(_position.x, _direction.x,
										playgroundRect.x, playgroundRect.RightTop().x);
		
		CheckAndProcessBoarderCollision(_position.y, _direction.y,
										playgroundRect.y, playgroundRect.RightTop().y);
	}
}

void CircleAim::CheckAndProcessBoarderCollision(float& position, float& direction,
												float boarderMin, float boarderMax)
{
	float nearestObjectEdge = position + ((direction > 0) ? 1 : -1) * _radius;
	float distanceToBorder(0);
	if(direction > 0) {
		distanceToBorder = boarderMax - nearestObjectEdge;
	} else {
		distanceToBorder = nearestObjectEdge - boarderMin;
	}
	
	if(distanceToBorder < 0) {
		position += distanceToBorder;
		direction *= -1;
	}
}

void CircleAim::SetTextureName(const std::string& textureName)
{
	_texture = Core::resourceManager.Get<Render::Texture>(textureName);
}

void CircleAim::SetPosition(const FPoint& position)
{
	_position = position;
}

const FPoint& CircleAim::GetPosition() const
{
	return _position;
}

void CircleAim::SetRadius(float radius)
{
	_radius = radius;
}

float CircleAim::GetRadius() const
{
	return _radius;
}

void CircleAim::SetDirection(const math::Vector3& direction)
{
	_direction = direction;
}

const math::Vector3& CircleAim::GetDirection() const
{
	return _direction;
}
