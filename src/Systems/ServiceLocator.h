#ifndef _SERVICELOCATOR_H_
#define _SERVICELOCATOR_H_

#include "EntityManager.h"

class EntityManager;

class ServiceLocator
{
public:
	static EntityManager* GetEntityManager();

	static void ProvideEntityManager(EntityManager* manager);

private:
	static EntityManager* _entity_manager;
};

#endif