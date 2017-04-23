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
#include <stdlib.h>
#include <cmath>
#include <bitset>

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
char separator = ' ';
std::list<nodeMealy> mealyNodes;
std::list<nodeMoore> mooreNodes;
std::list<edgeMealy> mealyEdges;
std::list<edgeMoore> mooreEdges;

std::list<nodeMealy>::const_iterator mealyNodeIter;
std::list<nodeMoore>::const_iterator mooreNodeIter;
std::list<edgeMealy>::const_iterator mealyEdgeIter;
std::list<edgeMoore>::const_iterator mooreEdgeIter;


bool compareMealyName(const mealyNode &lhs, const mealyNode &rhs) {
	int comp = strcmp(lhs.name, rhs.name);
	if (comp < 0) {
		return 1;
	} else if (comp > 0) {
		return 0;
	}
}

bool compareMooreName(const mooreNode &lhs, const mooreNode &rhs) {
	int comp = strcmp(lhs.name, rhs.name);
	if (comp < 0) {
		return 1;
	} else if (comp > 0) {
		return 0;
	}
}

void printGraph() {
	if (isMealy) {
		mealyNodes.sort(&compareMealyName);
		for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
			printf("NODE: %s\n", mealyNodeIter->name);
			for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter != mealyEdges.end(); ++mealyEdgeIter) {
				if (mealyNodeIter->name == mealyEdgeIter->fromNode->name) {
					printf("\t%s %s %i / %s\n", mealyEdgeIter->fromNode->name, mealyEdgeIter->toNode->name,
										std::bitset<32>(mealyEdgeIter->inputs), mealyEdgeIter->outputs);
				}
			}
		}
	} else {
		mooreNodes.sort(&compareMooreName);
		for (mooreNodeIter = mooreNodes.begin(); mooreNodeIter != mooreNodes.end(); ++mooreNodeIter) {
			printf("NODE: %s / %s\n", mooreNodeIter->name, mooreNodeIter->outputs);
			for (mooreEdgeIter = mooreEdges.begin(); mooreEdgeIter != mooreEdges.end(); ++mooreEdgeIter) {
				if (mooreNodeIter->name == mooreEdgeIter->fromNode->name) {
					printf("\t%s %s %i\n", mooreEdgeIter->fromNode->name, mooreEdgeIter->toNode->name,
										std::bitset<32>(mooreEdgeIter->inputs));
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
	
	bool foundInput = 0;
	if (isMealy) {
		printElement("Curr State", 10);
		printElement("|", pow(2, numInputBits) * 6 - 19);
		printElement("Next State / Output", pow(2,numInputBits) * 6);
		cout << endl;
		printElement("", 10);
		for (int i = 0; i < pow(2,numInputBits); i++) {
        	printElement(std::bitset<32>(i), 5);
		}
		cout << endl;
		separator = '-';
		printElement(' ', pow(2,numInputBits));
		separator = ' ';
		cout << endl;
		mealyNodes.sort(&compareMealyName);
		for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
			printElement(mealyNodeIter->name, 10);
			printElement("|", 1);
			for (int i = 0; i < pow(2,numInputBits); i++) {
				for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter!= mealyEdges.end(); ++mealyEdgeIter) {
					if (i == mealyEdgeIter->inputs) {
						printElement(mealyEdgeIter->toNode, 8);
						cout << " / ";
						printElement(mealyEdgeIter->outputs, 5);
						foundInput = 1;
						break;
					}
				}
				if (!foundInput) {
					printElement("X",8);
					cout << " / ";
					printElement("X",8);
				}
			}
			cout<<endl;
		}
	} else {
		printElement("Curr State /", 10);
		printElement("|", pow(2, numInputBits) * 6 - 10);
		printElement("Next State", pow(2,numInputBits) * 6);
		cout << endl;
		printElement("Output", 10);
		for (int i = 0; i < pow(2,numInputBits); i++) {
        	printElement(std::bitset<32>(i), 5);
		}
		cout << endl;
		separator = '-';
		printElement(' ', pow(2,numInputBits));
		separator = ' ';
		cout << endl;
		mealyNodes.sort(&compareMealyName);
		for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
			printElement(mealyNodeIter->name, 10);
			cout << " / ";
        	printElement(mooreNodeIter->outputs)
			cout << "|"
			for (int i = 0; i < pow(2,numInputBits); i++) {
				for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter!= mealyEdges.end(); ++mealyEdgeIter) {
					if (i == mealyEdgeIter->inputs) {
						printElement(mealyEdgeIter->toNode, 8);
						foundInput = 1;
						break;
					}
				}
				if (!foundInput) {
					printElement("X",8);;
				}
			}
			cout<<endl;
		}
	}


}


void setUp() {
    std::cout << "Welcome to Derin and Victor's State Generator" << std::endl;
    std::cout << "Press enter after each of the following input specifications" << std::endl;
    std::cout << "How many states will you have? (INT 1 - 25)" << std::endl;
    int numStates_temp = 0;
    std::cin >> numStates_temp;
    if (numStates_temp <= 25 && numStates_temp > 0) {
        numStates = numStates_temp; }
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
