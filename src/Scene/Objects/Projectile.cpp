#include "Projectile.h"

Projectile::Projectile(const FPoint& position,
					   const FPoint& direction,
					   const FPoint& size)
: baseclass(position, size, direction, "projectile")
{
}

void Projectile::Draw()
{
	baseclass::Draw();
}

void Projectile::Update(float dt, const IRect& boundingBox)
{
	baseclass::Update(dt, boundingBox);

	_angle = 180.f * _direction.GetAngle() / math::PI;
}
