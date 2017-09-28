#pragma once

#include "SceneDynamicObject.h"

namespace Scene {
	
class Projectile : public SceneDynamicObject
{
public:
	typedef SceneDynamicObject baseclass;
	
	Projectile(const FPoint& position, const FPoint& size, const FPoint& direction);
	virtual ~Projectile();
	
	virtual void Update(float dt, const IRect& boundingBox) override;
	
	void SetTrackEffect(ParticleEffectPtr effect);
	
private:
	virtual void OnBottomBoardCollision(float collisionSize) override;
	
	// Положение эффекта шлейфа от проджектайла
	FPoint GetJetPosition() const;

private:
	float _gravityFactor;
	ParticleEffectPtr _trackEffect;
};
	
}
