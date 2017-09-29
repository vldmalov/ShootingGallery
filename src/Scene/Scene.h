#pragma once

#include "list"

namespace Scene {
	
class SceneDynamicObject;
typedef std::shared_ptr<SceneDynamicObject> SceneDynamicObjectPtr;
typedef std::list<SceneDynamicObjectPtr> SceneDynamicObjectPtrList;

class CircleTarget;
typedef std::shared_ptr<CircleTarget> CircleTargetPtr;
typedef std::list<CircleTargetPtr> CircleTargetPtrList;
	
class Projectile;
typedef std::shared_ptr<Projectile> ProjectilePtr;
typedef std::list<ProjectilePtr> ProjectilePtrList;
	
class CannonObject;
typedef std::unique_ptr<CannonObject> CannonObjectPtr;

class Scene {

public:
	Scene();
	~Scene();
	
	void SetRect(const IRect& rect);
	
	void Reset();
	
	void Draw();
	void Update(float dt);
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);
	
	unsigned GetScore() const;
	
private:
	void InitCannon();
	
	void GenerateTargets();
	
	void OnLevelComplete();
	void OnGameOver();
	
	void UpdateEffects(float dt);
	void UpdateTargets(float dt);
	void UpdateProjectiles(float dt);
	void UpdateCannon(float dt);
	
	void ProcessCollisions();
	
	void OnPreDestroyTarget(CircleTargetPtr obj);
	void OnPreDestroyProjectile(ProjectilePtr obj);
	
	void ResetScore();
	void IncreaseScore();
	void OnScoreChanged();
	
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	
private:
	
	// Игровые объекты
	CannonObjectPtr		_cannon;
	CircleTargetPtrList _targets;
	ProjectilePtrList   _projectiles;
	
	// Контейнер эффектов
	EffectsContainer _effCont;
	
	// Прямоугольник всей сцены
	IRect _sceneRect;
	
	// Прямоугольник размещения целей
	IRect _targetsRect;
	
	// Игра в процессе
	bool _isGameActive;
	
	// Текущее количество очков
	unsigned _currentScore;
	
	// Время до завершения раунда
	float _timeToEnd;
	
};
	
} // End namespace Scene
