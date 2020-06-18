#include "Fuses.h"

void DumpVector(vector<bool> Fuses, uint32_t BlockSize)
{
	for(uint32_t Index = 0; Index < Fuses.size(); Index++)
	{
		if (Index % BlockSize == false)
			printf("%s", "\n");

		bool bTemporary = Fuses[Index];
		printf("%i", bTemporary);
	}
}

bool Fuses::Build(vector<DNF::Expression> Expressions, vector<bool>& FuseListOut)
{
	if (!Expressions.size())
	{
		ERROR("%s", "No expressions were given");
		return false;			
	}

	if (FuseListOut.size())
		FuseListOut.clear();

	//	Set AR Fuses to zero (we don't need them as of yet)

	FuseListOut.resize(5892);
	std:fill(FuseListOut.begin(), FuseListOut.begin() + 44, 1);

	//	Start writing expressions to FuseList.

	for(uint32_t Index = 0; Index < Expressions.size(); Index++)
	{
		uint32_t ExpIndexStart, ExpIndexEnd;

		ExpIndexStart = [Expressions, Index]() -> uint32_t
		{
			uint32_t FuseIndex = 44;

			for (uint32_t OLMC = 23; OLMC > Expressions[Index].m_OutputPin; OLMC--)
				FuseIndex += (Fuses::MaxOutputPinTerms(OLMC) + 1) * 44;

			return FuseIndex;
		}();

		ExpIndexEnd = ExpIndexStart + Fuses::MaxOutputPinTerms(Expressions[Index].m_OutputPin) * 44;

		vector<bool> ExpressionBuffer;

		if (!Fuses::BuildFromExpression(Expressions[Index], Fuses::MaxOutputPinTerms(Expressions[Index].m_OutputPin), 44, ExpressionBuffer)) 
		{
			ERROR("%s", "Couldn't build all expression fuses");
			return false;
		}

		std::copy(ExpressionBuffer.begin(), ExpressionBuffer.end(), FuseListOut.begin() + ExpIndexStart);
	}

	DumpVector(FuseListOut, 32);

	return true;
}

/*
*		Fuses::BuildFromExpression generates a fuselist for a specific expression and outputs the result in a supplied 
*		fuselist. It needs to know the term size and number of rows to correctly pad the fuselist with zeroes. 
*/

bool Fuses::BuildFromExpression(DNF::Expression Expression, uint32_t iNumRows, uint32_t iRowLength, vector<bool>& FuseList)
{
	if(!Fuses::IsValidOutputPin(Expression.m_OutputPin))
	{
		ERROR("%s", "Expression has invalid output pin");
		return false;
	}

	if (!Expression.m_Rows.size() || !iNumRows || !iRowLength)
	{
		ERROR("%s", "Invalid parameters");
		return false;
	}

	if (Expression.m_Rows.size() > Fuses::MaxOutputPinTerms(Expression.m_OutputPin))
	{
		ERROR("%s", "Too many terms for given output pin");
		return false;
	}

	if (FuseList.size())
		FuseList.clear();

	FuseList.resize(iNumRows * iRowLength);

	for(uint32_t TermIndex = 0; TermIndex < Expression.m_Rows.size(); TermIndex++)
	{
		std::fill(FuseList.begin() + TermIndex * iRowLength, FuseList.begin() + TermIndex * iRowLength + iRowLength, true);

		for(uint32_t PinIndex = 0; PinIndex < Expression.m_Rows[TermIndex].m_Pins.size(); PinIndex++)
		{
			int Index = Fuses::PinToIndex
			(
				Expression.m_Rows[TermIndex].m_Pins[PinIndex].m_PinNumber,
				Expression.m_Rows[TermIndex].m_Pins[PinIndex].m_Inverted,
				Expression.m_EnableFlipFlop ? MacrocellMode::MODE_REGISTERED_HIGH : MacrocellMode::MODE_COMBINATORIAL_HIGH
			);

			if(!Index)
			{
				ERROR("%s", "Couldn't resolve PIN index");
				return false;
			}

			FuseList[TermIndex * iRowLength + Index] = false;
		}
	}

	return true;
}

/*
*		Fuses::PinToIndex converts a PIN to a fuselist row index. It takes in a PIN number and a boolean
*		which indicates if the PIN is supposed to be inverted. It requires an extra parameter if the given  
*		PIN number correlates to an output pin. This parameter is called "Mode" and is an enum. The parameter
*		is needed because the output from the OLMC is inverted or not inverted depending on the mode it is
*		operating in (the mode is set through S0 and S1 fuses) so we need to know the mode to correctly pick
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
		case 13: return bInverted ? 43 : 42;
	}

	//	OUTPUT PINS

	if(Mode == MacrocellMode::MODE_COMBINATORIAL_HIGH)
	{
		switch (iPinNumber)
		{
			case 14: return bInverted ? 39 : 38;
			case 15: return bInverted ? 35 : 34;
			case 16: return bInverted ? 31 : 30;
			case 17: return bInverted ? 27 : 26;
			case 18: return bInverted ? 23 : 22;
			case 19: return bInverted ? 19 : 18;
			case 20: return bInverted ? 15 : 14;
			case 21: return bInverted ? 11 : 10;
			case 22: return bInverted ? 7 : 6;
			case 23: return bInverted ? 3 : 2;
		}
	}
	else if(Mode != MacrocellMode::MODE_NONE)
	{
		switch (iPinNumber)
		{
			case 14: return bInverted ? 38 : 39;
			case 15: return bInverted ? 34 : 35;
			case 16: return bInverted ? 30 : 31;
			case 17: return bInverted ? 26 : 27;
			case 18: return bInverted ? 22 : 23;
			case 19: return bInverted ? 18 : 19;
			case 20: return bInverted ? 14 : 15;
			case 21: return bInverted ? 10 : 11;
			case 22: return bInverted ? 6 : 7;
			case 23: return bInverted ? 2 : 3;
		}
	}

	//	Return -1 if we couldn't find an index which fits the given parameters.

	return -1;
}

/*
*		Fuses::MaxOutputPinTerms returns the maximum amount of terms an output OLMC can handle.
*		if the function return value is -1 it means that the given pin number is not an valid output pin 
*		thus the function can't return a valid term number.  
*/

int Fuses::MaxOutputPinTerms(uint32_t iPinNumber)
{
	switch(iPinNumber)
	{
		case 14: return 8;
		case 15: return 10;
		case 16: return 12;
		case 17: return 14;
		case 18: return 16;
		case 19: return 16;
		case 20: return 14;
		case 21: return 12;
		case 22: return 10;
		case 23: return 8;
		default: return -1;
	}
}

//		Fuses::IsValidOutputPin checks if a given pin is an output pin:

bool Fuses::IsValidOutputPin(uint32_t iPinNumber)
{
	if (iPinNumber >= 14 && iPinNumber <= 23)
		return true;
	return false;
}
