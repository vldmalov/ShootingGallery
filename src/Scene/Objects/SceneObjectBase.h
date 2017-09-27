#pragma once

namespace Scene {
	
class SceneObjectBase {
	
public:
	SceneObjectBase(const FPoint& position, const FPoint& size, const std::string& textureName);
	virtual ~SceneObjectBase();
	
	virtual void Draw();
	
	const FPoint& GetPosition() const;
	
protected:
	FPoint _position;
	FPoint _size;
	float  _angle;
	
private:
	Render::Texture* _texture;
};

}
