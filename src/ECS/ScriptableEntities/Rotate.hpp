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
        Canis::TransformComponent& transform = GetComponent<Canis::TransformComponent>();

        transform.rotation.y += glm::radians(360 * _dt);
        transform.rotation.x += glm::radians(360 * _dt);

        transform.isDirty = true;
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