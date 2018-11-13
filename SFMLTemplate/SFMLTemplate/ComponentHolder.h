#pragma once
#include "Component.h"
#include <vector>

class ComponentHolder
{
public:
	ComponentHolder();
	~ComponentHolder();
	template<class T> void AddComponent(Component*);
	template<class T> T* GetComponent();
private:
	std::vector<Component*> fComponents;
};

template<class T>
T* ComponentHolder::GetComponent()
{
	for (int i = 0; i < fComponents.size(); i++)
	{
		if (dynamic_cast<T*>(fComponents[i]) != nullptr)
		{
			return (T*)fComponents[i];
		}
	}
	throw "Cannot find Component";
	return nullptr;
}

template<class T>
void ComponentHolder::AddComponent(Component* aComponent)
{
	fComponents.push_back((T*)aComponent);
}
