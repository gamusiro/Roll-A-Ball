#include "Application.h"

#include "Logger.h"
#include "Utils.h"
#include "Time.h"
#include "Physics.h"
#include "Scene.h"
#include "SceneManager.h"

#include "scenes/GameScene.h"

void Application::Run()
{
    if(init())
    {
        SceneManager& sceneManager = SceneManager::Instance();
        while (!glfwWindowShouldClose(m_Window) && !sceneManager.Empty())
        {
            // Clear screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Scene
            sceneManager.update();
            sceneManager.render();

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
    m_Window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, DEFAULT_CAPTION, nullptr, nullptr);
    if(m_Window == nullptr)
    {
        LOG_CORE_ERROR("Failed to create window");
        return false;
    }
    LOG_CORE_INFO("Created window");

    // Make context
    glfwMakeContextCurrent(m_Window);

    // Load glad
    if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) != GLFW_TRUE)
    {
        LOG_CORE_ERROR("Failed to load glad library");
        return false;
    }
    LOG_CORE_INFO("Loaded glad library");

    // Bullet Physics
    Physics::Instance().init();

    // Load Scene
    SceneManager::Instance().LoadScene(std::make_shared<GameScene>());

    glEnable(GL_DEPTH_TEST);

    return true;
}

void Application::term()
{
    // Terminate scene
    SceneManager::Instance().term();

    // Terminate Physics
    Physics::Instance().term();

    glfwDestroyWindow(m_Window);
    glfwTerminate();
    LOG_CORE_INFO("Terminated glfw");

    Logger::Instance().term();
}