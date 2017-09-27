#pragma once

#include "SceneDynamicObject.h"

namespace Scene {
	
class Projectile : public SceneDynamicObject
{
public:
	typedef SceneDynamicObject baseclass;
	
	Projectile(const FPoint& position, const FPoint& size, const FPoint& direction);
	
	virtual void Update(float dt, const IRect& boundingBox) override;
	
private:
	virtual void OnBottomBoardCollision(float collisionSize) override;

private:
	float _gravityFactor;
};
	
}
