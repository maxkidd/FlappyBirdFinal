#include "Systems/ServiceLocator.h"
#include "Types.h"

EntityManager* ServiceLocator::_entity_manager = NULL;

EntityManager* ServiceLocator::GetEntityManager()
{
	return _entity_manager;
}

void ServiceLocator::ProvideEntityManager(EntityManager* manager)
{
	_entity_manager = manager;
}