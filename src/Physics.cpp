#include "Physics.h"

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

void Physics::update(float timeStep)
{
    m_DynamicsWorld->stepSimulation(timeStep);
}

void Physics::term()
{
    delete m_DynamicsWorld;
    delete m_Solver;
    delete m_OverlappingPairCache;
    delete m_CollisionDispatcher;
    delete m_CollisionConfiguration;
}