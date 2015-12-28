#include "slowscan.h"

SlowScan::SlowScan()
{

	// Initialize variables.
	pValue = NULL;

    // Build the name object
    pName = PyUnicode_FromString("pyslowscan");
    std::cout << "1" << std::endl;

    // Load the module object
    pModule = PyImport_Import(pName);
    std::cout << "2" << std::endl;
    PyErr_Print();

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    PyErr_Print();
    std::cout << "3" << std::endl;
   
    // Build the name of a callable class
    pClass = PyDict_GetItemString(pDict, "SlowScan");
    std::cout << "4" << std::endl;
	
    // Create an instance of the class
    if (PyCallable_Check(pClass))
    {
        pInstance = PyObject_CallObject(pClass, NULL);
	}
    else 
    {
        PyErr_Print();
    }
}

void SlowScan::playFile(PyObject* file_path)
{
	
	// Call the function "PrintText" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "playFile", "(O)", file_path);
}

SlowScan::~SlowScan()
{

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
}
