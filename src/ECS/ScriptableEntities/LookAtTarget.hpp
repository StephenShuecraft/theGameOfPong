#pragma once
#include <SDL_keyboard.h>
#include <string>

#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/TransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/MeshComponent.hpp>
#include <Canis/ECS/Components/SphereColliderComponent.hpp>

class LookAtTarget : public Canis::ScriptableEntity
{
public:
    Canis::Entity target;

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
        auto& transform = GetComponent<Canis::TransformComponent>();

        /*Canis::LookAt(
            transform,
            Canis::GetGlobalPosition(target.GetComponent<Canis::TransformComponent>()),
            glm::vec3(0.0f, 1.0f, 0.0f)
        );*/

        Canis::RotateTowardsLookAt(transform, glm::vec3(45.0f), glm::vec3(0.0f, 1.0f, 0.0), 3.14f * _dt);

        //glm::vec3 angles = glm::degrees(glm::eulerAngles(transform.rotation));

        //Canis::Log("x: " + std::to_string(angles.x) + " y: " + std::to_string(angles.y) + " z: " + std::to_string(angles.z));
    }
};

bool DecodeLookAtTarget(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "LookAtTarget")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<LookAtTarget>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}