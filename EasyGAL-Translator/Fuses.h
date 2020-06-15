#pragma once

#include "DNF.hpp"

namespace Fuses
{
	bool Build(vector<DNF::Expression> Expressions);
	bool BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength);
	uint32_t PinToIndex(uint32_t iPinNumber, bool bInverted);
}
