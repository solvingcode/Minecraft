#include "application.h"
#include "world/block/block-base.h"

std::unique_ptr<Application> Application::m_Instance = nullptr;

Application::Application()
: m_Window(nullptr)
, m_Running(false)
, m_Camera(100.0f, 0.1f, 1000.0f)
, m_StartTime(Time::GetMTime())
, m_OneDayTime(600)
{
    BlockBase::Get();
}

std::unique_ptr<Application>& Application::GetInstance(){
    if(Application::m_Instance == nullptr){
        Application::m_Instance = std::unique_ptr<Application>(new Application);
    }
    return Application::m_Instance;
}

void Application::Run(){
    auto& instance = GetInstance();
    instance->m_Running = true;
    instance->Init();
    
    instance->m_World = World::GetInstance(instance->m_Camera);
    instance->m_Renderer = std::make_unique<Renderer>();

    double lastTime = glfwGetTime();
    int nbFrames = 0;
    while (instance->m_Running)
    {
        double currentTime = glfwGetTime();
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){
            instance->m_Window->SetTitle("Voxel Game (" + std::to_string(double(nbFrames)) + ")");
            nbFrames = 0;
            lastTime += 1.0;
        }
        instance->m_Renderer->Clear();

        instance->UpdateTime();
        instance->m_World->m_Player.Update(*instance->m_World);
        instance->m_World->Update(instance->m_Camera);
        instance->m_Camera.Update(instance->m_World->m_Player);
        instance->m_World->Render(*instance->m_Renderer, instance->m_Camera);
        instance->m_Renderer->Render(instance->m_Camera, instance->m_AppTime, instance->m_World->m_Player.IsUnderWater());

        glfwSwapBuffers(instance->m_Window->GetNativeWindow());
        OnEvent();
        glfwPollEvents();
    }
}

void Application::handleKeyDownEvent(EventKeyboard &key){
    if(key.m_Key == GLFW_KEY_ESCAPE){
        m_Running = false;
    }
}

void Application::handleMouseMotion(EventMouseMotion &motion){
    m_Window->CenterCursor();
    float xMove = motion.m_Xpos - (m_Window->GetWidth()/2);
    float yMove = motion.m_Ypos - (m_Window->GetHeight()/2);
    m_World->m_Player.Rotate(xMove/2.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    m_World->m_Player.Rotate(yMove/2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void Application::OnEvent(){
    auto& instance = GetInstance();
    EventsPool *eventsPool = instance->m_Window->events.get();
    Event* ev;
    while (ev = eventsPool->PollEvent())
    {
        switch(ev->type){
            case EVENT_QUIT:
                instance->m_Running = false;
                break;
            case EVENT_KEYDOWN:
                instance->handleKeyDownEvent(ev->key);
                break;
            case EVENT_MOUSEMOTION:
                instance->handleMouseMotion(ev->motion);
                break;
        }
        delete ev;
    }
    instance->m_World->m_Player.HandleInput(*instance->m_Window);
    instance->handleMouseDown();
}

void Application::handleMouseDown(){
    if(m_Window->m_Mouse.IsButtonPressed(MouseButton::LEFT)){
        m_World->Mine(m_Camera);
    }
}

bool Application::Init(){
    GetInstance()->m_Window = Window::Create("Voxel Game", SCREEN_WIDTH, SCREEN_HEIGHT);
    GetInstance()->m_Window->InitEvents();
    if(glewInit() != GLEW_OK){
        std::cout << "Error !" << std::endl;
        exit(EXIT_FAILURE);
    }

    CallGL(glEnable(GL_DEPTH_TEST)); 
    CallGL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    return true;
}

void Application::UpdateTime(){
    std::chrono::milliseconds timeNow = Time::GetMTime();
    float timeRel = ((timeNow.count() - m_StartTime.count())%(m_OneDayTime*1000))/((float)m_OneDayTime*1000/2);
    m_AppTime = timeRel/2;
}

Application::~Application(){
    LogTrace("Destructing application...\n");
}