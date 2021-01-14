#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Pathfinder.h"

int test(int argc, char *argv[]) {

	Pathfinder* pathptr = NULL;//the Pathfinder
	// Test 2D array
	string filename = argv[1];
    ifstream in(argv[1]);
	pathptr = new Pathfinder();
	pathptr->importMaze(filename);
	cout << pathptr->toString();
	pathptr->solveMaze(filename);
	exit(0);
	// End of Test 2D array
}