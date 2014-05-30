#include "Logic/UpdateSystems.h"

#include "Systems/EntityManager.h"
#include "Systems/ServiceLocator.h"

#include "gba.h"

#include <vector>
#include <iterator>

UpdateSystems::UpdateSystems()
{
}
UpdateSystems::~UpdateSystems(){}

void UpdateSystems::Process()
{
	EntityManager* entity_manager = ServiceLocator::GetEntityManager();

	vector<ComponentTypes> types;
	types.push_back(COMP_PLAYER);
	types.push_back(COMP_RENDER);
	vector<unsigned int> entities = entity_manager->GetAllEntitiesPossessingComponents(types);
	vector<unsigned int>::iterator it = entities.begin();
	while (it != entities.end())
	{
		RenderComponent* renderComponent = (RenderComponent*)entity_manager->GetComponent(*it, COMP_RENDER);
		PlayerComponent* playerComponent = (PlayerComponent*)entity_manager->GetComponent(*it, COMP_PLAYER);

		playerComponent->_position.x += playerComponent->_velocity.x;
		playerComponent->_position.y += playerComponent->_velocity.y;

		renderComponent->_position.x = playerComponent->_position.x;
		renderComponent->_position.y = playerComponent->_position.y;
		
		renderComponent->_angleDegrees = playerComponent->_angleDegrees;

		it++;
	}
}