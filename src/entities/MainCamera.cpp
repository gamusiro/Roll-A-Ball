#include "entities/MainCamera.h"

#include "Scene.h"
#include "Logger.h"
#include "Camera.h"

MainCamera::MainCamera(ScenePtr scene)
    :Entity(scene)
{
}

void MainCamera::Awake()
{
    float fovy = glm::radians(60.0f);
    float aspect = static_cast<float>(DEFAULT_WIDTH) / static_cast<float>(DEFAULT_HEIGHT);
    float nearZ = 0.01f;
    float farZ = 20.0f;
    AddComponent<PerspectiveCamera>(fovy, aspect, nearZ, farZ);

    Transform& transfrom = GetComponent<Transform>();
    transfrom.SetPosition(glm::vec3(0.0f, 1.5f, 15.0f));
    transfrom.SetRotation(glm::quat(glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 0.0f)));

    m_ViewMatrix = Camera::CalcViewMatrix(transfrom);
}