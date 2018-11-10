
#include "util.h"

/////////////////////////////////////////////////
// helper function so that we can treat
// arrays like a circularly linked list
/////////////////////////////////////////////////
int positive_modulo(int i, int n) {
	return (i % n + n) % n;
}

