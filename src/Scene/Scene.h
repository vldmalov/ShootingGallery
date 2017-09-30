#pragma once

#include "list"

namespace Scene {
	
typedef std::function<void(void)> voidCallback;
	
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
	void SetPause(bool val);
	void TogglePause();
	
	void Draw();
	void Update(float dt);
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);
	
	unsigned GetScore() const;
	float GetTimeToEnd() const;
	
	void SetOnLevelCompleteCallback(voidCallback cb);
	void SetOnLevelFailureCallback(voidCallback cb);
	
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
	void OnDestroyTarget();
	
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
	
	// Игра на паузе
	bool _isPause;
	
	// Текущее количество очков
	unsigned _currentScore;
	
	// Время до завершения раунда
	float _timeToEnd;
	
	// Каллбеки на завершение игры
	voidCallback _onLevelCompleteCallback;
	voidCallback _onLevelFailureCallback;
	
};
	
} // End namespace Scene
