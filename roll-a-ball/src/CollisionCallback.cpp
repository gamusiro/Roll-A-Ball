#include "CollisionCallback.h"

#include "Entity.h"
#include "Physics.h"

btScalar CollisionCallback::addSingleResult(
    btManifoldPoint& cp,
    const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
    const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
    {
        ColliderHandle* handle1 = reinterpret_cast<ColliderHandle*>(colObj0Wrap->getCollisionObject()->getUserPointer());
        ColliderHandle* handle2 = reinterpret_cast<ColliderHandle*>(colObj1Wrap->getCollisionObject()->getUserPointer());
#ifdef DEBUG
        Tag& tag1 = entity1->GetComponent<Tag>();
        Tag& tag2 = entity2->GetComponent<Tag>();
        std::cout << tag1.GetName() << " and " << tag2.GetName() << std::endl;
#endif // DEBUG
        bool isTrigger = colObj0Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE;
        if(isTrigger)
            Physics::Instance().m_CurrentTrigger.insert({ handle1->m_Entity, handle2->m_Entity });
        else
            Physics::Instance().m_Current.insert({ handle1->m_Entity, handle2->m_Entity });
        return btScalar(0.0f);
    }