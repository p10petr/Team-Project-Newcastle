#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	

	AssetsManager::GOInstance = new SimpleMeshObject("ground1");//Floor
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f,0.0f,0.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol1";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.0f, 1.0f, 150.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground2");  //Right Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol2";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 35.5f, -184.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-135, 0, 0));


	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground3"); //Left Bottom
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, -0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol3";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 34.f, 184.5f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(135, 0, 0));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground4");  //right Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol4";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 91.f, -219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 20.0f, 1.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground5"); //Left Middle
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 20.0f, 1.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, 0));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol5";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 89.f, 219.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 20.0f, 1.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground6"); //Left top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol6";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.f, 185.f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(45, 0, 0));

	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground7"); //Right top
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false); 
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 50.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "groundcol7";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 145.5f, -184.5f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 1.0f, 50.0f)));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-45, 0, 0));

	m_scene->AddGameObject(AssetsManager::GOInstance);


	AssetsManager::GOInstance = new SimpleMeshObject("ground8");// Roof
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(150.f, 1.0f, 150.0f))*Matrix4::Translation(Vector3(0.0f, 0.f, 0.f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 1.0f, 1.f, 0.2f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name="groundcol8";
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 180.f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(150.f, 1.0f, 150.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("car");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(1.0f, 0.5f, 1.f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	ParticleEmitter* rainbow = new ParticleEmitter();
	rainbow->SetParticleSize(1.0f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(16.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);

	rainbow->SetSourcePosition(Vector3(10, 10, 10));
	m_scene->AddParticleObject(rainbow);

	/*AssetsManager::GOInstance = new SimpleMeshObject("car");
	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));*/

	m_scene->AddGameObject(AssetsManager::GOInstance);
}

