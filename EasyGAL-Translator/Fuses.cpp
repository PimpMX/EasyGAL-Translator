#include "Fuses.h"

bool Fuses::Build(vector<DNF::Expression> Expressions)
{
	return false;
}

bool Fuses::BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength)
{
	return false;
}

/*
*		Fuses::PinToIndex converts a PIN to a fuselist row index. It takes in a PIN number and a boolean
*		which indicates if the PIN is supposed to be inverted. It requires an extra parameter if the given  
*		PIN number correlates to an output pin. This parameter is called "Mode" and is an enum. The parameter
*		is needed because the output from the OLMC is inverted or not inverted depending from the mode it is
*		operating in (the mode is set through AR and SP fuses) so we need to know the mode to correctly pick
*		the inverted or non inverted output from the OLMC output. 
*		
*		Note: The "Mode" parameter is ignored if the PIN number correlates to an input pin. If the PIN is an 
*		output pin and the parameter is not set the function will return -1 which is not a valid index.
*		
*		Note: If the return value is -1 that means that the function couldn't find a valid index for the given
*		parameters.
*/

int Fuses::PinToIndex(uint32_t iPinNumber, bool bInverted, MacrocellMode Mode)
{
	//	INPUT PINS

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

	//	OUTPUT PINS

	if(Mode == MacrocellMode::MODE_COMBINATORIAL_HIGH)
	{
		switch (iPinNumber)
		{
			case 12: return bInverted ? 43 : 42;
			case 13: return bInverted ? 39 : 38;
			case 14: return bInverted ? 35 : 34;
			case 15: return bInverted ? 31 : 30;
			case 16: return bInverted ? 27 : 26;
			case 17: return bInverted ? 23 : 22;
			case 18: return bInverted ? 19 : 18;
			case 19: return bInverted ? 15 : 14;
			case 20: return bInverted ? 11 : 10;
			case 21: return bInverted ? 7 : 6;
			case 22: return bInverted ? 3 : 2;
		}
	}
	else if(Mode != MacrocellMode::MODE_NONE)
	{
		switch (iPinNumber)
		{
			case 12: return bInverted ? 43 : 42;
			case 13: return bInverted ? 38 : 39;
			case 14: return bInverted ? 34 : 35;
			case 15: return bInverted ? 30 : 31;
			case 16: return bInverted ? 26 : 27;
			case 17: return bInverted ? 22 : 23;
			case 18: return bInverted ? 18 : 19;
			case 19: return bInverted ? 14 : 15;
			case 20: return bInverted ? 10 : 11;
			case 21: return bInverted ? 6 : 7;
			case 22: return bInverted ? 2 : 3;
		}
	}

	//	Return -1 if we couldn't find an index which fits the given parameters.

	return -1;
}
