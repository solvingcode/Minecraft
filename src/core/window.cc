#include "window.h"

Window::Window(){}

Window* Window::Create(std::string title, int width, int height){
    Window *instance = new Window;
    instance->m_Width = width;
    instance->m_Height = height;
    instance->m_Title = title;
    instance->events = std::make_unique<EventsPool>();

    if (!glfwInit())
        return nullptr;
    CallGL(glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3));
    CallGL(glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3));
    CallGL(glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE));
    instance->m_Window = glfwCreateWindow(instance->m_Width, instance->m_Height, title.c_str(), NULL, NULL);
    if(!instance->m_Window){
        CallGL(glfwTerminate());
    }else{
        glfwSetWindowUserPointer(instance->m_Window, instance);
        CallGL(glfwMakeContextCurrent(instance->m_Window));
        CallGL(glfwSwapInterval(1));
    }
    return instance;
} 

void Window::SetTitle(std::string title){
    glfwSetWindowTitle(m_Window, title.c_str());
}

GLFWwindow* Window::GetNativeWindow(){
    return m_Window;
}

Window::~Window(){
    LogTrace("Destructing window...\n");
    glfwTerminate();
}

void Window::CenterCursor(){
    glfwSetCursorPos(m_Window, m_Width/2, m_Height/2);
}

int Window::GetWidth(){
    return m_Width;
}

int Window::GetHeight(){
    return m_Height;
}

void Window::InitEvents(){

    CenterCursor();
    //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* nativeWindow){
        Event* event = new Event();
        event->type = EVENT_QUIT;
        
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));
        EventsPool *events = window->events.get();
        events->Push(event);
    });

    glfwSetKeyCallback(m_Window, [](GLFWwindow* nativeWindow, int key, int scancode, int action, int mods){
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));
        Event* event = new Event();
        switch (action)
        {
        case GLFW_REPEAT:
        case GLFW_PRESS:
            event->type = EVENT_KEYDOWN;
            event->key = EventKeyboard(key, scancode);
            window->m_Keyboard.SetKeyPressed(key);
            break;
        case GLFW_RELEASE:
            event->type = EVENT_KEYUP;
            event->key = EventKeyboard(key, scancode);
            window->m_Keyboard.SetKeyReleased(key);
            break;
        
        default:
            break;
        }
        
        EventsPool *events = window->events.get();
        events->Push(event);
    });

    glfwSetCursorPos(m_Window, m_Width/2, m_Height/2);

    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* nativeWindow, double xpos, double ypos){
        Event* event = new Event();
        event->type = EVENT_MOUSEMOTION;
        event->motion = EventMouseMotion(xpos, ypos);

        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));
        EventsPool *events = window->events.get();
        events->Push(event);
    });

    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* nativeWindow, int button, int action, int mods){
        Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));
        switch (button)
        {
        case GLFW_MOUSE_BUTTON_RIGHT:
            if(action == GLFW_PRESS)
                window->m_Mouse.SetButtonPressed(MouseButton::RIGHT);
            else if(action == GLFW_RELEASE)
                window->m_Mouse.SetButtonReleased(MouseButton::RIGHT);
            break;
        case GLFW_MOUSE_BUTTON_LEFT:
            if(action == GLFW_PRESS)
                window->m_Mouse.SetButtonPressed(MouseButton::LEFT);
            else if(action == GLFW_RELEASE)
                window->m_Mouse.SetButtonReleased(MouseButton::LEFT);
            break;
        
        default:
            break;
        }
    });

}