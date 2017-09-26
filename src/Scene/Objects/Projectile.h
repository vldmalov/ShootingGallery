#pragma once

#include "SceneDynamicObject.h"

class Projectile : public SceneDynamicObject
{
public:
	typedef SceneDynamicObject baseclass;
	
	Projectile(const FPoint& position, const FPoint& direction, const FPoint& size);
	
	virtual void Draw() override;
	virtual void Update(float dt, const IRect& boundingBox) override;

};

typedef std::shared_ptr<Projectile> ProjectilePtr;
