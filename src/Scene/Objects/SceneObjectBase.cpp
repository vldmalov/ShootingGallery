#include "SceneObjectBase.h"


SceneObjectBase::SceneObjectBase(const FPoint& position,
								 const FPoint& size,
								 const std::string& textureName)
: _position(position)
, _size(size)
, _angle(0.f)
, _texture(Core::resourceManager.Get<Render::Texture>(textureName))
{
	
	if(!_texture) {
		Log::log.WriteWarn("SceneObjectBase. Texture " + textureName + " doesn't exist");
	}
}

SceneObjectBase::~SceneObjectBase()
{
}

void SceneObjectBase::Draw()
{
	if(_texture) {
		
		const IRect& textureRect = _texture->getBitmapRect();
		
		FPoint scaleFactor(_size.x / static_cast<float>(textureRect.Width()),
						   _size.y / static_cast<float>(textureRect.Height()));
		
		Render::device.PushMatrix();
		Render::device.MatrixTranslate(_position.x, _position.y, 0);
		Render::device.MatrixScale(scaleFactor.x, scaleFactor.y, 1.f);
		
		Render::device.MatrixRotate(math::Vector3(0.f, 0.f, 1.f), _angle);
		Render::device.MatrixTranslate(-static_cast<float>(textureRect.Width())  / 2.f,
									   -static_cast<float>(textureRect.Height()) / 2.f, 0);
		
		_texture->Draw();
		
		Render::device.PopMatrix();
	}
}

const FPoint& SceneObjectBase::GetPosition() const
{
	return _position;
}

