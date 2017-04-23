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
    nodeMoore(char* name_, char* outputs_) : name(name_), outputs(outputs_) {}
	char* name;
    char* outputs;
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

std::list<nodeMealy>::const_iterator mealyNodeIter;
std::list<nodeMoore>::const_iterator mooreNodeIter;
std::list<edgeMealy>::const_iterator mealyEdgeIter;
std::list<edgeMoore>::const_iterator mooreEdgeIter;

bool compareMealyName(const mealyNodes &lhs, const mealyNodes &rhs) {
	int comp = strcmp(lhs.name, rhs.name);
	if (comp < 0) {
		return 1;
	} else if (comp > 0) {
		return 0;
	}
}

bool compareMooreName(const mooreNodes &lhs, const mooreNodes &rhs) {
	int comp = strcmp(lhs.name, rhs.name);
	if (comp < 0) {
		return 1;
	} else if (comp > 0) {
		return 0;
	}
}

void printGraph() {
	if (isMealy) {
		mealyNodes.sort(&compareMealyName)
		for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
			printf("NODE: %s\n", mealyNodeIter->name);
			for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter != mealyEdges.end(); ++mealyEdgeIter) {
				if (mealyNodeIter == mealyEdgeIter->fromNode) {
					printf("\t%s %s %i / %s\n", mealyEdgeIter->fromNode->name, mealyEdgeIter->toNode->name,
										mealyEdgeIter->inputs, mealyEdgeIter->outputs);
				}
			}
		}
	} else {
		mooreNodes.sort(&compareMooreName)
		for (mooreNodeIter = mooreNodes.begin(); mooreNodeIter != mooreNodes.end(); ++mooreNodeIter) {
			printf("NODE: %s / %s\n", mealyNodeIter->name, mealyNodeIter->outputs);
			for (mooreEdgeIter = mooreEdgeIter.begin(); mooreEdgeIter != mooreEdges.end(); ++mooreEdgeIter) {
				if (mooreNodeIter == mooreNodeIter->fromNode) {
					printf("\t%s %s %i\n", mooreEdgeIter->fromNode->name, mooreEdgeIter->toNode->name,
										mooreEdgeIter->inputs);
				}
			}
		}
	}
}

template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
}

void printStateMachine() {
	printElement("Curr State", 10);
	printElement("|", math.pow(2, numInputBits) * 6 - 19);
	printElement("Next State / Output", math.pow(2,numInputBits) * 6 - 19);
	cout << endl;
	printElement("", 10)
	char buffer[4];
	for (int i = 0; i < math,pow(2,numInputBits); i++) {
		itoa(i,buffer,2);
		printElement(buffer, 8);

	}
}


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
