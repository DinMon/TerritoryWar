#include "DamageComponent.h"



DamageComponent::DamageComponent(int aDamage)
{
	fDamagePoint = aDamage;
}


DamageComponent::~DamageComponent()
{
}

int DamageComponent::GetDamage()
{
	return fDamagePoint;
}
