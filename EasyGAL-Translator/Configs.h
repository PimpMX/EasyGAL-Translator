#pragma once

#ifdef _WIN32

#include <direct.h>
#define GetCurrentDir _getcwd

#elif __linux__

#include <unistd.h>
#define GetCurrentDir getcwd

#endif

#include <stdint.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "Helper.hpp"

//	All credit goes to nlohmann and his json serializer: https://github.com/nlohmann/json

#include "Dependencies/json.hpp"

using namespace std;
using namespace nlohmann;

namespace Configs
{
	/*
	*	The CircuitConfig datastructure stores every important 
	*
	*	CircuitConfig::m_Outputs contains pairs of two unsigned integers.
	*	- The first value of a pair contains the designated output pin.
	*	- The second value of a pair contains the maximum output terms for the specified output pin.
	*/

	struct CircuitConfig 
	{
		uint32_t m_iNumFuses = 0;
		uint32_t m_iNumPins = 0;
		vector<uint32_t> m_Inputs = {};
		vector<pair<uint32_t, uint32_t>> m_Outputs = {};
	};

	bool Load(const char* szConfigName, CircuitConfig* pConfigOut);
}
