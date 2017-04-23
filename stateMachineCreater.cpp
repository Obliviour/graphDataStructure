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
#include <string>

using namespace std;

//----------STRUCT DECLARATIONS---------//

struct nodeMealy {
    nodeMealy(string name_) : name(name_) {}
    nodeMealy(): name("NULL") {}
	string name;
};

struct nodeMoore {
    nodeMoore(string name_, string outputs_) : name(name_), outputs(outputs_) {}
    nodeMoore(): name("NULL"), outputs("NULL") {}
	string name;
    string outputs;
};

struct edgeMealy {
    edgeMealy(nodeMealy* fromNode_, nodeMealy* toNode_, long inputs_, string outputs_) :
        fromNode(fromNode_), toNode(toNode_), inputs(inputs_), outputs(outputs_) {}
    edgeMealy() : fromNode(NULL), toNode(NULL), inputs(0), outputs("NULL") {}
	nodeMealy* fromNode;
	nodeMealy* toNode;
	long inputs;
	string outputs;
};

struct edgeMoore {
    edgeMoore(nodeMoore* fromNode_, nodeMoore* toNode_, long inputs_) :
        fromNode(fromNode_), toNode(toNode_), inputs(inputs_) {}
    edgeMoore() : fromNode(NULL), toNode(NULL), inputs(0) {}
	nodeMoore* fromNode;
	nodeMoore* toNode;
	long inputs;
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

std::list<nodeMealy>::iterator mealyNodeIter;
std::list<nodeMoore>::iterator mooreNodeIter;
std::list<edgeMealy>::iterator mealyEdgeIter;
std::list<edgeMoore>::iterator mooreEdgeIter;


bool compareMealyName(const nodeMealy &lhs, const nodeMealy &rhs) {
    int comp = (lhs.name).compare(rhs.name);
    //int comp = strcmp(lhs.name, rhs.name);
	if (comp < 0) {
		return 1;
	} else if (comp > 0) {
		return 0;
	}
}

bool compareMooreName(const nodeMoore &lhs, const nodeMoore &rhs) {
    int comp = (lhs.name).compare(rhs.name);
    //int comp = strcmp(lhs.name, rhs.name);
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
            cout << "NODE: " << mealyNodeIter->name << endl;
			//printf("NODE: %s\n", mealyNodeIter->name);
			for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter != mealyEdges.end(); ++mealyEdgeIter) {
				if (mealyNodeIter->name == mealyEdgeIter->fromNode->name) {
                    cout << "\t" <<  mealyEdgeIter->fromNode->name << " " << mealyEdgeIter->toNode->name << " ";
                    //NOTE I think this \n isnt suppose to be here
                    //printf("\t%s %s \n", mealyEdgeIter->fromNode->name, mealyEdgeIter->toNode->name);
                    cout << std::bitset<4>(mealyEdgeIter->inputs).to_string() << " / " << mealyEdgeIter->outputs << endl;
				}
			}
		}
	} else {
		mooreNodes.sort(&compareMooreName);
		for (mooreNodeIter = mooreNodes.begin(); mooreNodeIter != mooreNodes.end(); ++mooreNodeIter) {
            cout << "NODE: " << mooreNodeIter->name << " / " << mooreNodeIter->outputs << endl;
			//printf("NODE: %s / %s\n", mooreNodeIter->name, mooreNodeIter->outputs);
			for (mooreEdgeIter = mooreEdges.begin(); mooreEdgeIter != mooreEdges.end(); ++mooreEdgeIter) {
				if (mooreNodeIter->name == mooreEdgeIter->fromNode->name) {
                    cout << "\t" <<  mooreEdgeIter->fromNode->name << " " << mooreEdgeIter->toNode->name << " ";
					//printf("\t%s %s ", mooreEdgeIter->fromNode->name, mooreEdgeIter->toNode->name);
                    cout << std::bitset<4>(mooreEdgeIter->inputs).to_string() << endl;
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
        	printElement(std::bitset<4>(i), 5);
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
        	printElement(std::bitset<4>(i), 5);
		}
		cout << endl;
		separator = '-';
		printElement(' ', pow(2,numInputBits));
		separator = ' ';
		cout << endl;
		mealyNodes.sort(&compareMealyName);
		for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
			printElement(mealyNodeIter->name, 8);
			cout << " / ";
        	printElement(mooreNodeIter->outputs, 5);
			cout << "|";
			for (int i = 0; i < pow(2,numInputBits); i++) {
				for (mealyEdgeIter = mealyEdges.begin(); mealyEdgeIter!= mealyEdges.end(); ++mealyEdgeIter) {
					if (i == mealyEdgeIter->inputs) {
						printElement(mealyEdgeIter->toNode, 8);
						foundInput = 1;
						break;
					}
				}
				if (!foundInput) {
					printElement("X",8);
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
    string input;
    if (isMealy) {
//INTRO PRINT OUT STATEMENTS
        std::cout << "Begin adding NODE and ARC for MEALY State Machine" << endl;
        std::cout << "NODE name" << " or ARC fromNode toNode inputs / outputs" << endl;
        std::cout << "Type GRAPH to print graph and TABLE to print table" << endl;
        std::cout << "Type DONE to finish" << endl;
//DEFINE VARIABLES
        string option;
        string name;
        string outputs;
        string from;
        string to;
        string inputs;
        nodeMealy* before = NULL;
        nodeMealy* after = NULL;
//Begin parsing
        getline(cin, input);
        while(input.compare("DONE")) {
            int pos = 0;
            pos = input.find(" ", pos);                          //finds the location of the first space
            option = input.substr(0,pos);                      //option is now the start of the string to the space
            if (option.compare("NODE") == 0) {
                name = input.substr(pos + 1);                     //name is now the rest of the string (after space 1)
                //cout << "name is " << name << endl;
                nodeMealy nodeMealy_ = nodeMealy(name);
                //cout << "goes through const" << endl;
                //cout << nodeMealy_.name << endl;
                mealyNodes.push_back(nodeMealy_);
                //cout << "goes through pushback" << endl;
                cout << mealyNodes.size() << endl;
                //cout << mealyNodes.back().name << endl;
                cout << nodeMealy_.name << endl;
            } else if (option.compare("ARC") == 0) {
                input = input.substr(pos + 1);               //Update input from pos loc; "from to in / out"
                pos = input.find(" ", 0);                  //finds location of space; index of space
                from = input.substr(0,pos);                  //places from; "from"

                input = input.substr(pos + 1);               //Update input from pos loc
                pos = input.find(" ", 0);                    //finds the next space
                to = input.substr(0,pos);                    //sets this part to to

                input = input.substr(pos + 1);                   //Update input from pos loc
                pos = input.find(" ", 0);                       //  ----
                inputs = input.substr(0,pos);                //  ----

                input = input.substr(pos+3);                 //Updates input to the end of the string (add 2) for '/ '
                outputs = input;                                //Set this to outputs

                int count = 0;
                char * ptr;

                cout << "from node: " << from << " to node: " << to << " inputs: " << inputs << " outputs: " << outputs << endl;
                /**
                 * Check that the name of the arcs (to and from) exist in the std::list
                 */
                for (mealyNodeIter = mealyNodes.begin(); mealyNodeIter != mealyNodes.end(); ++mealyNodeIter) {
                    //cout << mealyNodeIter->name << endl;
                    if ((mealyNodeIter->name).compare(from) == 0) {
                        //cout << "from is in arc" << endl;
                        count++;
                        //cout << &(*mealyNodeIter) <<endl;
                        before = &(*mealyNodeIter);
                        //cout << &(*mealyNodeIter) <<endl;
                    }
                    if ((mealyNodeIter->name).compare(to) == 0) {
                        //cout << "to is in arc " << endl;
                        count++;
                        after = &(*mealyNodeIter);
                    }
                }
                if (count!=2) {
                    cout << "the ARC nodes are not in the array :" << count << endl;
                    getline(cin, input);
                    continue; //asks for next input
                }
                //cout << "now looking at the x possible values" << endl;
                /**
                 * now lets figure how many x's there are in the string
                 */
                const char* inputsCONST = inputs.c_str();
                char inputsCopy[numInputBits];
                strcpy(inputsCopy, inputsCONST);
                int numX = 0;
                int searchLoc = 0;
                searchLoc = inputs.find('x',searchLoc);
                while(searchLoc!=-1) {
                    numX++; //tells me the size
                    searchLoc = inputs.find('x',searchLoc + 1);
                }
                int size = pow(2,numX);
                long numInput[size];
                //cout << "size of numInputs " << size << endl;
                edgeMealy edgeMealy_ = edgeMealy();
                if (numX == 1) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2);
                    *loc = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2);
                    for (int i = 0; i < size; i++) {
                        edgeMealy_ = edgeMealy(before, after, numInput[i], outputs);
                        mealyEdges.push_back(edgeMealy_);
                    }
                } else if (numX == 2) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //00
                    *loc2 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //01
                    *loc = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //11
                    *loc2 = '0';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //10
                    for (int i = 0; i < size; i++) {
                        edgeMealy_ = edgeMealy(before, after, numInput[i], outputs);
                        mealyEdges.push_back(edgeMealy_);
                    }
                } else if (numX == 3) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    char* loc3 = strchr(inputsCopy,'x');
                    *loc3 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //000
                    *loc3 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //001
                    *loc2 = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //011
                    *loc = '1';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //111
                    *loc3 = '0';
                    numInput[4] = strtol(inputsCopy, &ptr, 2); //110
                    *loc2 = '0';
                    numInput[5] = strtol(inputsCopy, &ptr, 2); //100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[6] = strtol(inputsCopy, &ptr, 2); //010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[7] = strtol(inputsCopy, &ptr, 2); //101
                    for (int i = 0; i < size; i++) {
                        edgeMealy_ = edgeMealy(before, after, numInput[i], outputs);
                        mealyEdges.push_back(edgeMealy_);
                    }
                } else if (numX == 4) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    char* loc3 = strchr(inputsCopy,'x');
                    *loc3 = '0';
                    char* loc4 = strchr(inputsCopy,'x');
                    *loc4 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //0000
                    *loc3 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //0001
                    *loc2 = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //0011
                    *loc = '1';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //0111
                    *loc3 = '0';
                    numInput[4] = strtol(inputsCopy, &ptr, 2); //0110
                    *loc2 = '0';
                    numInput[5] = strtol(inputsCopy, &ptr, 2); //0100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[6] = strtol(inputsCopy, &ptr, 2); //0010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[7] = strtol(inputsCopy, &ptr, 2); //1101
                    *loc4 = '1';
                    numInput[8] = strtol(inputsCopy, &ptr, 2); //1000
                    *loc3 = '1';
                    numInput[9] = strtol(inputsCopy, &ptr, 2); //1001
                    *loc2 = '1';
                    numInput[10] = strtol(inputsCopy, &ptr, 2); //1011
                    *loc = '1';
                    numInput[11] = strtol(inputsCopy, &ptr, 2); //1111
                    *loc3 = '0';
                    numInput[12] = strtol(inputsCopy, &ptr, 2); //1110
                    *loc2 = '0';
                    numInput[13] = strtol(inputsCopy, &ptr, 2); //1100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[14] = strtol(inputsCopy, &ptr, 2); //1010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[15] = strtol(inputsCopy, &ptr, 2); //1101
                    for (int i = 0; i < size; i++) {
                        edgeMealy_ = edgeMealy(before, after, numInput[i], outputs);
                        mealyEdges.push_back(edgeMealy_);
                    }
                }
                else {
                    numInput[0] = strtol(inputsCopy, &ptr, 2);
                    edgeMealy edgeMealy_ = edgeMealy(before, after, numInput[0], outputs);
                    mealyEdges.push_back(edgeMealy_);
                    //cout << mealyEdges.size() << endl;
                    //cout << mealyEdges.back().outputs << endl;
                    //cout << edgeMealy_.outputs << endl;
                }
            } else if (option.compare("GRAPH") == 0) {
                printGraph();
            } else if (option.compare("TABLE") == 0) {
                printStateMachine();
            }
            getline(cin, input);
        }
    }
    else {
//INTRO PRINT OUT STATEMENTS
        std::cout << "Begin adding NODE and ARC for MOORE State Machine" << endl;
        std::cout << "NODE name / output" << " or ARC fromNode toNode inputs" << endl;
        std::cout << "Type GRAPH to print graph and TABLE to print table" << endl;
        std::cout << "Type DONE to finish" << endl;
//DEFINE VARIABLES
        string option;
        string name;
        string outputs;
        string from;
        string to;
        string inputs;
        nodeMoore* before = NULL;
        nodeMoore* after = NULL;
//Begin parsing
        getline(cin, input);
        while(input.compare("DONE")) {
            int pos = 0;
            pos = input.find(" ", pos);                          //finds the location of the first space
            option = input.substr(0,pos);                      //option is now the start of the string to the space
            if (option.compare("NODE") == 0) {
                input = input.substr(pos + 1);                   //Update input from pos loc
                pos = input.find(" ", 0);                       //finds location of space
                name = input.substr(0,pos);                  //places from

                input = input.substr(pos+3);                 //Updates input to the end of the string (add 2) for '/ '
                outputs = input;                                //Set this to outputs
                cout << "name: " << name << " output: " << outputs << endl;
                nodeMoore nodeMoore_ = nodeMoore(name, outputs);//creates nodeMoore
                mooreNodes.push_back(nodeMoore_);
                cout << mooreNodes.size() << endl;
                cout << mooreNodes.back().name << endl;
            } else if (option.compare("ARC") == 0) {
                input = input.substr(pos+1);                   //Update input from pos loc
                pos = input.find(" ", 0);                       //finds location of space
                from = input.substr(0,pos);                  //places from

                input = input.substr(pos+1);                   //Update input from pos loc
                pos = input.find(" ", 0);                       //finds the next space
                to = input.substr(0,pos);                    //sets this part to to

                input = input.substr(pos+1);                   //Update input from pos loc
                inputs = input;

                cout << "from: " << from << " to: " << to << " inputs: " << inputs << endl;
                int count = 0;
                char * ptr;
                /**
                 * Check that the name of the arcs (to and from) exist in the std::list
                 */
                for (mooreNodeIter = mooreNodes.begin(); mooreNodeIter != mooreNodes.end(); mooreNodeIter++) {
                    if ((mooreNodeIter->name).compare(from) == 0) {
                        count++;
                        before = &(*mooreNodeIter);
                    }
                    if ((mooreNodeIter->name).compare(to) == 0) {
                        count++;
                        after = &(*mooreNodeIter);
                    }
                }
                if (count!=2) {
                    cout << "the ARC nodes are not in the array :" << count << endl;
                    getline(cin, input);
                    continue; //asks for next input
                }
                /**
                 * now lets figure how many x's there are in the string
                 */
                const char* inputsCONST = inputs.c_str();
                char inputsCopy[numInputBits];
                strcpy(inputsCopy, inputsCONST);
                int numX = 0;
                int searchLoc = 0;
                searchLoc = inputs.find('x',searchLoc);
                while(searchLoc!=-1) {
                    numX++; //tells me the size
                    searchLoc = inputs.find('x',searchLoc + 1);
                }
                int size = pow(2,numX);
                long numInput[size];
                edgeMoore edgeMoore_ = edgeMoore();
                if (numX == 1) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2);
                    *loc = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2);
                    for (int i = 0; i < size; i++) {
                        edgeMoore_ = edgeMoore(before, after, numInput[i]);
                        mooreEdges.push_back(edgeMoore_);
                        //cout << mooreEdges.size() << endl;
                        //cout << mooreEdges.back().inputs << endl;
                    }
                } else if (numX == 2) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //00
                    *loc2 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //01
                    *loc = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //11
                    *loc2 = '0';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //10
                    for (int i = 0; i < size; i++) {
                        edgeMoore_ = edgeMoore(before, after, numInput[i]);
                        mooreEdges.push_back(edgeMoore_);
                        //cout << mooreEdges.size() << endl;
                        //cout << mooreEdges.back().inputs << endl;
                    }
                } else if (numX == 3) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    char* loc3 = strchr(inputsCopy,'x');
                    *loc3 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //000
                    *loc3 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //001
                    *loc2 = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //011
                    *loc = '1';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //111
                    *loc3 = '0';
                    numInput[4] = strtol(inputsCopy, &ptr, 2); //110
                    *loc2 = '0';
                    numInput[5] = strtol(inputsCopy, &ptr, 2); //100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[6] = strtol(inputsCopy, &ptr, 2); //010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[7] = strtol(inputsCopy, &ptr, 2); //101
                    for (int i = 0; i < size; i++) {
                        edgeMoore_ = edgeMoore(before, after, numInput[i]);
                        mooreEdges.push_back(edgeMoore_);
                        //cout << mooreEdges.size() << endl;
                        //cout << mooreEdges.back().inputs << endl;
                    }
                } else if (numX == 4) {
                    char* loc = strchr(inputsCopy,'x');
                    *loc = '0';
                    char* loc2 = strchr(inputsCopy,'x');
                    *loc2 = '0';
                    char* loc3 = strchr(inputsCopy,'x');
                    *loc3 = '0';
                    char* loc4 = strchr(inputsCopy,'x');
                    *loc4 = '0';
                    numInput[0] = strtol(inputsCopy, &ptr, 2); //0000
                    *loc3 = '1';
                    numInput[1] = strtol(inputsCopy, &ptr, 2); //0001
                    *loc2 = '1';
                    numInput[2] = strtol(inputsCopy, &ptr, 2); //0011
                    *loc = '1';
                    numInput[3] = strtol(inputsCopy, &ptr, 2); //0111
                    *loc3 = '0';
                    numInput[4] = strtol(inputsCopy, &ptr, 2); //0110
                    *loc2 = '0';
                    numInput[5] = strtol(inputsCopy, &ptr, 2); //0100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[6] = strtol(inputsCopy, &ptr, 2); //0010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[7] = strtol(inputsCopy, &ptr, 2); //1101
                    *loc4 = '1';
                    numInput[8] = strtol(inputsCopy, &ptr, 2); //1000
                    *loc3 = '1';
                    numInput[9] = strtol(inputsCopy, &ptr, 2); //1001
                    *loc2 = '1';
                    numInput[10] = strtol(inputsCopy, &ptr, 2); //1011
                    *loc = '1';
                    numInput[11] = strtol(inputsCopy, &ptr, 2); //1111
                    *loc3 = '0';
                    numInput[12] = strtol(inputsCopy, &ptr, 2); //1110
                    *loc2 = '0';
                    numInput[13] = strtol(inputsCopy, &ptr, 2); //1100
                    *loc = '0';
                    *loc2 = '1';
                    numInput[14] = strtol(inputsCopy, &ptr, 2); //1010
                    *loc = '1';
                    *loc2 = '0';
                    *loc3 = '1';
                    numInput[15] = strtol(inputsCopy, &ptr, 2); //101
                    for (int i = 0; i < size; i++) {
                        edgeMoore_ = edgeMoore(before, after, numInput[i]);
                        mooreEdges.push_back(edgeMoore_);
                        //cout << mooreEdges.size() << endl;
                        //cout << mooreEdges.back().inputs << endl;
                    }
                }
                else {
                    numInput[0] = strtol(inputsCopy, &ptr, 2);
                    edgeMoore edgeMoore_ = edgeMoore(before, after, numInput[0]);
                    mooreEdges.push_back(edgeMoore_);
                    //cout << mooreEdges.size() << endl;
                    //cout << mooreEdges.back().inputs << endl;
                }
            } else if (option.compare("GRAPH") == 0) {
                printGraph();
            } else if (option.compare("TABLE") == 0) {
                printStateMachine();
            }
            getline(cin, input);
        }
    }
}

int main() {
    setUp();
    setUpNodes();


	return 0;
}
