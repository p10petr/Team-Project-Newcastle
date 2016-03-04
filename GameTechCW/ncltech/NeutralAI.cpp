#include <nclgl/OBJMesh.h>
#include <ncltech\SimpleMeshObject.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\AssetsManager.h>
#include <ncltech\NCLDebug.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\SphereCollisionShape.h>
//#include <ncltech\PyramidCollisionShape.h>
#include <ncltech\Scene.h>

#include "NeutralAI.h"
#include "Chase.h"
#include "Dribble.h"

NeutralAI::NeutralAI(const std::string& name, Scene* m_scene) : SimpleMeshObject(name) {

	SetMesh(AssetsManager::Cube(), false);
	SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	SetColour(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	SetBoundingRadius(80.0f * 80.f);
	Physics()->name = name.c_str();
	Physics()->SetInverseMass(0.06f);
	Physics()->SetPosition(Vector3(30.0f, 5.0f, 60.0f));
	Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	scene = m_scene;

	currentState = new Chase(); //sets the initial current state for the first frame (actually instantiates the state when the state is changed, so you dont have inactive states instantiated and sitting in memory doing nothing, ie rather than creating all states at startup and just changing the pointed, create and delkete states as they are used
}

NeutralAI::~NeutralAI() {

}

void NeutralAI::OnUpdateObject(float dt) {
	//Physics()->SetPause(false); 

	//currentState->ForceCalculator(this); //every frame call the ForceCalculator method of currentState 
}

void NeutralAI::SetState(int setStateEnum) { //sets the state of the AI (when you call setstate you pass it an integer, and depending on which integer is passed a different state is chosen to be instantiated.
	delete currentState;

	if (setStateEnum == 1) {
		currentState = new Chase();
	}

	if (setStateEnum == 2) {
		currentState = new Dribble();
	}
}

//Chase == 1
//Dribble == 2

void NeutralAI::UpdateAI() {
	currentState->ForceCalculator(this);
}

Vector3 NeutralAI::DirectionCalculation(Vector3 to, Vector3 from) {
	Vector3 directionvector;

	directionvector = to - from;
	directionvector.Normalise();

	return directionvector;
}

void NeutralAI::RotationCalculation(Vector3 defendnode) {
	float dotproduct, angle;
	Vector3 crossproduct;

	NormalCal();
	dotproduct = Vector3::Dot(DirectionVector, GetFrontNormal());
	angle = acos(dotproduct);

	angle = angle * 57.3f;

	if (angle < 1.0f) {
		right = false;
		left = false;
		return;
	}

	crossproduct = Vector3::Cross(DirectionVector, GetFrontNormal());

	if (crossproduct.y > 0) {
		right = true;
		left = false;
	}

	if (crossproduct.y <= 0) {
		right = false;
		left = true;
	}
}



void NeutralAI::ForwardBackwardCalculation(float disttonode) {
	float currentforwardspeed, currentbackwardspeed, currentleftspeed, currentrightspeed;
	float maxspeed;

	//cout << disttonode << endl;

	maxspeed = disttonode * 1.3f;

	currentforwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetFrontNormal());
	currentbackwardspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRearNormal());
	currentleftspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetLeftNormal());
	currentrightspeed = Vector3::Dot(Physics()->GetLinearVelocity(), GetRightNormal());

	if (currentleftspeed > (maxspeed * 0.7) || currentrightspeed > (maxspeed * 0.7)) {
		forward = 0;
		reverse = 0;
		return;
	}

	{
		if (currentforwardspeed <= 0.0f) {
			currentforwardspeed = 0;
		}

		if (currentbackwardspeed <= 0.0f) {
			currentbackwardspeed = 0;
		}
	}

	{
		if (currentforwardspeed <= maxspeed) {
			forward = 1;
			reverse = 0;
		}

		if (currentforwardspeed > maxspeed) {
			forward = 0;
			reverse = 1;
		}
	}
}