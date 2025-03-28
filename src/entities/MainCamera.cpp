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
    float farZ = 50.0f;
    AddComponent<PerspectiveCamera>(fovy, aspect, nearZ, farZ);

    Transform& transform = GetComponent<Transform>();
    m_ViewMatrix = Camera::CalcViewMatrix(transform);
}