#include "TempPressWrapper.h"

TempPressWrapper::TempPressWrapper()
{

	// Initialize variables.
	pValue = NULL;

    // Build the name object
    pName = PyUnicode_FromString("MS5607");

    // Load the module object
    pModule = PyImport_Import(pName);
    PyErr_Print();

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    PyErr_Print();
   
    // Build the name of a callable class
    pClass = PyDict_GetItemString(pDict, "MS5607");
	
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

float TempPressWrapper::getTemperature()
{
	
	// Call the function "PrintText" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "PrintText", "F()");
}

TempPressWrapper::~TempPressWrapper()
{
	// Unused
}
