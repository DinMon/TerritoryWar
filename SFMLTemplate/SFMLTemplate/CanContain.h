#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <iostream>

class Entity;

class CanContain :
	public Component
{
public:
	CanContain();
	~CanContain();
	Entity* FetchItem(std::string);
	Entity* FetchCurrentItem();
	void AddItem(Entity*);
	void RemoveItem(std::string);
	void ShowListDebug();
	void ShowCurrentItemDebug();
private:
	std::vector<Entity*>::iterator fIterator;
	std::vector<Entity*> fItems;
};

