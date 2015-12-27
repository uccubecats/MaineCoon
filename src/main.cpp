#include <Python.h>
#include "hrdint/oleddisp/oleddisp.h"

int main() {

    // Initialize the Python Interpreter
    Py_Initialize();
	
	OledDisp* test = new OledDisp();
	test->PrintText(PyUnicode_FromString("Hello World!"));
	delete test;

    // Finish the Python Interpreter
    Py_Finalize();
	
	// Return Zero (Success).
	return 0;
};
