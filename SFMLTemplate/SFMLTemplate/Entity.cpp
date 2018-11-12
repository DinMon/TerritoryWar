#include "Entity.h"
#include "IDGenerator.h"

Entity::Entity(std::string aName)
{
	fName = aName;
	fId = IDGenerator::GenerateId();
	fComponentContainer = new ComponentHolder();
}

sf::Sprite Entity::getSprite()
{
	return fEntitySprite;
}

ComponentHolder * Entity::GetComponentContainer()
{
	return fComponentContainer;
}

int Entity::GetId()
{
	return fId;
}

std::string Entity::GetName()
{
	return fName;
}

