#pragma once

#include <ncltech\SimpleMeshObject.h>
#include <nclgl\Camera.h>

class BaseState; //foreward declaration of base state so compiler is awware of base states existance

class ArbitraryAI : public SimpleMeshObject { //ArbitraryAI object inherits from simplemeshobject and holds information of AI's hitbox and physics
public:
	ArbitraryAI(const std::string& name, Camera* cameraInstance, const int& radius); //on instantiation must pass its constructor name string to be given to simplemesh object (as its constructor requires it), creates string of inheritance GameObject->SimpleMeshObject->ArbitraryAI || also pass the instance of the camera to the AI so that it can access things like GetPosition
	ArbitraryAI();
	~ArbitraryAI();

	virtual void OnUpdateObject(float dt) override; //actions to be performed each update of the object, ie each frame, overrides onupdateobject in GameObject so that rather than having its velocity dictated entirely by the physics engine you can use your own logic to give it position velocity etc (still affected by collisions though)

	virtual void SetState(int newStateEnum); //sets the state of the AI, used by trigger check methods (located in ai state classes) to change which state BaseState* currentState points too 

	Vector3 GetCameraPosition()			 { return camera->GetPosition(); } 

private:
	BaseState* currentState; //pointer to the current state of the state machine, ie u can use currentState in methods within ArbitraryAI to do broadly the same thing, while the implementation changes depending on which state currentState is actually pointing too

	Camera* camera;
};
