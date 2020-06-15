#pragma once

#include "DNF.hpp"

//	All OLMC modes for the GAL22V10D (http://web.mit.edu/6.115/www/document/gal22v10.pdf)

enum class MacrocellMode
{
	MODE_NONE,
	MODE_REGISTERED_LOW,
	MODE_REGISTERED_HIGH,
	MODE_COMBINATORIAL_LOW,
	MODE_COMBINATORIAL_HIGH
};

/* The Fuses namesapce*/

namespace Fuses
{
	bool Build(vector<DNF::Expression> Expressions);
	bool BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength);
	int PinToIndex(uint32_t iPinNumber, bool bInverted, MacrocellMode Mode = MacrocellMode::MODE_NONE);
}
