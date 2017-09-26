#include "SceneDynamicObject.h"


SceneDynamicObject::SceneDynamicObject(const FPoint& position, const FPoint& size,
									   const FPoint& direction, const std::string& textureName)
: baseclass(position, size, textureName)
, _direction(direction)
{
}

void SceneDynamicObject::Update(float dt, const IRect& boundingBox)
{
	_position += dt * _direction;
	
	CheckAndProcessBoarderCollision(_position.x, _direction.x, _size.x / 2.f,
									boundingBox.x, boundingBox.RightTop().x);
	
	CheckAndProcessBoarderCollision(_position.y, _direction.y, _size.y / 2.f,
									boundingBox.y, boundingBox.RightTop().y);
}

void SceneDynamicObject::CheckAndProcessBoarderCollision(float& position,
														 float& direction,
														 float size,
														 float boarderMin,
														 float boarderMax)
{
	float nearestObjectEdge = position + ((direction > 0) ? 1 : -1) * size;
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

const FPoint& SceneDynamicObject::GetDirection() const
{
	return _direction;
}
