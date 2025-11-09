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

    Transform& plyTrans = FindEntity<Entity>("Player")->GetComponent<Transform>();
    Transform& camTrans = GetComponent<Transform>();

    m_Offset = camTrans.GetPosition() - plyTrans.GetPosition();
}

void MainCamera::Update()
{
    Transform& plyTrans = FindEntity<Entity>("Player")->GetComponent<Transform>();
    Transform& camTrans = GetComponent<Transform>();
    camTrans.SetPosition(plyTrans.GetPosition() + m_Offset);
    m_ViewMatrix = Camera::CalcViewMatrix(camTrans);
}