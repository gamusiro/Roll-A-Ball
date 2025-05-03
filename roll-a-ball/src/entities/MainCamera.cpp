#include "entities/MainCamera.h"

#include "Scene.h"
#include "Logger.h"
#include "Camera.h"
#include "Utils.h"

MainCamera::MainCamera(ScenePtr scene)
    :Entity(scene)
{
}

void MainCamera::Awake()
{
    float fovy = glm::radians(60.0f);
    float aspect = static_cast<float>(DEFAULT_WIDTH) / static_cast<float>(DEFAULT_HEIGHT);
    float nearZ = 0.3f;
    float farZ = 1000.0f;
    AddComponent<PerspectiveCamera>(fovy, aspect, nearZ, farZ);

    Transform& transform = GetComponent<Transform>();
    m_ViewMatrix = Camera::CalcViewMatrix(transform);
}

void MainCamera::Update()
{
    Transform& transform = GetComponent<Transform>();
    m_ViewMatrix = Camera::CalcViewMatrix(transform);
}