#pragma once

#include "SceneDynamicObject.h"

namespace Scene {
	
class CircleTarget : public SceneDynamicObject
{
public:
	typedef SceneDynamicObject baseclass;
	
	CircleTarget(const FPoint& position, float radius, const FPoint& direction);
	
	void Draw() override;
	void Update(float dt, const IRect& boundingBox) override;
	
	bool IsPointInTarget(const FPoint& point) const;
	
	float GetRadius() const;
};

typedef std::shared_ptr<CircleTarget> CircleTargetPtr;
	
}
