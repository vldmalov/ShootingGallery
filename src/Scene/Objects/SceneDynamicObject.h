#pragma once

#include "SceneObjectBase.h"

namespace Scene {

class SceneDynamicObject : public SceneObjectBase
{
public:
	typedef SceneObjectBase baseclass;
	SceneDynamicObject(const FPoint& position, const FPoint& size,
					   const FPoint& direction, const std::string& textureName);
	
	virtual void Update(float dt, const IRect& boundingBox);
	
	void SetProcessBoarderCollisions(bool val) { _processBoarderCollisions = val; }
	bool GetProcessBoarderCollisions() const { return _processBoarderCollisions; }
	
	void SetMarkedOnDelete(bool val) { _isMarkedOnDelete = val; }
	bool IsMarkedOnDelete() const { return _isMarkedOnDelete; }
	
	const FPoint& GetDirection() const;
	
private:
	
	void CheckAndProcessCollisions(const IRect& boundingBox);
	virtual void OnSideBoardCollision  (float collisionSize);
	virtual void OnTopBoardCollision   (float collisionSize);
	virtual void OnBottomBoardCollision(float collisionSize);
	
protected:
	FPoint _direction;
	bool   _processBoarderCollisions;
	bool   _isMarkedOnDelete;
};

}
