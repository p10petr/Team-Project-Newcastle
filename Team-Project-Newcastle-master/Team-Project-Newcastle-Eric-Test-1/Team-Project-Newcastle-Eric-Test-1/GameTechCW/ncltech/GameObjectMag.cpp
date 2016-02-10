#include "GameObjectMag.h"

void	GameObjectMag::GOMInit(Scene* m_scene) 
{
	

	Vector3 Proj_dir;
	Proj_dir.x = -sin(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.z = -cos(m_scene->m_Camera->GetYaw() * PI / 180.0f);
	Proj_dir.y = sin(m_scene->m_Camera->GetPitch() * PI / 180.0f);
	Proj_dir.Normalise();

	ParticleEmitter* rainbow = new ParticleEmitter();

	rainbow->SetParticleSize(1.0f);
	rainbow->SetParticleVariance(1.0f);
	rainbow->SetLaunchParticles(16.0f);
	rainbow->SetParticleLifetime(100.0f);
	rainbow->SetParticleSpeed(0.1f);

	rainbow->SetSourcePosition(Vector3(10 , 10, 10));
	m_scene->AddParticleObject(rainbow);

	AssetsManager::GOInstance = new SimpleMeshObject("ground");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->GetMesh()->SetTexture(AssetsManager::m_glass);
	//AssetsManager::GOInstance->GetMesh()->SetBumpMap(AssetsManager::m_glassBump);
	
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(50.0f, 1.0f, 70.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground";
	//AssetsManager::GOInstance->Physics()->SetInverseMass(1.0f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(50.0f, 1.0f, 70.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("ground_2");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->GetMesh()->SetTexture(AssetsManager::m_CheckerboardTex);
	//AssetsManager::GOInstance->GetMesh()->SetBumpMap(AssetsManager::m_glassBump);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 50.0f, 70.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "ground_2";
	//AssetsManager::GOInstance->Physics()->SetInverseMass(1.0f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(50.0f, 0.0f, 0.0f));
	AssetsManager::GOInstance->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0, 0, -30));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 50.0f, 70.0f)));

	m_scene->AddGameObject(AssetsManager::GOInstance);

	//AssetsManager::GOInstance = new SimpleMeshObject("ground_3");

	//AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	////AssetsManager::GOInstance->GetMesh()->SetTexture(AssetsManager::m_glass);
	////AssetsManager::GOInstance->GetMesh()->SetBumpMap(AssetsManager::m_glassBump);

	//AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(50.0f, 1.0f, 70.0f)));
	//AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	//AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	//AssetsManager::GOInstance->Physics()->name = "ground_3";
	////AssetsManager::GOInstance->Physics()->SetInverseMass(1.0f);
	//AssetsManager::GOInstance->Physics()->SetPosition(Vector3(0.0f, 100.0f, 0.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(50.0f, 1.0f, 70.0f)));

	//m_scene->AddGameObject(AssetsManager::GOInstance);

	AssetsManager::GOInstance = new SimpleMeshObject("car");

	AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	AssetsManager::GOInstance->Physics()->name = "car";
	AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	//AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(2.0f, 2.0f, 2.0f)));
	m_scene->AddGameObject(AssetsManager::GOInstance);

	//AssetsManager::GOInstance = new SimpleMeshObject("light");

	//AssetsManager::GOInstance->SetMesh(AssetsManager::Cube(), false);
	//AssetsManager::GOInstance->SetLocalTransform(Matrix4::Scale(Vector3(1.0f, 1.0f, 1.0f)));
	//AssetsManager::GOInstance->SetColour(Vector4(0.2f, 1.0f, 0.5f, 1.0f));
	//AssetsManager::GOInstance->SetBoundingRadius(80.0f * 80.f);

	//AssetsManager::GOInstance->Physics()->name = "light";
	////AssetsManager::GOInstance->Physics()->SetInverseMass(0.2f);
	////AssetsManager::GOInstance->Physics()->SetPosition(Vector3(10.0f, 10.0f, 10.0f));
	////AssetsManager::GOInstance->Physics()->SetCollisionShape(new CuboidCollisionShape(Vector3(1.0f, 1.0f, 1.0f)));
	////AssetsManager::GOInstance->Physics()->SetCollisionShape(new SphereCollisionShape(1.0f));
	//m_scene->AddGameObject(AssetsManager::GOInstance);
}

