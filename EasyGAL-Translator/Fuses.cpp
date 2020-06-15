#include "Fuses.h"

bool Fuses::Build(vector<DNF::Expression> Expressions)
{
	return false;
}

bool Fuses::BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength)
{
	return false;
}

uint32_t Fuses::PinToIndex(uint32_t iPinNumber, bool bInverted)
{
	switch(iPinNumber)
	{
	case 1: return bInverted ? 1 : 0;
	case 2: return bInverted ? 5 : 4;
	case 3: return bInverted ? 9 : 8;
	case 4: return bInverted ? 13 : 12;
	case 5: return bInverted ? 17 : 16;
	case 6: return bInverted ? 21 : 20;
	case 7: return bInverted ? 25 : 24;
	case 8: return bInverted ? 29 : 28;
	case 9: return bInverted ? 33 : 32;
	case 10: return bInverted ? 37 : 36;
	case 11: return bInverted ? 41 : 40;
	}
}
