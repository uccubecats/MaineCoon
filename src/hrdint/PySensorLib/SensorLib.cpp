#include "SensorLib.h"

SensorLib::SensorLib()
{

	// Initialize variables.
	pValue = NULL;

    // Build the name object
    pName = PyUnicode_FromString("PySensorLib");
    PyErr_Print();

    // Load the module object
    pModule = PyImport_Import(pName);
    PyErr_Print();

    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    PyErr_Print();
   
    // Build the name of a callable class
    pClass = PyDict_GetItemString(pDict, "PySensorLib");
    PyErr_Print();
	
    // Create an instance of the class
    if (PyCallable_Check(pClass))
    {
        pInstance = PyObject_CallObject(pClass, NULL);
	}
    else 
    {
	std::cout << "Failed..." << std::endl;
        PyErr_Print();
    }
}

void SensorLib::performNameTask(PyObject* text)
{
	
	// Call the function "performNameTask" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "performNameTask", "(O)", text);
}

double SensorLib::getInternalTemperature()
{
	
	// Call the function "getInternalTemperature" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "getInternalTemperature", "O()");
	
	// Return the converted value.
	return PyFloat_AsDouble(pValue);
}

double SensorLib::getExternalTemperature()
{
	
	// Call the function "getExternalTemperature" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "getExternalTemperature", "O()");
	
	// Return the converted value.
	return PyFloat_AsDouble(pValue);
}

double SensorLib::getOrientation()
{
	
	// Call the function "getOrientation" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "getOrientation", "O()");
	
	// Return the converted value.
	return PyFloat_AsDouble(pValue);
}

void SensorLib::sendAprsPackets(PyObject* text)
{
	
	// Call the function "PrintText" in PythonLand.
    pValue = PyObject_CallMethod(pInstance, "sendAprsPackets", "(O)", text);
}

SensorLib::~SensorLib()
{

    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
}
