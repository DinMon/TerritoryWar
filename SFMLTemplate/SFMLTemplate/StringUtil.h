#pragma once
#include <iostream>
#include "string.h"
#include <cstring>
#include <vector>

using namespace std;

class StringUtil
{
public:
	StringUtil();
	~StringUtil();
	static vector<string> SplitString(const string, const char*);
};

