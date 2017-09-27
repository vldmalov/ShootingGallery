#include "Projectile.h"
#include "Preferences.h"

namespace Scene {

Projectile::Projectile(const FPoint& position, const FPoint& size, const FPoint& direction)
: baseclass(position, size, direction, "projectile")
{
	Preferences& prefs = Preferences::Instance();
	_gravityFactor = prefs.getFloatValue("ProjectileGravity", 0.f);
}

void Projectile::Update(float dt, const IRect& boundingBox)
{
	_direction.y -= dt * _gravityFactor;
	baseclass::Update(dt, boundingBox);

	_angle = 180.f * _direction.GetAngle() / math::PI;
}

void Projectile::OnBottomBoardCollision(float collisionSize)
{
	SetMarkedOnDelete(true);
}
	
}
