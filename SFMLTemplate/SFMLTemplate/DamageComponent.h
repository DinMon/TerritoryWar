#pragma once
#include "Component.h"
class DamageComponent :
	public Component
{
public:
	DamageComponent(int);
	~DamageComponent();
	int GetDamage();
private:
	int fDamagePoint;
};

