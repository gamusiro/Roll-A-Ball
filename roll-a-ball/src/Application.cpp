#include "Application.h"

#include "Logger.h"
#include "Utils.h"
#include "Time.h"
#include "Scene.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Font.h"
#include "FontManager.h"
#include "ApplicationEvent.h"

void Application::Run()
{
    if(init())
    {
        SceneManager& sceneManager = SceneManager::Instance();
        InputManager& inputManager = InputManager::Instance();
        TimeManager& timeManager = TimeManager::Instance();
        while (!glfwWindowShouldClose(m_Window) && !sceneManager.Empty())
        {            
            // Time update
            timeManager.update();

            // Scene
            inputManager.update();
            sceneManager.update();

            // Clear screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, m_WindowWidth, m_WindowHeight);
            sceneManager.render();
            inputManager.reset();

            glfwSwapBuffers(m_Window);
            glfwPollEvents();
        }
    }
    term();
}

bool Application::init()
{
    // init logger
    Logger::Instance().init();

    // init glfw
    if(glfwInit() != GLFW_TRUE)
    {
        LOG_CORE_ERROR("Failed to initialize glfw");
        return false;
    }
    LOG_CORE_INFO("Initialized glfw");

    // create window
    m_WindowWidth = DEFAULT_WIDTH;
    m_WindowHeight = DEFAULT_HEIGHT;
    m_Window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_CAPTION, nullptr, nullptr);
    if(m_Window == nullptr)
    {
        LOG_CORE_ERROR("Failed to create window");
        return false;
    }
    LOG_CORE_INFO("Created window");

    // Make context
    glfwMakeContextCurrent(m_Window);

    // Key call back
    glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        InputManager& im = InputManager::Instance();
        switch (action)
        {
        case GLFW_PRESS:    im.setKey(key, true);   break;
        case GLFW_RELEASE:  im.setKey(key, false);  break;
        }
    });

    // Mouse button callback
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
    {
        InputManager& im = InputManager::Instance();
        switch (action)
        {
        case GLFW_PRESS:    im.setMouse(button, true);   break;
        case GLFW_RELEASE:  im.setMouse(button, false);  break;
        }
    });

    // Cursor callback
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
    {
        InputManager& im = InputManager::Instance();
        float x = static_cast<float>(xpos);
        float y = static_cast<float>(ypos);
        im.setMouse(x, y);
    });

    // Frame buffer resize callback
    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
    {
        if(width <= 0 || height <= 0)
            return;   // Minimize window size

        Application* app = (Application*)glfwGetWindowUserPointer(window);
        app->m_WindowWidth = width;
        app->m_WindowHeight = height;
        WindowResizeEvent e(width, height);
        SceneManager::Instance().m_CurScene->Dispatch<WindowResizeEvent>(std::move(e));
    });

    // Load glad
    if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != GLFW_TRUE)
    {
        LOG_CORE_ERROR("Failed to load glad library");
        return false;
    }
    LOG_CORE_INFO("Loaded glad library");

    // Freetype
    if(!FontManager::Instance().init())
    {
        LOG_CORE_ERROR("Failed to initialize FontManager");
        return false;
    }

    // Load fonts
    std::vector<std::string> list;
    list.push_back(FONT_NOTOSANS_JP);

    FontManager::Instance().load(list);

    FontPtr font = FontManager::Instance().GetFont(FONT_NOTOSANS_JP);

    std::string text = u8"残り個1234567890";
    std::u32string output;
    utf8::utf8to32(text.begin(), text.end(), std::back_inserter(output));
    font->MakeGlyphs(output);
    //font->MakeGlyphs();
    
    // Bullet Physics
    Physics::Instance().init();

    // Load Scene
    SceneManager::Instance().LoadScene(0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return true;
}

void Application::term()
{
    // Terminate scene
    SceneManager::Instance().term();

    // Terminate Physics
    Physics::Instance().term();

    // Terminate Fonts
    FontManager::Instance().term();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
    LOG_CORE_INFO("Terminated glfw");

    Logger::Instance().term();
}