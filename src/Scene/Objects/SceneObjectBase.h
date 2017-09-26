#pragma once

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
	Render::Texture* _texture;
};

typedef std::shared_ptr<SceneObjectBase> SceneObjectBasePtr;
