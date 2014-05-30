#ifndef _ENTITYMANAGER_H_
#define _ENTITYMANAGER_H_

#include "../Types.h"

#include <map>
#include <vector>
#include <set>


using std::vector;
using std::set;
using std::map;

class IComponent;

// Holds all entities and components with helper functions to access specific componenets
class EntityManager
{
public:
	EntityManager();
	~EntityManager();
	
	// Gets a given component pointer from a given entity
	IComponent* GetComponent(const int &entity, const ComponentTypes &component_type);
	
	// Returns vector of all components of given type
	vector<IComponent*> GetAllComponentsOfType(const ComponentTypes &component_type);
	
	// Returns vector of entity ID's of given component
	vector<unsigned int> GetAllEntitiesPossessingComponent(const ComponentTypes &component_type);

	// Returns vector of entity ID's of given components
	vector<unsigned int> GetAllEntitiesPossessingComponents(const vector<ComponentTypes>& types);
	
	// Adds given component to an entity
	void AddComponent(const unsigned int &entity, IComponent *component, const bool &replace = false);
	
	// Creates a new entity
	unsigned int CreateEntity();
	
	// Removes given entity
	void KillEntity(const unsigned int &entity);
	
	// Destroys all components and frees entities
	void ResetManager();
	
private:
	// Generates a unique entity ID
	int GenerateNewEntityID();
	
	// Lowest current unassigned ID
	unsigned int _lowest_unassigned_entity_id;
	// List of all the current entity IDs
	set<unsigned int> _all_entities;
	// Map of all component types to a map of entities that use the component and a pointer to the component
	map<ComponentTypes, map<unsigned int, IComponent*> > _component_store;
};

#endif