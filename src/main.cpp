#include <Python.h>
#include "hrdint/oleddisp/oleddisp.h"
#include "hrdint/slowscan/slowscan.h"
#include "hrdint/tempPress/tempPress.h"
#include <iostream>

int main() {

    // Initialize the Python Interpreter
    Py_Initialize();
	
	int Temp;
	
	//Test for Graces code.
	Mux* test = new Mux();
	Temp = test -> getTemperature(0);
	cout << Temp;
	Temp = test -> getTemperature(1);
	cout << Temp;
	
	//Create a new instance of OLED Display and Print "Hello World!" to it.
	//OledDisp* test = new OledDisp();
	//test->PrintText(PyUnicode_FromString("Hello World!"));
	//delete test;


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
