#ifdef _WIN32
#include <windows.h>
#endif

#include <Canis/App.hpp>
#include <Canis/ECS/Decode.hpp>
#include <Canis/Canis.hpp>
#include <Canis/SceneManager.hpp>
#include <Canis/ECS/Systems/RenderHUDSystem.hpp>
#include <Canis/ECS/Systems/RenderTextSystem.hpp>
#include <Canis/ECS/Systems/SpriteRenderer2DSystem.hpp>
#include <Canis/ECS/Systems/SpriteAnimationSystem.hpp>
#include <Canis/ECS/Systems/CollisionSystem2D.hpp>
#include <Canis/ECS/Systems/ButtonSystem.hpp>
#include <Canis/ECS/Systems/RenderMeshWithShadowSystem.hpp>

#include "ECS/ScriptableEntities/DebugCamera2D.hpp"
#include "ECS/ScriptableEntities/BeachBall.hpp"
#include "ECS/ScriptableEntities/GameOfLifeLoader.hpp"
#include "ECS/ScriptableEntities/SpawnCube.hpp"
#include "ECS/ScriptableEntities/FlyCam.hpp"
#include "ECS/ScriptableEntities/FPSCounter.hpp"
#include "ECS/ScriptableEntities/Paddle.hpp"

#include "ECS/Systems/GameOfLifeSystem.hpp"

int main(int argc, char* argv[])
{
    Canis::App app;

    // decode system
    app.AddDecodeSystem(Canis::DecodeButtonSystem);
    app.AddDecodeSystem(Canis::DecodeCollisionSystem2D);
	app.AddDecodeSystem(Canis::DecodeSpriteAnimationSystem);
    app.AddDecodeSystem(DecodeGameOfLifeSystem);

    // decode render system
    app.AddDecodeRenderSystem(Canis::DecodeRenderHUDSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderTextSystem);
    app.AddDecodeRenderSystem(Canis::DecodeSpriteRenderer2DSystem);
    app.AddDecodeRenderSystem(Canis::DecodeRenderMeshWithShadowSystem);

    // decode scriptable entities
    app.AddDecodeScriptableEntity(DecodeDebugCamera2D);
    app.AddDecodeScriptableEntity(DecodeBeachBall);
    app.AddDecodeScriptableEntity(DecodeGameOfLifeLoader);
    app.AddDecodeScriptableEntity(DecodeSpawnCube);
    app.AddDecodeScriptableEntity(DecodeFlyCam);
    app.AddDecodeScriptableEntity(DecodePaddle);
    app.AddDecodeScriptableEntity(DecodeFPSCounter);

    // decode component
    app.AddDecodeComponent(Canis::DecodeTransformComponent);
    app.AddDecodeComponent(Canis::DecodeDirectionalLightComponent);
    app.AddDecodeComponent(Canis::DecodeTagComponent);
    app.AddDecodeComponent(Canis::DecodeCamera2DComponent);
    app.AddDecodeComponent(Canis::DecodeRectTransformComponent);
    app.AddDecodeComponent(Canis::DecodeColorComponent);
    app.AddDecodeComponent(Canis::DecodeTextComponent);
    app.AddDecodeComponent(Canis::DecodeSprite2DComponent);
    app.AddDecodeComponent(Canis::DecodeUIImageComponent);
    app.AddDecodeComponent(Canis::DecodeUISliderComponent);
    app.AddDecodeComponent(Canis::DecodeSpriteAnimationComponent);
    app.AddDecodeComponent(Canis::DecodeCircleColliderComponent); 

    app.AddScene(new Canis::Scene("sprite_demo", "assets/scenes/sprite_demo.scene"));
    app.AddScene(new Canis::Scene("game_of_life", "assets/scenes/game_of_life.scene"));
    app.AddScene(new Canis::Scene("3d_demo", "assets/scenes/3d_demo.scene"));

    app.Run("Canis Demos", "sprite_demo"); 

    return 0; 
}  