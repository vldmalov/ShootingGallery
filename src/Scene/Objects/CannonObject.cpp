#include "CannonObject.h"

#include "Projectile.h"
#include "Preferences.h"

namespace Scene {

CannonObject::CannonObject(const FPoint& position, const FPoint& size)
: baseclass(position, size, "cannonBase")
, _turretTexture(Core::resourceManager.Get<Render::Texture>("cannon"))
, _reloadCooldown(0.f)
{
	if(!_turretTexture) {
		Log::log.WriteWarn("CannonObject. Turret texture doesn't exist");
	}
	
	_turretAngle = Preferences::Instance().getFloatValue("TurretInitAngle", 90.f);
	_observeAngle = _turretAngle;

	_turretLinkPointShift = FPoint(Preferences::Instance().getFloatValue("turretLinkPointShiftX", 0.f),
								   Preferences::Instance().getFloatValue("turretLinkPointShiftY", 0.f));
}
	
void CannonObject::Draw()
{
	baseclass::Draw();
	
	if(_turretTexture) {
		
		Render::device.PushMatrix();
		
		FPoint linkPoint = GetLinkPoint();
		Render::device.MatrixTranslate(linkPoint.x, linkPoint.y, 0);
		Render::device.MatrixRotate(math::Vector3(0.f, 0.f, 1.f), _turretAngle);
		
		float linkRadius = GetLinkRadius();
		Render::device.MatrixTranslate(-linkRadius, -linkRadius, 0);
		
		_turretTexture->Draw();
		
		Render::device.PopMatrix();
	}
}

FPoint CannonObject::GetLinkPoint() const
{
	return _position + _turretLinkPointShift;
}
	
float CannonObject::GetLinkRadius() const
{
	if(_turretTexture) {
		const IRect& turretRect = _turretTexture->getBitmapRect();
		int minTurretRectSize = math::min(turretRect.Width(), turretRect.Height());
		return (0.5f * static_cast<float>(minTurretRectSize));
	}
	
	return 0.f;
}
	
bool CannonObject::CanShot() const
{
	return _reloadCooldown <= 0.f;
}
	
ProjectilePtr CannonObject::Shot()
{
	_reloadCooldown = Preferences::Instance().getFloatValue("TurretReloadTime", 0.f);
	
	float projectileSpeed = Preferences::Instance().getFloatValue("ProjectileSpeed", 0.f);
	FPoint direction(projectileSpeed, 0.f);
	
	direction.Rotate(math::PI * (_turretAngle / 180.f));
	
	float projectileSize = Preferences::Instance().getFloatValue("ProjectileSize", 0.f);
	assert(projectileSize > 0);
	
	return std::make_shared<Projectile>(GetBulletOutPoint(), FPoint(projectileSize, projectileSize), direction);
}
	
void CannonObject::Update(float dt)
{
	if(_reloadCooldown > 0) {
		_reloadCooldown -= dt;
	}
	
	UpdateAngle(dt);
}
	
void CannonObject::UpdateAngle(float dt)
{
	float turretAngularVelocity = Preferences::Instance().getFloatValue("TurretAngularVelocity", 0.f);
	assert(turretAngularVelocity > 0);
	
	float rotateAngle = turretAngularVelocity * dt;
	
	if(_turretAngle < _observeAngle)
	{
		_turretAngle += rotateAngle;
		_turretAngle = math::min(_turretAngle, _observeAngle);
	}
	else if(_turretAngle > _observeAngle)
	{
		_turretAngle -= rotateAngle;
		_turretAngle = math::max(_turretAngle, _observeAngle);
	}
}
	
float normalizeAngle(float inputAngle, float maxVal, float minVal )
{
	if(inputAngle > maxVal)
	{
		inputAngle -= 2.f * math::PI;
	}
	
	if(inputAngle < minVal )
	{
		inputAngle += 2.f * math::PI;
	}
	
	return inputAngle;
}
	
void CannonObject::SetObservePoint(const FPoint& observePoint)
{
	FPoint linkPoint = GetLinkPoint();
	FPoint delta = observePoint - linkPoint;
	
	float angle = normalizeAngle(delta.GetAngle(), 3.f * math::PI/ 2.f, -math::PI / 2.f);
	
	Preferences& prefs = Preferences::Instance();
	float turretMaxAngle = prefs.getFloatValue("TurretMaxAngle", 145.f);
	float turretMinAngle = prefs.getFloatValue("TurretMinAngle", 35.f);
	
	_observeAngle = math::clamp(turretMinAngle, turretMaxAngle, angle * 180.f / math::PI);
}
	
FPoint CannonObject::GetBulletOutPoint() const
{
	FPoint result;
	
	if(_turretTexture) {
		
		float linkRadius = GetLinkRadius();
		
		const IRect& turretRect = _turretTexture->getBitmapRect();
		int maxTurretRectSize = math::max(turretRect.Width(), turretRect.Height());
		float turretLength = static_cast<float>(maxTurretRectSize) - linkRadius;
		
		result = FPoint(turretLength, 0.f);
		result.Rotate(math::PI * (_turretAngle / 180.f));
		result += GetLinkPoint();
	}
	
	return result;
}

}
