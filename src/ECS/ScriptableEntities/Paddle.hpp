#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>

class Paddle : public Canis::ScriptableEntity
{
private:

public:
    void OnCreate()
    {
        //Canis::Log("Paddle Loaded");
    }

    void OnReady()
    {

    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
         using namespace Canis;
        Entity leftPaddle = entity.GetEntityWithTag("LEFTPADDLE");
        auto&  rectLeftPaddle  = leftPaddle.GetComponent<RectTransformComponent>();
        

        //rectLeftPaddle.position.y

        Entity rightPaddle = entity.GetEntityWithTag("RIGHTPADDLE");
        auto&  rectRightPaddle  = rightPaddle.GetComponent<RectTransformComponent>();
        

        if (GetInputManager().GetKey(SDL_SCANCODE_W))
            rectLeftPaddle.position.y += 0.4f;
        if (GetInputManager().GetKey(SDL_SCANCODE_S))
            rectLeftPaddle.position.y -= 0.4f;

        if (GetInputManager().GetKey(SDL_SCANCODE_UP))
            rectRightPaddle.position.y += 0.4f;
        if (GetInputManager().GetKey(SDL_SCANCODE_DOWN))
            rectRightPaddle.position.y -= 0.4f;

    }

        
};

bool DecodePaddle(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "Paddle")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<Paddle>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;

}