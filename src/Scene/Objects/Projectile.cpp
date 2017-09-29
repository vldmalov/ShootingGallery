#include "Projectile.h"
#include "Preferences.h"

namespace Scene {

Projectile::Projectile(const FPoint& position, const FPoint& size, const FPoint& direction)
: baseclass(position, size, direction, "projectile")
, _trackEffect(nullptr)
{
	Preferences& prefs = Preferences::Instance();
	_gravityFactor = prefs.getFloatValue("ProjectileGravity", 0.f);
	
	UpdateAngle();
}
	
Projectile::~Projectile()
{
	if(_trackEffect) {
		_trackEffect->Finish();
	}
}
	
void Projectile::SetTrackEffect(ParticleEffectPtr effect)
{
	if(!effect) {
		return;
	}
	
	_trackEffect = effect;
	_trackEffect->SetPos(GetJetPosition());
	_trackEffect->Reset();
}

void Projectile::Update(float dt, const IRect& boundingBox)
{
	_direction.y -= dt * _gravityFactor;
	baseclass::Update(dt, boundingBox);
	
	if(_trackEffect) {
		_trackEffect->SetPos(GetJetPosition());
	}

	UpdateAngle();
}
	
void Projectile::UpdateAngle()
{
	_angle = 180.f * _direction.GetAngle() / math::PI;
}
	
FPoint Projectile::GetJetPosition() const
{
	FPoint jetPosition = _position;
	jetPosition -= _direction.Normalized() * (_size.y / 2.f);
	
	return jetPosition;
}

void Projectile::OnBottomBoardCollision(float collisionSize)
{
	SetMarkedOnDelete(true);
}
	
}
