#include "Systems/EntityManager.h"
#include "Components/IComponent.h"

#include <cstdarg>

EntityManager::EntityManager(){ _lowest_unassigned_entity_id = 1; }
EntityManager::~EntityManager(){ ResetManager(); }

IComponent* EntityManager::GetComponent(const int &entity, const ComponentTypes &component_type)
{
	// Attempt to find component type and store it in iterator
	map<ComponentTypes, map<unsigned int, IComponent*> >::iterator store_it = _component_store.find(component_type);

	// If iterator is at end, no component
	if(store_it == _component_store.end())
		return NULL;
	
	// Store the located map
	map<unsigned int, IComponent*> store = store_it->second;
	// Store the entity ID
	map<unsigned int, IComponent*>::iterator result_it = store.find(entity);
	
	// It wasn't there
	if(result_it == store.end())
		return NULL;
	
	// Return component
	return result_it->second;
}

vector<IComponent*> EntityManager::GetAllComponentsOfType(const ComponentTypes &component_type)
{
	// Empy vector of components
	vector<IComponent*> components;
	// Try to locate the component type map and store its position in the iterator
	map<ComponentTypes, map<unsigned int, IComponent*> >::iterator store_it = _component_store.find(component_type);
	
	if(store_it == _component_store.end())
		return components;
	
	// Grab the map and begin to iterate through it
	map<unsigned int, IComponent*> store = store_it->second;
	map<unsigned int, IComponent*>::iterator it = store.begin();
	
	// We store each entry in there and then return the resulting filled vector
	for(; it != store.end(); it++) {
		components.push_back( it->second );
	}
	
	// Return components
	return components;
}

vector<unsigned int> EntityManager::GetAllEntitiesPossessingComponent(const ComponentTypes &component_type)
{
	// Empty vector of entities
	vector<unsigned int> entities;
	
	// Attempt to grab the iterator map of the right type
	map<ComponentTypes, map<unsigned int, IComponent*> >::iterator store_it = _component_store.find(component_type);
	
	// Check if empty
	if(store_it == _component_store.end())
		return entities;
		
	// Grab the map and begin to iterate through it
	map<unsigned int, IComponent*> store = store_it->second;
	map<unsigned int, IComponent*>::iterator it = store.begin();
	
	// Store all entities into the entities vector
	for(; it != store.end(); it++ )
		entities.push_back( it->first );
	
	// Return entities
	return entities;
}

vector<unsigned int> EntityManager::GetAllEntitiesPossessingComponents(const vector<ComponentTypes>& types)
{
	// Empty vector of entities
	vector<unsigned int> entities;

	// Attempt to grab the iterator map of the right type
	set<unsigned int>::iterator it = _all_entities.begin();
	while (it != _all_entities.end())
	{
		unsigned int currentEntity = *it;
		bool hasAllComponents = true;
		for (size_t i = 0; i < types.size(); i++)
		{
			hasAllComponents &= GetComponent(currentEntity, types[i]) != NULL;
		}
		if (hasAllComponents)
			entities.push_back(currentEntity);
		++it;
	}
	
	return entities;
}

void EntityManager::AddComponent(const unsigned int &entity, IComponent *component, const bool &replace)
{
	// Find if the component already exists
	map<ComponentTypes, map<unsigned int, IComponent*> >::iterator store_it = _component_store.find(component->type());
	
	// If component doesn't exist, assign a spot
	if(store_it == _component_store.end())
	{
		_component_store[component->type()] = map<unsigned int, IComponent*>();
	}
	else // If component exists don't want to replace, do nothing
	{
		map<unsigned int, IComponent*>::iterator result_it = store_it->second.find( entity );
		
		if( result_it != store_it->second.end() )
			if( !replace )
				return;
	}
	
	component->entityID = entity;
	
	// Store component with entity key
	_component_store[component->type()][entity] = component;
}

unsigned int EntityManager::CreateEntity()
{
	// Get ID to store entity
	int new_id = GenerateNewEntityID();
	
	if(new_id < 1)
		return 0;
	
	// Insert new entity ID
	_all_entities.insert(new_id);
	
	return new_id;
}

void EntityManager::KillEntity(const unsigned int &entity)
{
	// Kill entity
	_all_entities.erase(entity);
}

int EntityManager::GenerateNewEntityID()
{
	// If lowest id is less than the max for unsigned integers return the next one
	if(_lowest_unassigned_entity_id < UINT_MAX)
		return _lowest_unassigned_entity_id++;
	
	// Run through current entities and find one that doesn't exist TODO
	
	// Too many entities! error
	return 0;
}

void EntityManager::ResetManager()
{
	// Get iterator for the map
	map<ComponentTypes, map<unsigned int, IComponent*> >::iterator it = _component_store.begin();
	
	// Iterate through store
	for(; it != _component_store.end(); it++)
	{
		map<unsigned int, IComponent*> nested = it->second;
		map<unsigned int, IComponent*>::iterator nested_it = nested.begin();
		
		// Iterate through nested map and delete
		for(; nested_it != nested.begin(); nested_it++ ) 
		{
			KillEntity(nested_it->first);
			if(nested_it->second)
			{
				delete nested_it->second;
				nested_it->second = 0;
			}
		}
	}
	
	// Clear main map
	_component_store.clear();
	
	// Clear entities
	_all_entities.clear();
	
	// Reset lowest ID
	_lowest_unassigned_entity_id = 1;
}















