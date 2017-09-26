#pragma once

#include "SceneDynamicObject.h"

class CircleTarget : public SceneDynamicObject
{
public:
	typedef SceneDynamicObject baseclass;
	
	CircleTarget(const FPoint& position, float radius, const FPoint& direction);
	
	void Draw() override;
	void Update(float dt, const IRect& boundingBox) override;
	
	float GetRadius() const;
};

typedef std::shared_ptr<CircleTarget> CircleTargetPtr;
