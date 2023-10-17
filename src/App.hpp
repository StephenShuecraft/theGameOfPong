#pragma once
#ifdef __ANDROID__
    #include <android/log.h>
    #define LOGW(...) __android_log_print(ANDROID_LOG_WARN,__VA_ARGS__)
#endif

#include <Canis/Canis.hpp>
#include <Canis/SceneManager.hpp>


enum AppState
{
    ON,
    OFF
};

class App
{
public:
    App();
    ~App();

    void Run();

private:
    void Load();
    void Loop();
    void Update();
    void Draw();
    void LateUpdate();
    void FixedUpdate(float dt);
    void InputUpdate();
    void LoadECS();

    Canis::SceneManager m_sceneManager;

    AppState m_appState = AppState::OFF;

    Canis::Window m_window;
    Canis::Time m_time;
    Canis::InputManager m_inputManager;
    Canis::Camera m_camera = Canis::Camera(glm::vec3(0.0f, 0.15f, -0.3f),glm::vec3(0.0f, 1.0f, 0.0f),Canis::YAW+90.0f,Canis::PITCH+0.0f);
    Canis::AssetManager m_assetManager;

    double m_deltaTime;

    unsigned int m_seed;
};