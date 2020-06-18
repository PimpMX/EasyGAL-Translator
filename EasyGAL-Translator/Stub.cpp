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

	Data.m_InputPins = { 2, 4 };
	Data.m_OutputPin = 23;
	Data.m_EnableFlipFlop = false;
	Data.m_Table = { 0, 1, 1, 1 };

	DNF::Expression Expression;
	LOG("%i", DNF::Build(Data, Expression));

	vector<bool> Fuselist;
	Fuses::Build(vector<DNF::Expression> {Expression}, Fuselist);
}