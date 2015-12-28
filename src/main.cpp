#include <Python.h>
//#include "hrdint/oleddisp/oleddisp.h"
#include "hrdint/slowscan/slowscan.h"

int main() {

    // Initialize the Python Interpreter
    Py_Initialize();
	
	SlowScan* test = new SlowScan();
	test->playFile(PyUnicode_FromString("Hello World!"));
	delete test;

    // Finish the Python Interpreter
    Py_Finalize();
	
	// Return Zero (Success).
	return 0;
};
