#include "SceneDynamicObject.h"

namespace Scene {

SceneDynamicObject::SceneDynamicObject(const FPoint& position, const FPoint& size,
									   const FPoint& direction, const std::string& textureName)
: baseclass(position, size, textureName)
, _direction(direction)
, _processBoarderCollisions(true)
, _isMarkedOnDelete(false)
{
}

void SceneDynamicObject::Update(float dt, const IRect& boundingBox)
{
	_position += dt * _direction;
	
	if(_processBoarderCollisions) {
		CheckAndProcessCollisions(boundingBox);
	}
}

float GetDistanceToBorder(float position, float size, float direction,  float boarderMin, float boarderMax)
{
	float nearestObjectEdge = position + ((direction > 0) ? 1 : -1) * size;
	float distanceToBorder(0);
	if(direction > 0) {
		distanceToBorder = boarderMax - nearestObjectEdge;
	} else {
		distanceToBorder = nearestObjectEdge - boarderMin;
	}
	
	return distanceToBorder;
}

void SceneDynamicObject::CheckAndProcessCollisions(const IRect& boundingBox)
{
	float distance = GetDistanceToBorder(_position.x, _size.x / 2.f, _direction.x,
										 boundingBox.x,  boundingBox.RightTop().x);
	if(distance < 0.f) {
		OnSideBoardCollision(distance);
	}
	
	distance = GetDistanceToBorder(_position.y, _size.y / 2.f, _direction.y,
								   boundingBox.y,  boundingBox.RightTop().y);
	if(distance < 0.f) {
		
		if(_direction.y > 0.f) {
			OnTopBoardCollision(distance);
		} else {
			OnBottomBoardCollision(distance);
		}
	}
}

void SceneDynamicObject::OnSideBoardCollision(float collisionSize)
{
	_position.x += collisionSize;
	_direction.x *= -1;
}

void SceneDynamicObject::OnTopBoardCollision(float collisionSize)
{
	_position.y += collisionSize;
	_direction.y *= -1;
}

void SceneDynamicObject::OnBottomBoardCollision(float collisionSize)
{
	_position.y += collisionSize;
	_direction.y *= -1;
}

const FPoint& SceneDynamicObject::GetDirection() const
{
	return _direction;
}

}
