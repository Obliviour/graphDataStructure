/**
 * Derin Ozturk and Victor Barr
 * ECE3020 Project 3
 */

#include <stdio.h>
#include <string.h>
//----------GLOBAL VARIABLES---------//

enum stateType {
    MEALY = 0,
    MOORE
};
int numStates = 25;
int numInputBits = 4;


struct NodeMealy {
	char name[8];
}

struct NodeMoore {
	char name[8];
}

struct edgeMealy {
	NodeMealy* fromNode;
	NodeMealy* toNode;
	int inputs;
	char outputs[6];
}

struct edgeMoore {
	NodeMoore* fromNode;
	NodeMoore* toNode;
	int intputs;
}

int main() {

	return 0;
}
