#include "Physics.h"

#include "BoxCollider.h"
#include "SphereCollider.h"
#include "MeshCollider.h"
#include "Entity.h"

Physics& Physics::Instance()
{
    static Physics instance;
    return instance;
}

void Physics::AddRigidBody(btRigidBody* rigidBody)
{
    m_DynamicsWorld->addRigidBody(rigidBody);
}

void Physics::RemoveRigidBody(btRigidBody* rigidBody)
{
    m_DynamicsWorld->removeRigidBody(rigidBody);
}

void Physics::init()
{
    m_CollisionConfiguration    = new btDefaultCollisionConfiguration();
    m_CollisionDispatcher       = new btCollisionDispatcher(m_CollisionConfiguration);
    m_OverlappingPairCache      = new btDbvtBroadphase();
    m_Solver                    = new btSequentialImpulseConstraintSolver();
    m_DynamicsWorld             = new btDiscreteDynamicsWorld(m_CollisionDispatcher, m_OverlappingPairCache, m_Solver, m_CollisionConfiguration);
    m_DynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}

void Physics::update(entt::registry& registry, float timeStep)
{
    m_Last = m_Current;
    m_Current.clear();

    m_LastTrigger = m_CurrentTrigger;
    m_CurrentTrigger.clear();

    // Physics simulation
    m_DynamicsWorld->stepSimulation(timeStep);

    auto view = registry.view<Transform, RigidBody>();
    for(auto entity : view)
    {
        Transform& transform = view.get<Transform>(entity);
        RigidBody& rigidBody = view.get<RigidBody>(entity);
        transform.SetPosition(rigidBody.GetPosition());
    }
    
    {// Box Colliders
        auto bcView = registry.view<Tag, BoxCollider>();
        for(auto entity : bcView) {
            Collider& collider = bcView.get<BoxCollider>(entity);
            m_DynamicsWorld->contactTest(collider.m_RigidBody, m_Callback);
        }
    }

    {// Sphere Colliders
        auto scView = registry.view<Tag, SphereCollider>();
        for(auto entity : scView) {
            Collider& collider = scView.get<SphereCollider>(entity);
            m_DynamicsWorld->contactTest(collider.m_RigidBody, m_Callback);
        }
    }

    {// Mesh Colliders
        auto msView = registry.view<Tag, MeshCollider>();
        for(auto entity : msView) {
            Collider& collider = msView.get<MeshCollider>(entity);
            m_DynamicsWorld->contactTest(collider.m_RigidBody, m_Callback);
        }
    }

    // Currnet Collisions
    for (const auto& pair : m_Current)
    {
        bool wasColliding = m_Last.find(pair) != m_Last.end();
        if (!wasColliding)
            pair.first->OnCollisionEnter(pair.second);
        else
            pair.first->OnCollisionStay(pair.second);
    }

    // Last Collisions
    for (const auto& pair : m_Last)
    {
        bool nowColliding = m_Current.find(pair) != m_Current.end();
        if (!nowColliding)
            pair.first->OnCollisionExit(pair.second);
    }

    // Currnet Trigger Collisions
    for (const auto& pair : m_CurrentTrigger)
    {
        bool wasColliding = m_LastTrigger.find(pair) != m_LastTrigger.end();
        if (!wasColliding)
            pair.first->OnTriggerEnter(pair.second);
        else
            pair.first->OnTriggerStay(pair.second);
    }

    // Last Trigger Collisions
    for (const auto& pair : m_LastTrigger)
    {
        bool nowColliding = m_CurrentTrigger.find(pair) != m_CurrentTrigger.end();
        if (!nowColliding)
            pair.first->OnTriggerExit(pair.second);
    }
}

void Physics::term()
{
    delete m_DynamicsWorld;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_CollisionDispatcher;
    delete m_CollisionConfiguration;
}