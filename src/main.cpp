#include "Python.h"

int main() {
	Py_Initialize();
	// Return zero (success).

	Py_Finalize();
	return 0;
};
