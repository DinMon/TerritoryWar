#pragma once
static class IDGenerator
{
public:
	IDGenerator();
	~IDGenerator();
	static int GenerateId();
private:
	static int fIdCounter;
};

