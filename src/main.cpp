#include <Python.h>
#include "hrdint/oleddisp/oleddisp.h"
#include "hrdint/slowscan/slowscan.h"
#include "hrdint/tempPress/tempPress.h"
#include <iostream>

/** Unix-like platform char * to wchar_t conversion. */
wchar_t *nstrws_convert(char *raw) {
  wchar_t *rtn = (wchar_t *) calloc(1, (sizeof(wchar_t) * (strlen(raw) + 1)));
  setlocale(LC_ALL,"en_US.UTF-8"); // Seriously, eat a bag of dicks python developers. Unless you do this python 3 crashes.
  mbstowcs(rtn, raw, strlen(raw));
  return rtn;
}

/** Dispose of an array of wchar_t * */
void nstrws_dispose(int count, wchar_t ** values) {
  for (int i = 0; i < count; i++) {
    free(values[i]);
  }
  free(values);
}

/** Convert an array of strings to wchar_t * all at once. */
wchar_t **nstrws_array(int argc, char *argv[]) {
  wchar_t **rtn = (wchar_t **) calloc(argc, sizeof(wchar_t *));
  for (int i = 0; i < argc; i++) {
    rtn[i] = nstrws_convert(argv[i]);
  }
  return rtn;
}

int main(int argc, char** argv) {

    // Initialize the Python Interpreter
    Py_Initialize();

	wchar_t** tmpWcharArr = nstrws_array(argc, argv);
	PySys_SetArgv(argc, tmpWcharArr);


	int Temp;

	//Test for Graces code.
	Mux* test = new Mux();
	Temp = test -> getTemperature(0);
	std::cout << Temp << std::endl;
	Temp = test -> getTemperature(1);
	std::cout << Temp << std::endl;

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
	nstrws_dispose(argc, tmpWcharArr);
	
	// Return Zero (Success).
	return 0;
};
