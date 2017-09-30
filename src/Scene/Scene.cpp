#include "Scene.h"
#include "Utils/Random.hpp"
#include "Objects/CircleTarget.h"
#include "Objects/Projectile.h"
#include "Objects/CannonObject.h"
#include "Preferences.h"

namespace Scene {
	
Scene::Scene()
: _cannon(nullptr)
, _isGameActive(false)
, _isPause(false)
, _timeToEnd(0.f)
, _onLevelCompleteCallback(nullptr)
, _onLevelFailureCallback(nullptr)
{
	ResetScore();
	Log::log.WriteDebug("Scene has been constructed");
}

Scene::~Scene()
{
	Log::log.WriteDebug("Scene has been destroyed");
}
	
void Scene::SetRect(const IRect& rect)
{
	_sceneRect = rect;
	
	// Обновляем область размещения целей
	unsigned bottomIndent = _sceneRect.Height() / 3;
	_targetsRect = IRect(_sceneRect.x,       _sceneRect.y + bottomIndent,
						 _sceneRect.Width(), _sceneRect.Height() - bottomIndent);
}

void Scene::Reset()
{
	ResetScore();
	
	_targets.clear();
	_isGameActive = true;
	_isPause = false;
	
	_timeToEnd = Preferences::Instance().getFloatValue("Time", 0.f);
	assert(_timeToEnd > 0);
	
	InitCannon();
	_projectiles.clear();
	GenerateTargets();
}
	
void Scene::SetPause(bool val)
{
	_isPause = val;
}
	
void Scene::TogglePause()
{
	_isPause = !_isPause;
}
	
void Scene::InitCannon()
{
	Preferences& prefs = Preferences::Instance();
	const float CANNON_BASE_WIDTH  = prefs.getFloatValue("CannonBaseWidth",  -1);
	const float CANNON_BASE_HEIGHT = prefs.getFloatValue("CannonBaseHeight", -1);
	assert(CANNON_BASE_WIDTH > 0 && CANNON_BASE_HEIGHT > 0);
	
	FPoint CannonSize(CANNON_BASE_WIDTH, CANNON_BASE_HEIGHT);
	
	const float cannonBoardlineIndent = prefs.getIntValue("CannonBoardlineIndent", 0.f);
	FPoint CannonPosition(static_cast<float>(_targetsRect.Width()) / 2.f, CannonSize.y / 2.f + cannonBoardlineIndent);
	
	_cannon.reset(new CannonObject(CannonPosition, CannonSize));
}

void Scene::GenerateTargets()
{
	Preferences& prefs = Preferences::Instance();
	
	const int TARGETS_COUNT = prefs.getIntValue("CountTarget", -1);
	assert(TARGETS_COUNT > 0);
	
	const float MIN_TARGET_RADIUS = prefs.getFloatValue("MinTargetRadius", -1);
	const float MAX_TARGET_RADIUS = prefs.getFloatValue("MaxTargetRadius", -1);
	const float TARGET_MAX_SPEED  = prefs.getFloatValue("TargetMaxSpeed", -1);
	
	assert(MIN_TARGET_RADIUS > 0 && MAX_TARGET_RADIUS > 0 && TARGET_MAX_SPEED > 0);
	
	for(unsigned i = 0; i < TARGETS_COUNT; ++i) {
		
		const float radius = math::random(MIN_TARGET_RADIUS, MAX_TARGET_RADIUS);
		
		FPoint position(math::random(_targetsRect.x  + radius,
									 _targetsRect.RightTop().x - radius),
						math::random(_targetsRect.y  + radius,
									 _targetsRect.RightTop().y - radius));
		
		FPoint direction(math::random(0.f, TARGET_MAX_SPEED), 0.f);
		direction.Rotate(math::random(0.f, 2.f * math::PI));

		CircleTargetPtr newTarget = std::make_shared<CircleTarget>(position, radius, direction);
		//newTarget->SetProcessBoarderCollisions(false);
		
		_targets.push_back(newTarget);
	}
}

void Scene::Draw()
{
	
	for(CircleTargetPtr targetPtr : _targets) {
		targetPtr->Draw();
	}
	
	for(ProjectilePtr projectilePtr : _projectiles) {
		projectilePtr->Draw();
	}
	
	if(_cannon) {
		_cannon->Draw();
	}
	
	_effCont.Draw();
}
	
void Scene::Update(float dt)
{
	if(_isPause) {
		return;
	}
	
	if(_isGameActive) {
		_timeToEnd -= dt;
		if (_timeToEnd < 0.f) {
			OnGameOver();
		}
	}

	UpdateEffects(dt);
	UpdateTargets(dt);
	UpdateProjectiles(dt);
	UpdateCannon(dt);
	
	ProcessCollisions();
}

void Scene::UpdateEffects(float dt)
{
	_effCont.Update(dt);
}
	
void Scene::UpdateTargets(float dt)
{
	CircleTargetPtrList::const_iterator it = _targets.begin();
	while(it != _targets.end())
	{
		(*it)->Update(dt, _targetsRect);
		
		if((*it)->IsMarkedOnDelete()) {
			OnPreDestroyTarget(*it);
			_targets.erase(it++);
			OnDestroyTarget();
		}
		else {
			++it;
		}
	}
}

void Scene::UpdateProjectiles(float dt)
{
	ProjectilePtrList::const_iterator it = _projectiles.begin();
	while(it != _projectiles.end())
	{
		(*it)->Update(dt, _targetsRect);
		
		if((*it)->IsMarkedOnDelete()) {
			_projectiles.erase(it++);
		}
		else {
			++it;
		}
	}
}
	
void Scene::UpdateCannon(float dt)
{
	if(_cannon) {
		_cannon->Update(dt);
	}
}
	
void Scene::ProcessCollisions()
{
	float projectileCollisionRadius = Preferences::Instance().getFloatValue("ProjectileCollisionRadius", 0.f);
	for(ProjectilePtr projectilePtr : _projectiles) {
		const FPoint& projectilePos = projectilePtr->GetPosition();
		
		for(CircleTargetPtr targetPtr : _targets) {
			if(targetPtr->IsCollisionWithCircle(projectilePos, projectileCollisionRadius)) {
				projectilePtr->SetMarkedOnDelete(true);
				targetPtr->SetMarkedOnDelete(true);
				break;
			}
		}
	}
}
	
void Scene::OnPreDestroyTarget(CircleTargetPtr obj)
{
	ParticleEffectPtr eff = _effCont.AddEffect("BubbleBoom");
	eff->SetPos( obj->GetPosition() );
	eff->Reset();
}
	
void Scene::OnDestroyTarget()
{
	if(_isGameActive) {
		IncreaseScore();
	}
}
	
void Scene::ResetScore()
{
	_currentScore = 0;
	OnScoreChanged();
}
	
void Scene::IncreaseScore()
{
	++_currentScore;
	OnScoreChanged();
}
	
unsigned Scene::GetScore() const
{
	return _currentScore;
}
	
float Scene::GetTimeToEnd() const
{
	return _timeToEnd;
}
	
void Scene::OnScoreChanged()
{
	// Проверка окончания игры
	if(_targets.empty()) {
		
		OnLevelComplete();
	}
}
	
void Scene::SetOnLevelCompleteCallback(voidCallback cb)
{
	_onLevelCompleteCallback = cb;
}
	
void Scene::SetOnLevelFailureCallback(voidCallback cb)
{
	_onLevelFailureCallback = cb;
}
	
void Scene::OnLevelComplete()
{
	_isGameActive = false;
	if(_onLevelCompleteCallback) {
		_onLevelCompleteCallback();
	}
}
	
void Scene::OnGameOver()
{
	_isGameActive = false;
	if(_onLevelFailureCallback) {
		_onLevelFailureCallback();
	}

}

bool Scene::MouseDown(const IPoint &mouse_pos)
{
	if(!_isGameActive || _isPause) {
		return false;
	}
	
	if(Core::mainInput.GetMouseLeftButton())
	{
		if(_cannon && _cannon->CanShot()) {
			ProjectilePtr newProjectile = _cannon->Shot();
			
			ParticleEffectPtr projectileTrackEffect = _effCont.AddEffect("ProjectileJet");
			newProjectile->SetTrackEffect(projectileTrackEffect);
			
			_projectiles.push_back(newProjectile);
		}
	}
	return false;
}

void Scene::MouseMove(const IPoint &mousePosition)
{
	if(_isPause) {
		return;
	}
	
	if(_cannon) {
		_cannon->SetObservePoint(mousePosition);
	}
}

void Scene::MouseUp(const IPoint &mousePosition)
{
}
	
} // End namespace Scene

