#include "Stub.hpp"

/*
*	This main is not the main which will be used in the final compile of EasyGal.
*	It is only used to compile the stub which feeds the TableData to the translator.
*/

using namespace std;

#include "Serialization.h"

int main() 
{
	std::vector<bool> states;
	states.resize(511);
	states.insert(states.begin(), true);
	states.insert(states.begin() + 52, true);
	states.resize(511);

	for(uint32_t Index = 0; Index < states.size(); Index++)
	{
		if (Index % 32 == 0)
			printf("%s", "\n");

		bool b = states[Index];

		printf("%i", b);
	}

	JEDEC testFile(24, 5892, states, "Out.jed");
	testFile.Serialize();
}