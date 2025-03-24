#ifndef ROLL_A_BALL_INCLUDE_PHYSICS_H_
#define ROLL_A_BALL_INCLUDE_PHYSICS_H_
#include "Config.h"

class Physics
{
public:
    static Physics& Instance();

public:
    void AddRigidBody(btRigidBody* rigidBody);
    void RemoveRigidBody(btRigidBody* rigidBody);

private:
    void init();
    void update(float timeStep = 1.0f / 60.0f);
    void term();

private:
    Physics() = default;
    ~Physics() = default;
    Physics(const Physics&) = delete;
    Physics operator= (const Physics&) = delete;

private:
    btCollisionConfiguration*               m_CollisionConfiguration;
    btCollisionDispatcher*                  m_CollisionDispatcher;
    btBroadphaseInterface*                  m_OverlappingPairCache;
    btSequentialImpulseConstraintSolver*    m_Solver;
    btDiscreteDynamicsWorld*                m_DynamicsWorld;

private:
    friend class Application;
};

#endif