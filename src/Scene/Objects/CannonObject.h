#pragma once

#include "SceneObjectBase.h"

namespace Scene {
	
class Projectile;
typedef std::shared_ptr<Projectile> ProjectilePtr;
	
class CannonObject : public SceneObjectBase
{
public:
	typedef SceneObjectBase baseclass;
	
	CannonObject(const FPoint& position, const FPoint& size);
	
	virtual void Draw() override;
	virtual void Update(float dt);
	
	void SetObservePoint(const FPoint& observePoint);
	
	bool CanShot() const;
	ProjectilePtr Shot();
	
private:
	void UpdateAngle(float dt);
	
	FPoint GetLinkPoint() const;
	float  GetLinkRadius() const;
	FPoint GetBulletOutPoint() const;
	
private:
	float _turretAngle;
	float _observeAngle;
	Render::Texture* _turretTexture;
	
	FPoint _turretLinkPointShift;
	float _reloadCooldown;
};
	
}
