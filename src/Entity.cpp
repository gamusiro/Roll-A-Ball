#include "Entity.h"

Entity::Entity(ScenePtr scene)
	:m_Scene(scene),
	m_ID(scene->create())
{
}
