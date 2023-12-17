#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

#include "Rotate.hpp"

class SpawnCube : public Canis::ScriptableEntity
{
private:
    bool m_mouseLock = false;
public:
    void OnCreate()
    {
        
    }

    void OnReady()
    {
        GetScene().camera->Position = glm::vec3(0.0f, 0.0f, -5.0f);
        GetScene().camera->WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        GetScene().camera->FOV = glm::radians(90.0f);
        GetScene().camera->override_camera = false;
        GetScene().camera->UpdateCameraVectors();
        m_mouseLock = false;
        GetWindow().MouseLock(m_mouseLock);

        Canis::TransformComponent t;

        Canis::Entity emptyParent = CreateEntity();
        emptyParent.AddComponent<Canis::TransformComponent>(t);
        DecodeRotate("Rotate", emptyParent);
        

        Canis::TransformComponent transform;
        transform.position.x += 3;
        Canis::ColorComponent color;
        Canis::MeshComponent mesh;
        Canis::SphereColliderComponent collider;

        mesh.id = Canis::AssetManager::LoadModel("assets/models/white_block.obj");
        mesh.material = Canis::AssetManager::LoadMaterial("assets/materials/box.material");

        Canis::Entity cube = CreateEntity();
        cube.AddComponent<Canis::TransformComponent>(transform);
        cube.AddComponent<Canis::ColorComponent>(color);
        cube.AddComponent<Canis::MeshComponent>(mesh);
        cube.AddComponent<Canis::SphereColliderComponent>(collider);
        DecodeRotate("Rotate", cube);

        cube.SetParent(emptyParent);
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);

        if (keystate[SDL_SCANCODE_W] && m_mouseLock)
        {
            GetScene().camera->ProcessKeyboard(Canis::Camera_Movement::FORWARD, _dt);
        }

        if (keystate[SDL_SCANCODE_S] && m_mouseLock)
        {
            GetScene().camera->ProcessKeyboard(Canis::Camera_Movement::BACKWARD, _dt);
        }

        if (keystate[SDL_SCANCODE_A] && m_mouseLock)
        {
            GetScene().camera->ProcessKeyboard(Canis::Camera_Movement::LEFT, _dt);
        }

        if (keystate[SDL_SCANCODE_D] && m_mouseLock)
        {
            GetScene().camera->ProcessKeyboard(Canis::Camera_Movement::RIGHT, _dt);
        }

        if (GetInputManager().JustPressedKey(SDLK_F11))
        {
            m_mouseLock = !m_mouseLock;

            GetWindow().MouseLock(m_mouseLock);
        }

        if (m_mouseLock)
        {
            GetScene().camera->ProcessMouseMovement(GetInputManager().mouseRel.x, -GetInputManager().mouseRel.y);
        }

        if (GetInputManager().JustPressedKey(SDLK_ESCAPE))
        {
            m_mouseLock = false;
            GetWindow().MouseLock(m_mouseLock);
        }
    }
};

bool DecodeSpawnCube(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "SpawnCube")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<SpawnCube>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}