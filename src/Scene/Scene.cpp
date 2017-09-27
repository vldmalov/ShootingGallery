#include "Scene.h"
#include "Utils/Random.hpp"
#include "Objects/CircleTarget.h"
#include "Objects/Projectile.h"
#include "Preferences.h"

namespace Scene {
	
Scene::Scene()
: _onPause(false)
, _curTex(0)
, _timer(0)
, _angle(0)
, _eff(nullptr)
, _scale(0.f)
, _timeToEnd(0.f)
, _timeIsOver(false)
, _playgroundRect()
{
	Init();
	Log::log.WriteDebug("Scene has been constructed");
}

Scene::~Scene()
{
	Log::log.WriteDebug("Scene has been destroyed");
}


void Scene::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("btnStart_Text");
	_tex2 = Core::resourceManager.Get<Render::Texture>("Circle"); // Circle
	_tex3 = Core::resourceManager.Get<Render::Texture>("Star");
	
	
	_curTex = 0;
	_angle = 0;
	
	spline.addKey(0.0f, FPoint(100.0f, 100.0f));
	spline.addKey(0.2f, FPoint(150.0f, 300.0f));
	spline.addKey(0.55f, FPoint(500.0f, 300.0f));
	spline.addKey(0.75f, FPoint(630.0f, 450.0f));
	spline.addKey(1.0f, FPoint(600.0f, 550.0f));
	spline.CalculateGradient();
}

void Scene::Reset()
{
	_targets.clear();
	_timeIsOver = false;
	
	Preferences& prefs = Preferences::Instance();
	int gameTime = prefs.getIntValue("Time", -1);
	assert(gameTime > 0);
	
	_timeToEnd = static_cast<float>(gameTime);
	GenerateTargets();
}

void Scene::GenerateTargets()
{
	Preferences& prefs = Preferences::Instance();
	const int TARGETS_COUNT = prefs.getIntValue("CountTarget", -1);
	assert(TARGETS_COUNT > 0);
	
	const int MIN_T_RADIUS = prefs.getIntValue("MinTargetRadius", -1);
	const int MAX_T_RADIUS = prefs.getIntValue("MaxTargetRadius", -1);
	const int TARGET_MAX_SPEED = prefs.getIntValue("TargetMaxSpeed", -1);
	
	assert(MIN_T_RADIUS > 0 && MAX_T_RADIUS > 0 && TARGET_MAX_SPEED > 0);
	
	for(unsigned i = 0; i < TARGETS_COUNT; ++i) {
		
		const float radius = math::random(static_cast<float>(MIN_T_RADIUS),
										  static_cast<float>(MAX_T_RADIUS));
		
		FPoint position(math::random(_playgroundRect.x  + radius,
									 _playgroundRect.RightTop().x - radius),
						math::random(_playgroundRect.y  + radius,
									 _playgroundRect.RightTop().y - radius));
		
		float maxSpeed = static_cast<float>(TARGET_MAX_SPEED);
		FPoint direction(math::random(-maxSpeed, maxSpeed),
						 math::random(-maxSpeed, maxSpeed));

		CircleTargetPtr newTarget = std::make_shared<CircleTarget>(position, radius, direction);
		//newTarget->SetProcessBoarderCollisions(false);
		
		_targets.push_back(newTarget);
	}
}

void Scene::setPlaygroundRect(const IRect& rect)
{
	_playgroundRect = rect;
	
	Reset();
}

const IRect& Scene::getPlaygroundRect() const
{
	return _playgroundRect;
}

void Scene::SetPause(bool onPause)
{
	_onPause = onPause;
}

void Scene::DrawObjects(const SceneDynamicObjectPtrList& objectList)
{
	for(SceneDynamicObjectPtr objectPtr : objectList) {
		objectPtr->Draw();
	}
}

void Scene::Draw()
{
	//
	// Получаем текущее положение курсора мыши.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	
	//
	// Проталкиваем в стек текущее преобразование координат, чтобы в дальнейшем
	// можно было восстановить это преобразование вызовом PopMatrix.
	//
	Render::device.PushMatrix();
	
	//
	// Изменяем текущее преобразование координат, перемещая центр координат в позицию мыши
	// и поворачивая координаты относительно этого центра вокруг оси z на угол _angle.
	//
	Render::device.MatrixTranslate((float)mouse_pos.x, (float)mouse_pos.y, 0);
	Render::device.MatrixRotate(math::Vector3(0, 0, 1), _angle);
	
	/*
	if (!_curTex)
	{
		//
		// Метод Texture::Draw() выводит квадратный спрайт с размерами текстуры
		// в центре координат (0, 0). Центр координат и преобразование координат вершин
		// спрайта устанавливаются с применением текущего преобразования.
		//
		// При вызове метода Texture::Draw() вызывать Texture::Bind() необязательно.
		//
		_tex1->Draw();
	}
	else
	{
		IRect texRect = _tex2->getBitmapRect();
		
		//
		// При отрисовке текстуры можно вручную задавать UV координаты той части текстуры,
		// которая будет натянута на вершины спрайта. UV координаты должны быть нормализованы,
		// т.е., вне зависимости от размера текстуры в текселях, размер любой текстуры
		// равен 1 (UV координаты задаются в диапазоне 0..1, хотя ничто не мешает задать их
		// больше единицы, при этом в случае установленной адресации текстуры REPEAT, текстура
		// будет размножена по этой стороне соответствующее количество раз).
		//
		
		FRect rect(texRect);
		FRect uv(0.25, 0.75, 0.25, 0.75);
		
		_tex2->TranslateUV(rect, uv);
		
		Render::device.MatrixScale(_scale);
		Render::device.MatrixTranslate(-texRect.width * 0.5f, -texRect.height * 0.5f, 0.0f);
		
		//
		// Привязываем текстуру.
		//
		_tex2->Bind();
		
		//
		// Метод DrawQuad() выводит в графическое устройство квадратный спрайт, состоящий их двух
		// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
		// если разрешено текстурирование.
		//
		// Перед вызовом DrawQuad() должен быть вызов Texture::Bind() либо SetTexturing(false),
		// иначе визуальный результат будет непредсказуемым.
		//
		Render::DrawQuad(rect, uv);
	}
	 */
	
	//
	// Воостанавливаем прежнее преобразование координат, снимая со стека изменённый фрейм.
	//
	Render::device.PopMatrix();
	
	DrawObjects(_targets);
	DrawObjects(_projectiles);
	
	// RenderSplineObject();
	
	//
	// Этот вызов отключает текстурирование при отрисовке.
	//
	Render::device.SetTexturing(false);
	
	//
	// Метод BeginColor() проталкивает в стек текущий цвет вершин и устанавливает новый.
	//
	Render::BeginColor(Color(255, 128, 0, 255));
	
	//
	// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
	// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
	// если разрешено текстурирование.
	//
	// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
	// иначе визуальный результат будет непредсказуемым.
	//
	Render::DrawRect(924, 0, 100, 100);
	
	//
	// Метод EndColor() снимает со стека текущий цвет вершин, восстанавливая прежний.
	//
	Render::EndColor();
	
	//
	// Опять включаем текстурирование.
	//
	Render::device.SetTexturing(true);
	
	//
	// Рисуем все эффекты, которые добавили в контейнер (Update() для контейнера вызывать не нужно).
	//
	_effCont.Draw();
	
	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
	Render::PrintString(924 + 100 / 2, 55, utils::lexical_cast(static_cast<int>(_timeToEnd)) + " sec", 1.f, CenterAlign);
	
}

//float getAngle(const FPoint& from, const FPoint& to)
//{
//	const double EPS = 1.0E-8;
//	
//	FPoint delta = to - from;
//	
//	if(fabs(delta.x) <= EPS) {
//		return 180.f * math::PI / 2.f;
//	}
//	
//	if(fabs(delta.y) <= EPS) {
//		return 0.0f;
//	}
//	
//	return 180.f * math::atan(delta.y, delta.x);
//}

//void Scene::RenderSplineObject()
//{
//	//
//	// Получаем текущие координаты объекта, двигающегося по сплайну
//	//
//	
//	const float DELTA = 1.0E-4;
//	
//	float splineProgress = math::clamp(0.0f, 1.0f, _timer / (2 * math::PI));
//	FPoint currentPosition = spline.getGlobalFrame(splineProgress);
//	
//	FPoint from, to;
//	if(splineProgress >= DELTA) {
//		float beforeProgress = math::clamp(0.0f, 1.0f, splineProgress - DELTA);
//		from = spline.getGlobalFrame(beforeProgress);
//		to = currentPosition;
//	} else {
//		float afterProgress = math::clamp(0.0f, 1.0f, splineProgress + DELTA);
//		from = currentPosition;
//		to = spline.getGlobalFrame(afterProgress);
//	}
//	
//	
//	float angle = getAngle(from, to);
//	
//	//
//	// И рисуем объект в этих координатах
//	//
//	Render::device.PushMatrix();
//	
//	Render::device.MatrixTranslate(currentPosition.x, currentPosition.y, 0);
//	Render::device.MatrixRotate(math::Vector3(0.f, 0.f, 1.f), angle);
//	_tex3->Draw();
//	Render::device.PopMatrix();
//}

void Scene::OnTimeOver()
{
	_timeIsOver = true;
	
	// Show results
	// Show menu
}

void Scene::UpdateObjects(SceneDynamicObjectPtrList& objectList, float dt)
{
	SceneDynamicObjectPtrList::const_iterator it = objectList.begin();
	while(it != objectList.end())
	{
		(*it)->Update(dt, _playgroundRect);
		
		if((*it)->IsMarkedOnDelete()) {
			objectList.erase(it++);
		}
		else {
			++it;
		}
	}
}

void Scene::Update(float dt)
{
	_timeToEnd -= dt;
	if (_timeToEnd < 0.f && !_timeIsOver) {
		OnTimeOver();
	}
	
	if(_timeIsOver) {
		return;
	}
	//
	// Обновим контейнер с эффектами
	//
	_effCont.Update(dt);
	
	UpdateObjects(_targets,     dt);
	UpdateObjects(_projectiles, dt);
	
	for(SceneDynamicObjectPtr projectilePtr : _projectiles) {
		const FPoint& projectilePos = projectilePtr->GetPosition();
	
		for(SceneDynamicObjectPtr objectPtr : _targets) {
			CircleTargetPtr targetPtr = dynamic_pointer_cast<CircleTarget>(objectPtr);
			if(targetPtr) {
				if(targetPtr->IsPointInTarget(projectilePos)) {
					projectilePtr->SetMarkedOnDelete(true);
					targetPtr->SetMarkedOnDelete(true);
				}
			}
		}
	}
	
	//
	// dt - значение времени в секундах, прошедшее от предыдущего кадра.
	// Оно может принимать разные значения, в зависимости от производительности системы
	// и сложности сцены.
	//
	// Для того, чтобы наша анимация зависела только от времени, и не зависела от
	// производительности системы, мы должны рассчитывать её от этого значения.
	//
	// Увеличиваем наш таймер с удвоенной скоростью.
	//
	
	_timer += dt; // * 2;
	
	//
	// Зацикливаем таймер в диапазоне (0, 2п).
	// Это нужно делать для предотвращения получения некорректных значений,
	// если вдруг переполнится разрядная сетка (float переполнился) или задержка
	// от предыдущего кадра была слишкой большой (система тормози-и-ит).
	//
	// Диапазон значений выбран равным (0, 2п), потому что мы используем это значение
	// для расчёта синуса, и большие значения будут просто периодически повторять результат.
	//
	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
	}
	
	//
	// Анимирование параметра масштабирования в зависимости от таймера.
	//
	_scale = 0.8f + 0.25f * sinf(_timer);
}


bool Scene::MouseDown(const IPoint &mouse_pos)
{
	if(_timeIsOver) {
		return false;
	}
	
	if (Core::mainInput.GetMouseRightButton())
	{
		//
		// При нажатии на правую кнопку мыши, создаём эффект шлейфа за мышкой.
		//
//		_eff = _effCont.AddEffect("Iskra");
//		_eff->posX = mouse_pos.x + 0.f;
//		_eff->posY = mouse_pos.y + 0.f;
//		_eff->Reset();
//		
//		//
//		// И изменяем угол наклона текстуры.
//		//
//		_angle += 25;
//		while (_angle > 360)
//		{
//			_angle -= 360;
//		}
	}
	else
	{
		const float PROJECTILE_SPEED(200.f);
		FPoint GunPosition = {600.f, 0.f};
		FPoint direction(static_cast<float>(mouse_pos.x) - GunPosition.x,
						 static_cast<float>(mouse_pos.y) - GunPosition.y);
		direction.Normalize();
		direction *= PROJECTILE_SPEED;
		FPoint size(35.f, 35.f);
		ProjectilePtr projectile = std::make_shared<Projectile>(GunPosition, size, direction);
		_projectiles.push_back(projectile);
		
		//
		// При нажатии на левую кнопку мыши, создаём временный эффект, который завершится сам.
		//
//		ParticleEffectPtr eff = _effCont.AddEffect("FindItem2");
//		eff->posX = mouse_pos.x + 0.f;
//		eff->posY = mouse_pos.y + 0.f;
//		eff->Reset();
//		
//		//
//		// Изменяем значение с 0 на 1 и наоборот.
//		//
//		_curTex = 1 - _curTex;
	}
	return false;
}

void Scene::MouseMove(const IPoint &mouse_pos)
{
	if (_eff)
	{
		//
		// Если эффект создан, то перемещаем его в позицию мыши.
		//
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
	}
}

void Scene::MouseUp(const IPoint &mouse_pos)
{
	if (_eff)
	{
		//
		// Если эффект создан, то при отпускании мыши завершаем его.
		//
		_eff->Finish();
		_eff = NULL;
	}
}
	
} // End namespace Scene

