#include "Stub.hpp"

/*
*	This main is not the main which will be used in the final compile of EasyGal.
*	It is only used to compile the stub which feeds the TableData to the translator.
*/

using namespace std;

#include "Fuses.h"
#include "Configs.h"

int main() 
{
	TableData Data;
	Data.m_InputPins = { 1, 2 };
	Data.m_OutputPin = 23;
	Data.m_EnableFlipFlop = false;
	Data.m_Table = { 0, 0, 0, 1 };

	LOG("%i", Translator::Process(vector<TableData>{Data}, "out", "out.jed"));
}