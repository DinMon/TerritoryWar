#include "IDGenerator.h"

int IDGenerator::fIdCounter = 0;

IDGenerator::IDGenerator()
{
}


IDGenerator::~IDGenerator()
{
}

int IDGenerator::GenerateId()
{
	return ++fIdCounter;
}
