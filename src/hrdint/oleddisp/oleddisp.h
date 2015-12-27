#include <Python.h>
#include <iostream>

class OledDisp
{

	private:
		PyObject* pName;
		PyObject* pModule;
		PyObject* pDict;
		PyObject* pClass;
		PyObject* pInstance;
		PyObject* pValue;

	public:
		OledDisp();
		void PrintText(PyObject* text);
		virtual ~OledDisp();
};
