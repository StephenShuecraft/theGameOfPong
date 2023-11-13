#pragma once

#include <SDL_keyboard.h>

#include <glm/glm.hpp>

#include <Canis/ECS/Systems/System.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/ColorComponent.hpp>
#include <Canis/ECS/Components/ScriptComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

#include "../Components/GameOfLifeComponent.hpp"

#include "../ScriptableEntities/GameOfLifeLoader.hpp"

class GameOfLifeSystem : public Canis::System
{
private:
    bool m_runRulesUpdate = false;
    float m_resetTime = 0.25f;
    float m_countDown = 0.0f;
public:

    GameOfLifeSystem() : Canis::System() {

    }

    ~GameOfLifeSystem() {

    }

    void Create()
    {

    }

    void Ready()
    {

    }

    void Update(entt::registry &_registry, float _deltaTime)
    {
        // get all
        auto view = _registry.view<Canis::RectTransformComponent, Canis::ColorComponent, GameOfLifeComponent>();

        // find the entity in the scene with a tag Boards
        Canis::Entity e = GetScene().FindEntityWithTag("Boards");

        // get the scriptable entity off of it
        GameOfLifeLoader* loader = static_cast<GameOfLifeLoader*>(e.GetComponent<Canis::ScriptComponent>().Instance);

        // on click change state
        for(auto[entity, rectTransform, color, gameOfLife] : view.each())
        {
            // turn on cell
            

            // turn off cell
            
        }

        // toggel running

        // rules loop
        if (m_runRulesUpdate)
        {
            m_countDown -= _deltaTime;

            if (m_countDown < 0.0f)
            {
                m_countDown = m_resetTime;

                for(auto[entity, rectTransform, color, gameOfLife] : view.each())
                {
                    // find index
                    
                    // rap the index around the screen

                    // check neighbors

                    // rule one

                    // rule two

                    // rule three

                    // rule four
                }
            }
        }

        // set color based on state
        for(auto[entity, rectTransform, color, gameOfLife] : view.each())
        {
            // update current state
            if (gameOfLife.update == true)
            {
                gameOfLife.currentState = gameOfLife.nextState;
                gameOfLife.update = false;
            }
            // clear
            if (GetInputManager().JustPressedKey(SDLK_c))
            {
                gameOfLife.currentState = false;
            }
            // update color
            if (gameOfLife.currentState == true)
            {
                color.color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
            }
            else{
                color.color = glm::vec4(1.0f);
            }
        }
    }
};

bool DecodeGameOfLifeSystem(const std::string &_name, Canis::Scene *_scene)
{
    if (_name == "GameOfLifeSystem")
    {
        _scene->CreateSystem<GameOfLifeSystem>();
        return true;
    }
    return false;
}
