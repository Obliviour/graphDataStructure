/**
 * Derin Ozturk and Victor Barr
 * ECE3020 Project 3
 */

#include <stdio.h>
#include <string.h>
#include <list>
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;
struct nodeMealy {
    nodeMealy(char* name_) : name(name_) {}
	char* name;
};

struct nodeMoore {
    nodeMoore(char* name_) : name(name_) {}
	char* name;
};

struct edgeMealy {
    edgeMealy(nodeMealy* fromNode_, nodeMealy* toNode_, int inputs_, char* outputs_) :
        fromNode(fromNode_), toNode(toNode_), inputs(inputs_), outputs(outputs_) {}
	nodeMealy* fromNode;
	nodeMealy* toNode;
	int inputs;
	char* outputs;
};

struct edgeMoore {
    edgeMoore(nodeMoore* fromNode_, nodeMoore* toNode_, int inputs_) :
        fromNode(fromNode_), toNode(toNode_), inputs(inputs_) {}
	nodeMoore* fromNode;
	nodeMoore* toNode;
	int inputs;
};

//----------GLOBAL VARIABLES---------//

int isMealy = 0;
int numStates = 25;
int numInputBits = 4;
std::list<nodeMealy> mealyNodes;
std::list<nodeMoore> mooreNodes;
std::list<edgeMealy> mealyEdges;
std::list<edgeMoore> mooreEdges;

std::list<nodeMealy>::const_iterator mode;

void setUp() {
    std::cout << "Welcome to Derin and Victor's State Generator" << std::endl;
    std::cout << "Press enter after each of the following input specifications" << std::endl;
    std::cout << "How many states will you have? (INT 1 - 25)" << std::endl;
    int numStates_temp = 0;
    std::cin >> numStates_temp;
    if (numStates_temp <= 25 && numStates_temp > 0)
        numStates = numStates_temp;
    else {
        std::cout << "Incorrect number of states" << std::endl;
        std::exit(0);
    }
    std::cout << "How many input bits? (INT 1-4)" << std::endl;
    int numInputBits_temp = 0;
    std::cin >> numInputBits_temp;
    if (numInputBits_temp <= 4 && numInputBits_temp > 0)
        numInputBits = numInputBits_temp;
    else {
        std::cout << "Incorrect number of input bits" << std::endl;
        std::exit(0);
    }
    std::cout << "Mealy (Press 1) or Moore Machine (Press 0)?" << std::endl;
    int isMealy_temp = 0;
    std::cin >> isMealy_temp;
    if (isMealy_temp != 0 && isMealy_temp != 1) {
        std::cout << "Not a 0 or 1 input, exit program";
        std::exit(0);
    } else isMealy = isMealy_temp;
}

void setUpNodes() {
    if (isMealy) {
        std::cout << "Begin adding NODE and ARC for MEALY State Machine" << endl;
        std::cout << "NODE name" << " or ARC fromNode toNode inputs / outputs" << endl;
        std::cout << "Type DONE to finish" << endl;
    }
    else {
        std::cout << "Begin adding NODE and ARC for MOORE State Machine" << endl;
        std::cout << "NODE name / output" << " or ARC fromNode toNode inputs" << endl;
        std::cout << "Type DONE to finish" << endl;
    }
}

int main() {
    setUp();
	return 0;
}
