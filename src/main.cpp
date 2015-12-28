#include <Python.h>
#include "hrdint/oleddisp/oleddisp.h"
#include "hrdint/slowscan/slowscan.h"

int main() {

    // Initialize the Python Interpreter
    Py_Initialize();
	
	//Create a new instance of OLED Display and Print "Hello World!" to it.
	OledDisp* test = new OledDisp();
	test->PrintText(PyUnicode_FromString("Hello World!"));
	delete test;


/*	//Create a new instance of OLED Display and Print "Hello World!" to it.
	SlowScan* test2 = new SlowScan();
	test2->playFile(PyUnicode_FromString(<file_path name>));
	delete test2;
*/

    // Finish the Python Interpreter
    Py_Finalize();
	
	// Return Zero (Success).
	return 0;
};
