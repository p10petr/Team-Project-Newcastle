#include <nclgl\Window.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\NCLDebug.h>
#include "MyScene.h"

Scene* scene = NULL;

int Quit(bool pause = false, const string &reason = "") {
	if (scene)
	{
		delete scene;
		scene = NULL;
	}

	Window::Destroy();

	if (pause) {
		std::cout << reason << std::endl;
		system("PAUSE");
	}

	return 0;
}

int main()
{
	//-------------------
	//--- MAIN ENGINE ---
	//-------------------

	//Initialise the Window
	if (!Window::Initialise("Engine", 1280, 800, false))
	{
		return Quit(true, "Window failed to initialise!");
	}

	//Initialise the PhysicsEngine
	//Create GameObject Iterate Root Node upon which the GameObject List will be built
	PhysicsEngine::Instance();

	//Initialise the Scene, complete scene graph list
	//All Game Assets will be pre-loaded in
	//by initialising GameAssetsManager
	scene = new MyScene(Window::GetWindow());
	//scene(gom);
	
	//Initialise the ActionHandler Instnace
	ActionHandler::Instance();
	ActionHandler::Instance()->SetDefaultScene(scene);
	
	if (!scene->HasInitialised())
	{
		return Quit(true, "Renderer failed to initialise!");
	}

	GameTimer engine_timer;

	//Create main game-loop
	while (Window::GetWindow().UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)){
		float dt = Window::GetWindow().GetTimer()->GetTimedMS() * 0.001f;	//How many milliseconds since last update?

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_P))
		{
			PhysicsEngine::Instance()->SetPaused(!PhysicsEngine::Instance()->IsPaused());
		}

		engine_timer.GetTimedMS();

		if (!PhysicsEngine::Instance()->IsGameover()) {
			
			//ActionHandler
			//Update AI, ControlHandler etc
			//by updating 
			//overridden OnUpdateObject for each GameObject sub-class 
			//such as Player, AI, Static Object, Dynamic Object etc
			ActionHandler::Instance()->Update(dt);
			
			//Update Physics Properties, Resolve collision, apply impluse
			PhysicsEngine::Instance()->Update(dt);
			
			float physics_ms = engine_timer.GetTimedMS();

			//Update Graphic Properties, Camera etc
			//By updating OnRenderObject
			scene->UpdateScene(dt);
			
			if (PhysicsEngine::Instance()->IsGameover()) {
				continue;
			}

			float update_ms = engine_timer.GetTimedMS();

			//Debug Data
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Engine: %s (Press P to toggle)", PhysicsEngine::Instance()->IsPaused() ? "Paused" : "Enabled");
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "--------------------------------");
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Collision Detection Distance: " + std::to_string(PhysicsEngine::Instance()->GetCollisionDetectionDis()));
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Timestep : %5.2fms (%5.2f FPS)", PhysicsEngine::Instance()->GetUpdateTimestep() * 1000.0f, 1.0f / PhysicsEngine::Instance()->GetUpdateTimestep());
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Graphics Timestep: %5.2fms (%5.2f FPS)", dt * 1000.0f, 1.0f / dt);
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Physics Update: %5.2fms", physics_ms);
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Scene Update  : %5.2fms", update_ms);
			
			//Render the Scene
			scene->RenderScene();

		}


		else {
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "GameOver!");
			NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "Press H to check LeaderBoard, ESC to shut down the window.");
			if (Window::GetKeyboard()->KeyDown(KEYBOARD_H)) {
				std::vector<string> LB_name;
				std::vector<string> LB_score;
				std::string filename = "leaderboard.txt";

				std::ifstream f(filename.c_str(), std::ios::in);
				if (f) {
					while (!f.eof()) {
						std::string name;
						std::string score;
						f >> name;
						f >> score;
						LB_name.push_back(name);
						LB_score.push_back(score);
					}
				}
				f.close();
				for (unsigned int i = 0; i < LB_name.size(); i++) {
					NCLDebug::AddStatusEntry(Vector4(1.0f, 1.0f, 1.0f, 1.0f), "No." + std::to_string(i + 1) + "\t"
						+ LB_name[i] + "\t" + LB_score[i]);
				}
			}

			scene->RenderScene();
		}

	}

	//Cleanup
	return Quit();
}