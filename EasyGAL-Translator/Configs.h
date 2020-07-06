#pragma once

#include <stdint.h>
#include <vector>

using namespace std;

struct Config
{
	uint32_t m_iNumInputs;
	uint32_t m_iNumOutputs;

	vector<uint32_t> m_Inputs;
	vector<uint32_t> m_Outputs;

	uint32_t m_iNumFuses;
};
