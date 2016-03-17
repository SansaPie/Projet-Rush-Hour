#ifndef _TEST_GENERAL_H_
#define _TEST_GENERAL_H_
#include <stdbool.h>

bool test_equality_bool(bool expected, bool  value, char *msg);
bool test_equality_int(int expected, int value, char *msg);

#endif // !_TEST_GENERAL_H_
