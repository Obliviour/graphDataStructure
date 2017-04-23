/**
 * Derin Ozturk and Victor Barr
 * ECE3020 Project 3
 */

#include <stdio.h>
#include <string.h>
#include <list>

struct nodeMealy {
	char name[8];
}

struct nodeMoore {
	char name[8];
	char outputs[6]
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

//----------GLOBAL VARIABLES---------//

enum stateType {
    MEALY = 0,
    MOORE
};
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


int main() {

	return 0;
}
