#include "Scene.h"

Scene::Scene()
{ 
}

void Scene::Destroy(const std::shared_ptr<Entity> entity)
{
    if (!entity)
    {
        LOG_CORE_WARN("Scene::Destroy entity is null");
        return;
    }

    if (m_Entities.find(entity->m_Name) == m_Entities.end())
    {
        LOG_CORE_WARN("Scene::Destroy entity is not found");
        return;
    }

    entity->OnDestroy();
    m_Entities.erase(entity->m_Name);
    m_Registry.destroy(entity->m_ID);
}
