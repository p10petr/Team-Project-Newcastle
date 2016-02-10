#include "Scene.h"
#include "AssetsManager.h"
#include "NCLDebug.h"
#include "PhysicsEngine.h"
#include <algorithm>

Scene::Scene(Window& window) : OGLRenderer(window)
{	
	//used as friend class
	AssetsManager::InitializeMeshes();


	/*m_DebugShader = new Shader(SHADERDIR"debugVertex.glsl", SHADERDIR"debugFragment.glsl");
	if (!m_DebugShader->LinkProgram()){
		return;
	}
	
	m_DefaultLightShader = new Shader(SHADERDIR"TechVertexExtend.glsl", SHADERDIR"TechLightFragment.glsl");
	if (!m_DefaultLightShader->LinkProgram()){
		return;
	} 
	
	m_DefaultShadowShader = new Shader(SHADERDIR"TechVertex.glsl", SHADERDIR"TechShadowFragment.glsl");
	if (!m_DefaultShadowShader->LinkProgram()){
		return;
	}
	
	m_ShadowVolumeShader = new Shader(SHADERDIR"TechVertex.glsl", SHADERDIR"PassThroughFragment.glsl", SHADERDIR"ShadowVolumeGeometry.glsl");
	if (!m_ShadowVolumeShader->LinkProgram()){
		return;
	}*/
	
	SceneShader = new Shader(SHADERDIR"TardisVertex.glsl", SHADERDIR"TardisFragment.glsl");
	if (!SceneShader->LinkProgram()){
		return;
	}
	
	ShadowShader = new Shader(SHADERDIR"shadowVert.glsl", SHADERDIR"shadowFrag.glsl");
	if (!ShadowShader->LinkProgram()){
		return;
	}
	
	////*******************************
	////**		CUBE MAP			**
	////*******************************
	////for sky box
	m_skyboxShader = new Shader(SHADERDIR"skyboxVertex.glsl", SHADERDIR"skyboxFragment.glsl");
	if (!m_skyboxShader->LinkProgram()){
		return;
	}

	cubeMap = SOIL_load_OGL_cubemap(
		TEXTUREDIR"skyBox/sky_pos_z.jpg",
		TEXTUREDIR"skyBox/sky_neg_z.jpg",
		TEXTUREDIR"skyBox/sky_pos_y.jpg",
		TEXTUREDIR"skyBox/sky_neg_y.jpg",
		TEXTUREDIR"skyBox/sky_neg_x.jpg",
		TEXTUREDIR"skyBox/sky_pos_x.jpg",
		SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, 0);

	if (!cubeMap)
	{
		return;
	}
	/*m_ParticleShader = new Shader(SHADERDIR"ParticleVertex.glsl",
		SHADERDIR"ParticleFragment.glsl",
		SHADERDIR"ParticleGeometry.glsl");

	if (!m_ParticleShader->LinkProgram()) {
		return;
	}

	m_RootParticleList = new ParticleEmitter();*/

	m_Camera = new Camera();
	m_RootGameObject = new GameObject();	//root is created here

	m_RootGameObject->m_Scene = this;

	/*m_AmbientColour = Vector3(0.2f, 0.2f, 0.2f);
	m_InvLightDirection = Vector3(0.5f, 1.0f, -0.8f);
	m_SpecularIntensity = 128.0f;

	m_InvLightDirection.Normalise();*/

	m_ScreenDTex = NULL;
	m_ScreenCTex = NULL;
	m_ScreenFBO = NULL;
	BuildScreenFBO();

	/*clearcolor = Vector4(0.6f, 0.6f, 0.6f, 1.f);
	glClearColor(clearcolor.x, clearcolor.y, clearcolor.z, clearcolor.w);*/

	NCLDebug::LoadShaders();

	init = true;

	lightList.push_back(Light(Vector3(0, 300, 0),//position
		Vector4(1, 1, 1, 1), //light color
		200.0f //light radius
		, 5.0f // brightness
		, Vector3(1, 1, 1)
		));
	//lightList.push_back(Light(Vector3(0, 0, 0),//position
	//	Vector4(1, 1, 1, 1), //light color
	//	50.0f //light radius
	//	, 5.0f // brightness
	//	, Vector3(1, 1, 1)
	//	));
	//lightList.push_back(Light(Vector3(-36.3696, -72.7393, 58.1914),//position
	//	Vector4(1, 1, 1, 1), //light color
	//	500.0f //light radius
	//	, 10.0f // brightness
	//	, Vector3(1, 1, 1)
	//	));
	//lightList.push_back(Light(Vector3(0, 50.0f, 0),//position
	//	Vector4(1, 0, 0, 1), //light color
	//	50.0f //light radius
	//	, 5.0f // brightness
	//	, Vector3(1, 1, 1)
	//	));

	///////////////////////////////////////////////////////////////
	//SHADOW
	///////////////////////////////////////////////////////////////
	//start Shadow
	glGenTextures(1, &shadowTex);
	glBindTexture(GL_TEXTURE_2D, shadowTex);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOWSIZE, SHADOWSIZE, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	//compare between depth texture and depth buffer
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

	glBindTexture(GL_TEXTURE_2D, 0);

	glGenFramebuffers(1, &shadowFBO);

	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowTex, 0);

	glDrawBuffer(GL_NONE);//no need to attatch the colour infomation
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//end Shadow
	glEnable(GL_DEPTH_TEST);

	///////////////////////////////////////////////////////////////
	//END   SHADOW
	///////////////////////////////////////////////////////////////
}

Scene::~Scene()
{
	AssetsManager::ReleaseMeshes();

	/*if (m_DefaultLightShader)
	{
		delete m_DefaultLightShader;
		m_DefaultLightShader = NULL;
	}

	if (m_DefaultShadowShader)
	{
		delete m_DefaultShadowShader;
		m_DefaultShadowShader = NULL;
	}

	if (m_ShadowVolumeShader)
	{
		delete m_ShadowVolumeShader;
		m_ShadowVolumeShader = NULL;
	}*/

	  
	if (SceneShader)
	{
		delete SceneShader;
		SceneShader = NULL;
	}
	 if (ShadowShader)
	{
		 delete ShadowShader;
		 ShadowShader = NULL;
	}
	 if (m_skyboxShader)
	{
		 delete m_skyboxShader;
		 m_skyboxShader = NULL;
	}
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = NULL;
	}

	if (m_RootGameObject)
	{
		delete m_RootGameObject;
		m_RootGameObject = NULL;
	}

	glDeleteTextures(1, &m_ScreenDTex);
	glDeleteTextures(1, &m_ScreenCTex);
	glDeleteFramebuffers(1, &m_ScreenFBO);

	NCLDebug::ReleaseShaders();
}


void Scene::AddGameObject(GameObject* game_object)
{
	m_RootGameObject->AddChildObject(game_object);
}

GameObject* Scene::FindGameObject(const std::string& name)
{
	return m_RootGameObject->FindGameObject(name);
}

//int frame_idx = 0;
void Scene::RenderScene()
{
	//Check to see if the window has been resized
	if (m_ScreenTexWidth != width || m_ScreenTexHeight != height)
	{
		BuildScreenFBO();
	}


	//Reset all varying data
	textureMatrix.ToIdentity();
	modelMatrix.ToIdentity();
	viewMatrix = m_Camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(0.01f, 1000.0f, (float)width / (float)height, 45.0f);
	m_FrameFrustum.FromMatrix(projMatrix * viewMatrix);



	//Update all Object's World Transform
	UpdateWorldMatrices(m_RootGameObject, Matrix4());

	NCLDebug::SetDebugDrawData(projMatrix * viewMatrix, m_Camera->GetPosition());

	

	//Setup Default Shader Uniforms
	Vector3 camPos = m_Camera->GetPosition();
	Vector3 lightPos = m_InvLightDirection * -100.0f;
	Vector4 lightPosEyeSpace = viewMatrix * Vector4(lightPos.x, lightPos.y, lightPos.z, 1.0f);

	/*SetCurrentShader(m_DefaultLightShader);
	SetShaderLightList(lightList);
	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "ambientColour"), 1, &m_AmbientColour.x);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "invLightDir"), 1, &m_InvLightDirection.x);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, &camPos.x);
	glUniform1f(glGetUniformLocation(currentShader->GetProgram(), "specularIntensity"), m_SpecularIntensity);

	SetCurrentShader(m_DefaultShadowShader);
	UpdateShaderMatrices();
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "ambientColour"), 1, &m_AmbientColour.x);

	SetCurrentShader(m_ShadowVolumeShader);
	SetShaderLightList(lightList);
	UpdateShaderMatrices();
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "invLightDir"), 1, &m_InvLightDirection.x);*/


	//Setup Render FBO/OpenGL States
	//glBindFramebuffer(GL_FRAMEBUFFER, m_ScreenFBO);
	//glStencilFunc(GL_ALWAYS, 0, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	//glClearColor(clearcolor.x, clearcolor.y, clearcolor.z, clearcolor.w);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	/////////////////////////////////////////////////
	//glDisable(GL_CULL_FACE);
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	//glDepthFunc(GL_ALWAYS);
	//glDepthMask(GL_FALSE);//disable the depth buffer, it won't write on depth buffer
	//SetCurrentShader(m_skyboxShader);//set skyboxShader to be currentShader


	//glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "cubeTex"), 0);

	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMap);

	//UpdateShaderMatrices(); //update "modelMatrix" "viewMatrix" "projMatrix" "textureMatrix"


	//SetTextureRepeating(quad->GetTexture(), true);
	//quad->Draw(false);

	//glUseProgram(0);
	//glDepthMask(GL_TRUE);//enable depth buffer

	//glDepthFunc(GL_LEQUAL);
	///////////////////////////////////////////////////

	//glEnable(GL_MULTISAMPLE);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_DEPTH_CLAMP);
	//glEnable(GL_STENCIL_TEST);
	//glEnable(GL_CULL_FACE);
	//glEnable(GL_BLEND);
	//glDepthFunc(GL_LEQUAL);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Build Render List
	BuildNodeLists(m_RootGameObject);
	SortNodeLists();
	
	////Render the Scene in the Dark (As if it were a shadow)
	//SetCurrentShader(m_DefaultShadowShader);//TechVertex  TechShadowFragment
	////DrawNodes(false);

	////Render the Shadow Volumes to the Stencil Buffer
	//SetCurrentShader(m_ShadowVolumeShader);//TechVertex  PassThroughFragment  ShadowVolumeGeometry
	//glDepthFunc(GL_LESS);
	//glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	//glDepthMask(GL_FALSE);

	//glStencilFunc(GL_ALWAYS, 0, 0xFF);
	//glStencilOpSeparate(GL_FRONT, GL_KEEP, GL_INCR_WRAP, GL_KEEP);
	//glStencilOpSeparate(GL_BACK, GL_KEEP, GL_DECR_WRAP, GL_KEEP);

	//glDisable(GL_CULL_FACE);
	////DrawNodes(false);
	//glEnable(GL_CULL_FACE);
	//

	////Finally Render the Light Sections of the scene where the shadow volumes overlapped
	//glDepthFunc(GL_LEQUAL);
	//glStencilFunc(GL_EQUAL, 0, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//glDepthMask(GL_TRUE);

	//SetCurrentShader(m_DefaultLightShader);//TechVertex  TechLightFragment
	////DrawNodes(true);

	////  start shadow

	////glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	viewMatrix = m_Camera->BuildViewMatrix();
	projMatrix = Matrix4::Perspective(1.0f, 1000.0f, (float)width / (float)height, 45.0f);

	for (int i = 0; i < 6;i++)
	{
	
	DrawShadowScene();
	//viewMatrix = Matrix4::BuildViewMatrix((lightList.at(0)).GetPosition(), Vector3(0,0,0));
	DrawCominedScene();
	}
	
	//UpdateShaderMatrices();

	

	//Clear Render List
	ClearNodeLists();


	//Finally draw all debug data to FBO (this fbo has anti-aliasing and the screen buffer does not)
	glDisable(GL_DEPTH_TEST);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	PhysicsEngine::Instance()->DebugRender();

	NCLDebug::SortDebugLists();
	NCLDebug::DrawDebugLists();
	NCLDebug::ClearDebugLists();

	/////////////////////////////////////////////////
	//PARTICLE
	/////////////////////////////////////////////////
	
	
	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	//SetCurrentShader(m_ParticleShader);
	//glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);

	//DrawParticleList(m_RootParticleList);


	/////////////////////////////////////////////////
	//glDepthMask(GL_TRUE);



	//Present our Screen
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//PresentScreenFBO();

	//Swap Buffers and get ready to repeat the process
	//glUseProgram(0);
	SwapBuffers();
}

void Scene::DrawShadowScene()
{
	glBindFramebuffer(GL_FRAMEBUFFER, shadowFBO);
	glClear(GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, SHADOWSIZE, SHADOWSIZE);

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	SetCurrentShader(ShadowShader);
	//from the light to the middle of the height map
	//viewMatrix = Matrix4::BuildViewMatrix(lightList.at(10).GetPosition(), MiddleOfScene);

	viewMatrix = Matrix4::BuildViewMatrix(lightList.at(0).GetPosition(), Vector3(0,0,0));
	textureMatrix = biasMatrix * (projMatrix * viewMatrix);
	(lightList.at(0)).SetlightViewProjMat(biasMatrix * (projMatrix * viewMatrix));

	//Texture matrix is really  = biasMatrix * (light proj Matrix * light view Matrix)

	UpdateShaderMatrices();

	//draw a shadow of each things
	DrawNodes(false);

	glUseProgram(0);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glViewport(0, 0, width, height);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Scene::DrawCominedScene()
{
	SetCurrentShader(SceneShader);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "diffuseTex"), 0);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "bumpTex"), 1);
	glUniform1i(glGetUniformLocation(currentShader->GetProgram(), "shadowTex"), 2);
	glUniform3fv(glGetUniformLocation(currentShader->GetProgram(), "cameraPos"), 1, (float*)&m_Camera->GetPosition());

	SetShaderLightList(lightList);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, shadowTex);

	viewMatrix = m_Camera->BuildViewMatrix();

	UpdateShaderMatrices();

	//draw the object
	DrawNodes(false);

	glUseProgram(0);
}
void Scene::DrawParticleList(ParticleEmitter* n)
{
	for (auto emitterChild : n->GetChildren()) {

		glUniform1f(glGetUniformLocation(currentShader->GetProgram(), "particleSize"), emitterChild->GetParticleSize());

		UpdateShaderMatrices();

		emitterChild->Draw();
	}
}

void Scene::UpdateParticleList(float dt, ParticleEmitter* cNode)
{
	//cNode->OnUpdateObject(dt);
	for (auto child : cNode->GetChildren()) {
		child->Update(dt* 100.f);
	}
}
//
void Scene::AddParticleObject(ParticleEmitter* particle_object)
{
	m_RootParticleList->AddChildParticle(particle_object);
}
void Scene::UpdateScene(float dt)
{
	m_Camera->UpdateCamera(dt * 1000.f);
	UpdateNode(dt, m_RootGameObject);
	//UpdateParticleList(dt, m_RootParticleList);
}


void Scene::BuildScreenFBO()
{
	m_ScreenTexWidth = width;
	m_ScreenTexHeight = height;

	//Generate our Scene Depth Texture
	if (!m_ScreenDTex) glGenTextures(1, &m_ScreenDTex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ScreenDTex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_DEPTH24_STENCIL8, width, height, GL_FALSE);

	//Generate our Scene Colour Texture
	if (!m_ScreenCTex) glGenTextures(1, &m_ScreenCTex);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_ScreenCTex);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 16, GL_RGBA8, width, height, GL_FALSE);

	//Generate our Framebuffers
	if (!m_ScreenFBO) glGenFramebuffers(1, &m_ScreenFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ScreenFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_ScreenDTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_ScreenDTex, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ScreenCTex, 0);

	//Validate our framebuffer
	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE
		|| !m_ScreenDTex 
		|| !m_ScreenCTex)
	{
		//GL_FRAMEBUFFER_INC
		cout << "Error: Unable to create screen framebuffer object.";
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Scene::PresentScreenFBO()
{
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_ScreenFBO);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void Scene::UpdateWorldMatrices(GameObject* cNode, const Matrix4& parentWM)
{
	cNode->m_WorldTransform = parentWM * cNode->Physics()->GetWorldSpaceTransform() * cNode->m_LocalTransform;

	for (auto child : cNode->GetChildren()) {
		UpdateWorldMatrices(child, cNode->m_WorldTransform);
	}
}

void Scene::BuildNodeLists(GameObject* cNode)
{
	Vector3 obj_pos = cNode->Physics()->GetPosition();
	Vector3 direction = obj_pos - m_Camera->GetPosition();

	FrustrumSortingObject fso;
	fso.camera_distance = Vector3::Dot(direction, direction);
	fso.target			= cNode;

	if (m_FrameFrustum.InsideFrustum(obj_pos, cNode->GetBoundingRadius())) {
		if (cNode->GetColour().w < 1.0f) {
			m_TransparentNodeList.push_back(fso);
		}
		else{
			m_NodeList.push_back(fso);
		}
	}

	for (auto child : cNode->GetChildren()) {
		BuildNodeLists(child);
	}
}


void Scene::SortNodeLists()
{
	std::sort(m_TransparentNodeList.begin(), m_TransparentNodeList.end(), FrustrumSortingObject::CompareByCameraDistance);
	std::sort(m_NodeList.begin(), m_NodeList.end(), FrustrumSortingObject::CompareByCameraDistance);
}

void Scene::ClearNodeLists()
{
	m_TransparentNodeList.clear();
	m_NodeList.clear();
}

void Scene::DrawNodes(bool drawTransparentObjects)
{
	for (auto node : m_NodeList) {
		DrawNode(node.target);
	}

	if (drawTransparentObjects)
	{
		glFrontFace(GL_CW);
		for (auto node : m_TransparentNodeList) {
			DrawNode(node.target);
		}

		glFrontFace(GL_CCW);
		for (auto node : m_TransparentNodeList) {
			DrawNode(node.target);
		}
	}
}

void Scene::DrawNode(GameObject* n)
{
	modelMatrix.ToIdentity();
	Matrix4 temp = (lightList.at(0)).GetlightViewProjMat()  * n->m_WorldTransform;
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "textureMatrix"), 1, false, *&temp.values);

	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "testMatrix"), 1, false, *&temp.values);
	glUniformMatrix4fv(glGetUniformLocation(currentShader->GetProgram(), "modelMatrix"), 1, false, (float*)&n->m_WorldTransform);
	glUniform4fv(glGetUniformLocation(currentShader->GetProgram(), "nodeColour"), 1, (float*)&n->GetColour());

	n->OnRenderObject();
}


void Scene::UpdateNode(float dt, GameObject* cNode)
{
	cNode->OnUpdateObject(dt);  

	for (auto child : cNode->GetChildren()) {
		UpdateNode(dt, child);
	}
}
