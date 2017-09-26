#pragma once

#include "list"

class CircleAim;
typedef std::shared_ptr<CircleAim> CircleAimPtr;
typedef std::list<CircleAimPtr> CircleAimPtrList;

class Scene : public std::enable_shared_from_this<Scene> {

public:
	Scene();
	~Scene();
	
	void setPlaygroundRect(const IRect& rect);
	const IRect& getPlaygroundRect() const;
	void Reset();
	
	void Draw();
	void Update(float dt);
	
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);
	void MouseUp(const IPoint& mouse_pos);
	
	
	void SetPause(bool onPause);
	
private:
	void Init();
	void RenderSplineObject();
	
private:
	bool _onPause;
	
private:
	
	IRect _playgroundRect;
	
	float _timer;
	
	float _scale;
	float _angle;
	
	Render::Texture* _tex1;
	Render::Texture* _tex2;
	Render::Texture* _tex3;
	int _curTex;
	
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
	
	TimedSpline<FPoint> spline;
	
	CircleAimPtrList _aims;
};
