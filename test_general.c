#include <stdio.h>
#include <stdlib.h>
#include "test_general.h"

/**
* @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
* @return true if expected==value
*/
bool test_equality_int(int expected, int value, char * msg) {
	if (expected != value)
		fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
	return expected == value;
}

/**
* @brief test if value is equal to expected; if not, displays an error message containing msg to standard error output
*/
bool test_equality_bool(bool expected, bool value, char * msg) {
	if (expected != value)
		fprintf(stderr, "ERR: value expected %d ; value computed %d. %s\n", expected, value, msg);
	return expected == value;
}

