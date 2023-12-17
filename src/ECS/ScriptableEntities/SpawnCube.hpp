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
public:
    void OnCreate()
    {
        
    }

    void OnReady()
    {
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