#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "HeaderSymbol.h"

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "box2d/box2d.h"
#include "Resource.h"



using namespace std;

class GameObject;
struct PhysicProp
{
	string name = "";
	ObjectType objectType;
	float width = 0.f;
	float height = 0.f;
	GameObject* go = nullptr;
};

class GameObject 
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void create(unsigned int shader = 0) = 0;
	void CreateTexture(Resource*);
	virtual void draw() = 0;

	inline void setLinePosition(b2Vec2 position1, b2Vec2 position2) {
		linePos1 = position1;
		linePos2 = position2;
	}

	void updateObjectPosition(b2Vec2 offset = {0.f, 0.f});
	void updateObjectUV();


// getter and setter
public:
	inline PhysicProp* getPhysicProp() {
		return physicProp;
	}
	inline bool getDispose() {
		return dispose;
	}
	inline void setDispose(bool dispose) {
		this->dispose = dispose;
	}
	inline bool getHide() {
		return hide;
	}
	inline void setHide(bool hide) {
		this->hide = hide;
	}
	inline b2Vec2 getPosition() {
		return body->GetWorldCenter();
	}
	inline void setPosition(b2Vec2 position) {
		this->position = position;
	}
	bool isTriggerAnimation() const {
		return triggerAnimation;
	}
	void setTriggerAnimation(bool triggerAnimation = false) {
		this->triggerAnimation = triggerAnimation;
	}
	void setPosition() {
		body->SetTransform(position, body->GetAngle());
	}
	bool isRemovePhysic() const {
		return removePhysic;
	}
	void setRemovePhysic(bool removePhysic = false) {
		this->removePhysic = removePhysic;
	}
	void setBoxCount(int boxCount = 0) {
		this->boxCount = boxCount;
	}


protected:
	void createBuffer();
	void createInstanceBuffer();
	void initRectPhysics(b2BodyType, b2Vec2, float angle = 0.0f);
	void initPhysics(b2Vec2, b2Vec2);
	void initPhysics(b2BodyType, b2Vec2, float);

	unsigned int inst = 0;
	int boxCount = 0;

	glm::vec2 translation[30]; // create enough room to hold the sprite position
	
	float vertices[32];
	
	unsigned int indices[6] = {
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	glm::mat4 transformGameObject = glm::mat4(1.f);

	PhysicProp* physicProp = new PhysicProp();

	b2World* physicWorld;
	b2Body* body;

	unsigned int vao = 0;
	unsigned int vbo = 0;
	unsigned int idc = 0;
	unsigned int tex = 0;

	b2Vec2 position = {0.f, 0.f};
	b2Vec2 linePos1 = {0.f, 0.f};
	b2Vec2 linePos2 = {0.f, 0.f};

	unsigned int transformLoc = 0;
	unsigned int offsetLocation = 0;

	bool triggerAnimation = false;


private:
	bool dispose = false;
	bool hide = false;
	bool removePhysic = false;
};

#endif /* GAMEOBJECT_H_ */
