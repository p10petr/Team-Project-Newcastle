#include <nclgl/OGLRenderer.h>
#include <nclgl/Camera.h>
#include <nclgl/Shader.h>
#include <nclgl/Frustum.h>

#include "TSingleton.h"
#include "GameObject.h"

struct FrustrumSortingObject
{
	float		camera_distance;
	GameObject* target;

	static bool CompareByCameraDistance(const FrustrumSortingObject& a, const FrustrumSortingObject& b)  {
		return (a.camera_distance < b.camera_distance) ? true : false;
	}
};

class Scene : public OGLRenderer
{
	friend class GameObjectMag;
public:
	Scene(Window& window);
	~Scene();

	void AddGameObject(GameObject* game_object);	
	GameObject* FindGameObject(const std::string& name);
	void SetClearColor(Vector4 color) { clearcolor = color; }

	virtual bool InitialiseGL()				{ return true; };
	virtual void RenderScene();
	virtual void UpdateScene(float dt); //This is msec * 0.001f (e.g time relative to seconds not milliseconds
protected:
	void	BuildScreenFBO();
	void	PresentScreenFBO();

	void	UpdateWorldMatrices(GameObject* node, const Matrix4& parentWM);

	void	BuildNodeLists(GameObject* node);
	void	SortNodeLists();
	void	ClearNodeLists();
	void	DrawNodes(bool drawTransparentObjects);
	void	DrawNode(GameObject* n);

	void	UpdateNode(float dt, GameObject* n);
protected:
	Camera*				m_Camera;
	Shader*				m_DebugShader;
	Shader			   *m_DefaultLightShader, *m_DefaultShadowShader;
	Shader*				m_ShadowVolumeShader;

	GameObject*			m_RootGameObject;

	Frustum				m_FrameFrustum;
	vector<FrustrumSortingObject> m_TransparentNodeList;
	vector<FrustrumSortingObject> m_NodeList;

	GLuint	m_ScreenTexWidth, m_ScreenTexHeight;
	GLuint  m_ScreenDTex, m_ScreenCTex, m_ScreenFBO;

	Vector3 m_AmbientColour;
	Vector3 m_InvLightDirection;
	Vector4 clearcolor;
	float   m_SpecularIntensity;

};