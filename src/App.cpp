#include "App.hpp"
#include <Canis/ECS/Systems/RenderHUDSystem.hpp>
#include <Canis/ECS/Systems/RenderTextSystem.hpp>
#include <Canis/ECS/Systems/SpriteRenderer2DSystem.hpp>
#include <Canis/ECS/Systems/SpriteAnimationSystem.hpp>

#include <Canis/ECS/Systems/CollisionSystem2D.hpp>
#include <Canis/ECS/Systems/ButtonSystem.hpp>

#include <Canis/ECS/Decode.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/BeachBall.hpp"

App::App()
{
	{ // decode systems
		sceneManager.decodeSystem.push_back(Canis::DecodeButtonSystem);
		sceneManager.decodeSystem.push_back(Canis::DecodeCollisionSystem2D);
		sceneManager.decodeSystem.push_back(Canis::DecodeSpriteAnimationSystem);
	}

	{ // decode render systems
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderHUDSystem);
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderTextSystem);
		sceneManager.decodeRenderSystem.push_back(Canis::DecodeSpriteRenderer2DSystem);
	}
	
	{ // decode scriptable entities
		sceneManager.decodeScriptableEntity.push_back(DecodeDebugCamera2D);
		sceneManager.decodeScriptableEntity.push_back(DecodeBeachBall);
	}

	{ // decode component
		sceneManager.decodeEntity.push_back(Canis::DecodeTagComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeCamera2DComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeRectTransformComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeColorComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeTextComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeSprite2DComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeSpriteAnimationComponent);
		sceneManager.decodeEntity.push_back(Canis::DecodeCircleColliderComponent);
	}
}
App::~App()
{
	
}

void App::Run()
{
	if (appState == AppState::ON)
		Canis::FatalError("App already running.");

	Canis::Init();

	unsigned int windowFlags = 0;

	window.Create("Canis", 1280, 800, windowFlags);

	time.init(30);

	camera.override_camera = false;


	seed = std::time(NULL);
	srand(seed);
	Canis::Log("seed : " + std::to_string(seed));

	sceneManager.Add(new Canis::Scene("SpriteDemo", "assets/scenes/SpriteDemo.scene"));

	sceneManager.PreLoad(
		&window,
		&inputManager,
		&time,
		&camera,
		&assetManager,
		seed
	);

	Canis::Log("Q App 0");

	Load();

	appState = AppState::ON;

	Loop();
}
void App::Load()
{
	sceneManager.ForceLoad("SpriteDemo");

	// start timer
	previousTime = high_resolution_clock::now();
}
void App::Loop()
{
	while (appState == AppState::ON)
	{
		deltaTime = time.startFrame();
		sceneManager.SetDeltaTime(deltaTime);

		Update();
		Draw();
		// Get SDL to swap our buffer
		window.SwapBuffer();
		LateUpdate();
		InputUpdate();

		window.fps = time.endFrame(); 
	}
}
void App::Update()
{
	sceneManager.Update();
}
void App::Draw()
{
	sceneManager.Draw();
}
void App::LateUpdate()
{
	sceneManager.LateUpdate();
}
void App::InputUpdate()
{
	if (!inputManager.Update(window.GetScreenWidth(), window.GetScreenHeight()))
		appState = AppState::OFF;
	
	sceneManager.InputUpdate();
}