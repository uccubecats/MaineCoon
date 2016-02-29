#include <Python.h>
#include <iostream>

class SensorLib
{

	private:
		PyObject* pName;
		PyObject* pModule;
		PyObject* pDict;
		PyObject* pClass;
		PyObject* pInstance;
		PyObject* pValue;

	public:
		SensorLib();
		void performNameTask(PyObject* text);
		double getInternalTemperature();
		double getExternalTemperature();
		double getOrientation();
		void sendAprsPackets(PyObject* text);
		virtual ~SensorLib();
};
