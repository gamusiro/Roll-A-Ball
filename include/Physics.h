#ifndef ROLL_A_BALL_INCLUDE_PHYSICS_H_
#define ROLL_A_BALL_INCLUDE_PHYSICS_H_
#include "Config.h"

#include "CollisionCallback.h"

class Physics
{
public:
    static Physics& Instance();

public:
    void AddRigidBody(btRigidBody* rigidBody);
    void RemoveRigidBody(btRigidBody* rigidBody);

private:
    void init();
    void update(entt::registry& registry, float timeStep = 1.0f / 60.0f);
    void term();

private:
    Physics() = default;
    ~Physics() = default;
    Physics(const Physics&) = delete;
    Physics operator= (const Physics&) = delete;

private:
    struct PairHash {
        size_t operator()(const std::pair<Entity*, Entity*>& pair) const noexcept {
            return std::hash<Entity*>()(pair.first) ^ (std::hash<Entity*>()(pair.second) << 1);
        }
    };

private:
    btCollisionConfiguration*               m_CollisionConfiguration;
    btCollisionDispatcher*                  m_CollisionDispatcher;
    btBroadphaseInterface*                  m_OverlappingPairCache;
    btSequentialImpulseConstraintSolver*    m_Solver;
    btDiscreteDynamicsWorld*                m_DynamicsWorld;
    CollisionCallback                       m_Callback;

    std::unordered_set<std::pair<Entity*, Entity*>, PairHash> m_Last;
    std::unordered_set<std::pair<Entity*, Entity*>, PairHash> m_Current;
    std::unordered_set<std::pair<Entity*, Entity*>, PairHash> m_LastTrigger;
    std::unordered_set<std::pair<Entity*, Entity*>, PairHash> m_CurrentTrigger;

private:
    friend class Application;
    friend class CollisionCallback;
};

#endif