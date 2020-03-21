#pragma once

#include <iostream>
#include "utils/log.h"
#include "window.h"
#include "renderer/renderer.h"
#include "model.h"
#include "texture/texture.h"
#include "core/camera.h"
#include "world/world.h"
#include "utils/time.h"

class Application{
public:
    static void Run();
    ~Application();
private:
    static std::unique_ptr<Application> m_Instance;
    bool m_Running;
    Window *m_Window;
    World *m_World;
    Camera m_Camera;
    std::unique_ptr<Renderer> m_Renderer;
    bool Init();
    Application();
    static std::unique_ptr<Application>& GetInstance();
    static void OnEvent();
    void handleKeyDownEvent(EventKeyboard &key);
    void handleMouseMotion(EventMouseMotion &motion);
    void handleMouseDown();
    void UpdateTime();
    std::chrono::milliseconds m_StartTime;
    int m_OneDayTime;
    float m_AppTime;
};
