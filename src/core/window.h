#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "utils/log.h"
#include <memory>
#include <events/events-pool.h>
#include "events/keyboard.h"
#include "events/mouse.h"

class Window{
public:
    static Window* Create(std::string title, int width, int height);
    GLFWwindow* GetNativeWindow();
    std::unique_ptr<EventsPool> events;
    Keyboard m_Keyboard;
    Mouse m_Mouse;
    void InitEvents();
    void CenterCursor();
    ~Window();
    int GetWidth();
    int GetHeight();
    void SetTitle(std::string title);
private:
    int m_Width, m_Height;
    std::string m_Title;
    GLFWwindow* m_Window;
    Window();
};