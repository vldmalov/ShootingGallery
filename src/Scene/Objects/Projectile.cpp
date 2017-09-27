#include "Projectile.h"

namespace Scene {
	
const float GRAVITY_FACTOR = 20.f;

Projectile::Projectile(const FPoint& position, const FPoint& size, const FPoint& direction)
: baseclass(position, size, direction, "projectile")
{
}

void Projectile::Update(float dt, const IRect& boundingBox)
{
	_direction.y -= dt * GRAVITY_FACTOR;
	baseclass::Update(dt, boundingBox);

	_angle = 180.f * _direction.GetAngle() / math::PI;
}

void Projectile::OnBottomBoardCollision(float collisionSize)
{
	_isMarkedOnDelete = true;
}
	
}
