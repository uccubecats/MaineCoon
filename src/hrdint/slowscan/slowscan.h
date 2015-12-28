#include <Python.h>
#include <iostream>

class SlowScan
{

	private:
		PyObject* pName;
		PyObject* pModule;
		PyObject* pDict;
		PyObject* pClass;
		PyObject* pInstance;
		PyObject* pValue;

	public:
		SlowScan();
		void playFile(PyObject* text);
		virtual ~SlowScan();
};
