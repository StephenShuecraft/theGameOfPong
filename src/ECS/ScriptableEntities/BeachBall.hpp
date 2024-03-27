#pragma once
#include <string>
#include <vector>
#include <Canis/ScriptableEntity.hpp>
#include <Canis/ECS/Components/RectTransformComponent.hpp>
#include <Canis/ECS/Components/TextComponent.hpp>

class BeachBall : public Canis::ScriptableEntity
{
private:
    glm::vec2   m_direction;
    glm::vec4   m_color;
    float       m_speed;
    float       m_timeBetweenAnimation = 3.0f;
    float       m_countDown = 0.0f;
    int         scorePlayer1 = 0;
    int         scorePlayer2 = 0;
    unsigned int m_animIndex = 0;
    std::vector<glm::vec2> m_spawnPoints = {};
public:
    void OnCreate()
    {
        m_countDown = m_timeBetweenAnimation;
    }

    void OnReady()
    {
        m_direction = glm::vec2(1.0f, 0.4f);
        m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        m_speed = 150.0f;
    }
    
    void OnDestroy()
    {

    }

    void OnUpdate(float _dt)
    {
        using namespace Canis;
        Entity leftPaddle = entity.GetEntityWithTag("LEFTPADDLE");
        auto&  rectLeftPaddle  = leftPaddle.GetComponent<RectTransformComponent>();
        auto&  colorLeftPaddle  = leftPaddle.GetComponent<ColorComponent>();

        //rectLeftPaddle.position.y

        Entity rightPaddle = entity.GetEntityWithTag("RIGHTPADDLE");
        auto&  rectRightPaddle  = rightPaddle.GetComponent<RectTransformComponent>();
        auto&  colorRightPaddle  = rightPaddle.GetComponent<ColorComponent>();

        Entity rectBox = entity.GetEntityWithTag("BOX");
        auto& rect = rectBox.GetComponent<RectTransformComponent>();
        auto& colorRect  = rectBox.GetComponent<ColorComponent>();

        Entity textB = entity.GetEntityWithTag("TEXT");
        auto&  textBox  = textB.GetComponent<RectTransformComponent>();
        auto& textBoxText = textB.GetComponent<TextComponent>();
        

        float halfSizeX = rect.size.x/2.0f;
        float halfSizeY = rect.size.y/2.0f;
        
    // Check for collision in the y-axis

    // left paddle
        if(rect.position.x + rect.size.x > rectLeftPaddle.position.x &&
            rect.position.y + rect.size.y + 30 > rectLeftPaddle.position.y &&
            rectLeftPaddle.position.x +  rectLeftPaddle.size.x  > rect.position.x &&
            rectLeftPaddle.position.y +  rectLeftPaddle.size.y  > rect.position.y){
	        m_direction.x *= -1.0f;
            m_speed += 40.0f;
            m_color = colorLeftPaddle.color;

        }


    //right paddle
        if(rect.position.x + rect.size.x > rectRightPaddle.position.x &&
            rect.position.y + rect.size.y > rectRightPaddle.position.y &&
            rectRightPaddle.position.x +  rectRightPaddle.size.x > rect.position.x &&
            rectRightPaddle.position.y +  rectRightPaddle.size.y > rect.position.y){
	        m_direction.x *= -1.0f;
            m_speed += 40.0f;
            m_color = colorRightPaddle.color;

        }
 

    //window bounce
        if (rect.position.x + halfSizeX >= GetWindow().GetScreenWidth()/2.0f ||
                rect.position.x - halfSizeX <= GetWindow().GetScreenWidth()/-2.0f){
            m_direction.x *= -1.0f;
            if(m_color == colorRightPaddle.color){
                scorePlayer2++;
            }
            if(m_color == colorLeftPaddle.color){
                scorePlayer1++;}

            
            }

        if (rect.position.y + halfSizeY >= GetWindow().GetScreenHeight()/2.0f ||
                rect.position.y - halfSizeY <= GetWindow().GetScreenHeight()/-2.0f)
            m_direction.y *= -1.0f;
        
        
        rect.position += (m_direction * (m_speed * _dt));
        colorRect.color = m_color;
        if (GetInputManager().JustPressedKey(SDLK_p))
            m_speed += 50.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_r))
            m_speed = 150.0f;
        
        if (GetInputManager().JustPressedKey(SDLK_d))
        {
            GetScene().Instantiate("assets/prefebs/test_character.scene");
        }
        //if (GetInputManager().JustPressedKey(SDL_SCANCODE_W))
        //{
            //
        //}

        textBoxText.text = "P1: "+ std::to_string(scorePlayer1) +" | P2:" + std::to_string(scorePlayer2);
        
    }
};

bool DecodeBeachBall(const std::string &_name, Canis::Entity &_entity)
{
    if (_name == "BeachBall")
    {
        Canis::ScriptComponent scriptComponent = {};
        scriptComponent.Bind<BeachBall>();
        _entity.AddComponent<Canis::ScriptComponent>(scriptComponent);
        return true;
    }
    return false;
}