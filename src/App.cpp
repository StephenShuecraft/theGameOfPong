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
		m_sceneManager.decodeSystem.push_back(Canis::DecodeButtonSystem);
		m_sceneManager.decodeSystem.push_back(Canis::DecodeCollisionSystem2D);
		m_sceneManager.decodeSystem.push_back(Canis::DecodeSpriteAnimationSystem);
	}

	{ // decode render systems
		m_sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderHUDSystem);
		m_sceneManager.decodeRenderSystem.push_back(Canis::DecodeRenderTextSystem);
		m_sceneManager.decodeRenderSystem.push_back(Canis::DecodeSpriteRenderer2DSystem);
	}
	
	{ // decode scriptable entities
		m_sceneManager.decodeScriptableEntity.push_back(DecodeDebugCamera2D);
		m_sceneManager.decodeScriptableEntity.push_back(DecodeBeachBall);
	}

	{ // decode component
		m_sceneManager.decodeEntity.push_back(Canis::DecodeTagComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeCamera2DComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeRectTransformComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeColorComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeTextComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeSprite2DComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeSpriteAnimationComponent);
		m_sceneManager.decodeEntity.push_back(Canis::DecodeCircleColliderComponent);
	}
}
App::~App()
{
	
}

void App::Run()
{
	if (m_appState == AppState::ON)
		Canis::FatalError("App already running.");

	Canis::Init();

	unsigned int windowFlags = 0;

	m_window.Create("Canis", 1280, 800, windowFlags);

	m_time.init(30);

	m_camera.override_camera = false;


	m_seed = std::time(NULL);
	srand(m_seed);
	Canis::Log("seed : " + std::to_string(m_seed));

	m_sceneManager.Add(new Canis::Scene("SpriteDemo", "assets/scenes/SpriteDemo.scene"));

	m_sceneManager.PreLoad(
		&m_window,
		&m_inputManager,
		&m_time,
		&m_camera,
		&m_assetManager,
		m_seed
	);

	Load();

	m_appState = AppState::ON;

	Loop();
}
void App::Load()
{
	m_sceneManager.ForceLoad("SpriteDemo");
}
void App::Loop()
{
	while (m_appState == AppState::ON)
	{
		m_deltaTime = m_time.startFrame();
		m_sceneManager.SetDeltaTime(m_deltaTime);

		Update();
		Draw();
		// Get SDL to swap our buffer
		m_window.SwapBuffer();
		LateUpdate();
		InputUpdate();

		m_window.fps = m_time.endFrame(); 
	}
}
void App::Update()
{
	m_sceneManager.Update();
}
void App::Draw()
{
	m_sceneManager.Draw();
}
void App::LateUpdate()
{
	m_sceneManager.LateUpdate();
}
void App::InputUpdate()
{
	if (!m_inputManager.Update(m_window.GetScreenWidth(), m_window.GetScreenHeight()))
		m_appState = AppState::OFF;
	
	m_sceneManager.InputUpdate();
}