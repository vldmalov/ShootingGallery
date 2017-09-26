#pragma once

#include "SceneObjectBase.h"

class SceneDynamicObject : public SceneObjectBase
{
public:
	typedef SceneObjectBase baseclass;
	SceneDynamicObject(const FPoint& position, const FPoint& size,
					   const FPoint& direction, const std::string& textureName);
	
	virtual void Update(float dt, const IRect& boundingBox);
	
	const FPoint& GetDirection() const;
	
private:
	void CheckAndProcessBoarderCollision(float& position, float& direction, float size,
										 float boarderMin, float boarderMax);
	
protected:
	FPoint _direction;
};
