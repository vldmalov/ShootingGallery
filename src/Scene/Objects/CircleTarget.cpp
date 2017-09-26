#include "CircleTarget.h"

CircleTarget::CircleTarget(const FPoint& position, float radius, const FPoint& direction)
: baseclass(position, FPoint(2.f * radius, 2.f * radius), direction, "soapBubble")
{
}

void CircleTarget::Draw()
{
	baseclass::Draw();
}

void CircleTarget::Update(float dt, const IRect& boundingBox)
{
	baseclass::Update(dt, boundingBox);
}

float CircleTarget::GetRadius() const
{
	assert(_size.x == _size.y);
	return _size.x / 2.0;
}
