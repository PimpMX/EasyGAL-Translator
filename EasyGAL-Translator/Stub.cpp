#include "Stub.hpp"

/*
*	This main is not the main which will be used in the final compile of EasyGal.
*	It is only used to compile the stub which feeds the TableData to the translator.
*/

using namespace std;

#include "Fuses.h"

int main() 
{
	TableData Data;

	Data.m_InputPins = { 2, 3 };
	Data.m_OutputPin = 22;
	Data.m_EnableFlipFlop = false;
	Data.m_Table = { 0, 1, 1, 1 };

	DNF::Expression Expression;
	LOG("%i", DNF::Build(Data, Expression));

	vector<bool> Fuselist;

	LOG("%i", Fuses::BuildFromExpression(Expression, 8, 44, Fuselist));

	for(uint32_t Index = 0; Index < Fuselist.size(); Index++)
	{
		if (Index % 44 == 0)
			printf("%s", "\n");

		bool b = Fuselist[Index];
		printf("%i", b);
	}
}