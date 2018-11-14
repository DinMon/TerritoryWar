#include "StringUtil.h"

StringUtil::StringUtil()
{
}


StringUtil::~StringUtil()
{
}

vector<string> StringUtil::SplitString(const string line, const char* delimiter)
{
	vector<string> tokens;
	char *cstr = new char[line.size() + 1];
	std::copy(begin(line), end(line), cstr);
	cstr[line.size()] = '\0';

	char *p;

	p = strtok(cstr, delimiter);
	while (p != NULL)
	{
		tokens.push_back(p);
		p = strtok(NULL, delimiter);
	}
	return tokens;
}
