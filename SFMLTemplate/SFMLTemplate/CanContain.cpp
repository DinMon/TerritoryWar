#include "CanContain.h"
#include "Entity.h"

CanContain::CanContain()
{
}

CanContain::~CanContain()
{
}

Entity* CanContain::FetchItem(std::string aName)
{
	for (auto &lItem : fItems)
	{
		if (lItem->GetName() == aName)
		{
			return lItem;
		}
	}
	return nullptr;
}

Entity* CanContain::FetchCurrentItem()
{
	if (std::next(fIterator) != fItems.end())
	{
		fIterator++;
	}
	else
	{
		fIterator = fItems.begin();
	}
	ShowCurrentItemDebug();
	return *fIterator;
}

void CanContain::AddItem(Entity* aItem)
{
	fItems.push_back(aItem);
	if (fItems.size() == 1)
	{
		fIterator = fItems.begin();
	}
	else
	{
		fIterator++;
	}
	ShowListDebug();
}

void CanContain::RemoveItem(std::string aName)
{
	auto it = find(fItems.begin(), fItems.end(), FetchItem(aName));
	fItems.erase(it);
}

void CanContain::ShowListDebug()
{
	std::cout << "CanContain list of Items: " << std::endl;
	for (auto &item : fItems)
	{
		std::cout << " - " << item->GetName() << std::endl;
	}
}

void CanContain::ShowCurrentItemDebug()
{
	std::cout << "CanContain current Item in use: " << (*fIterator)->GetName() << std::endl;
}
