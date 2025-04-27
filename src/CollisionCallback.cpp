#include "CollisionCallback.h"

#include "Entity.h"
#include "Physics.h"

btScalar CollisionCallback::addSingleResult(
    btManifoldPoint& cp,
    const btCollisionObjectWrapper* colObj0Wrap, int partId0, int index0,
    const btCollisionObjectWrapper* colObj1Wrap, int partId1, int index1)
    {
        Entity* entity1 = reinterpret_cast<Entity*>(colObj0Wrap->getCollisionObject()->getUserPointer());
        Entity* entity2 = reinterpret_cast<Entity*>(colObj1Wrap->getCollisionObject()->getUserPointer());
#ifdef DEBUG
        Tag& tag1 = entity1->GetComponent<Tag>();
        Tag& tag2 = entity2->GetComponent<Tag>();
        std::cout << tag1.GetName() << " and " << tag2.GetName() << std::endl;
#endif // DEBUG
        bool isTrigger = !(colObj0Wrap->getCollisionObject()->getCollisionFlags() & btCollisionObject::CF_NO_CONTACT_RESPONSE);
        if(isTrigger)
            Physics::Instance().m_Current.insert({entity1, entity2});
        else
            Physics::Instance().m_Current.insert({ entity1, entity2 });
        return btScalar(0.0f);
    }