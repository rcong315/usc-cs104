#include "misc_utils.h"

#include <sys/resource.h>

#include <iostream>
#include <sstream>
#include <cstring>

std::string stackLimToString(rlim_t stackLimit)
{
	std::stringstream result;

	if(stackLimit == RLIM_INFINITY)
	{
		result << "infinity";
	}
	else
	{
		result << "0x" << std::hex << stackLimit;
	}

	return result.str();
}

void removeStackLimit()
{
	struct rlimit stack_limit = {};
	getrlimit(RLIMIT_STACK, &stack_limit);

	std::cout << "Stack size was " << stackLimToString(stack_limit.rlim_cur) << " bytes, setting it to the max of " << stackLimToString(stack_limit.rlim_max) << " bytes." << std::endl;

	stack_limit.rlim_cur = stack_limit.rlim_max;
	setrlimit(RLIMIT_STACK, &stack_limit);
}

void makeLowercase(std::string & toConvert)
{
	for(size_t index = 0; index < toConvert.length(); ++index)
	{
		toConvert[index] = (char)std::tolower(toConvert[index]);
	}
}