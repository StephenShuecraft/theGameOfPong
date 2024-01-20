#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

class Rotate : public Canis::ScriptableEntity
{
public:
    void OnCreate()
    {
        
    }

    void OnReady()
    {
        
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        entity.Rotate(glm::vec3(glm::radians(30 * _dt), glm::radians(30 * _dt), glm::radians(30 * _dt)));
    }
};

bool DecodeRotate(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "Rotate")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<Rotate>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}