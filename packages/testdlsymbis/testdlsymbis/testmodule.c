#include <Python.h>
#include <stdio.h>
#include <dlfcn.h>
#include <emscripten.h>


static PyObject *
runtest(PyObject *self, PyObject *args)
{ 
    char buffer[1024];
    void* damod = dlopen("/lib/python3.8/site-packages/testdlsym.so", RTLD_LAZY);
    int* global_ptr = (int*)dlsym(damod, "global");
    void (*foo_ptr)(int) = (void (*)(int))dlsym(damod, "foo");
    if (!foo_ptr) {
          sprintf(buffer,"print('''dlsymbis failed: %s''')", dlerror());
	  PyRun_SimpleString(buffer);
	  Py_RETURN_NONE;
    }
    foo_ptr(*global_ptr);
    (*global_ptr)++;
    (*global_ptr)++;
    (*global_ptr)++;
    dlclose(damod);

    Py_RETURN_NONE;
}

static PyMethodDef TestDlSymMethods[] = {
    {"run", runtest, METH_VARARGS, "run dlsymbis tests"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef testdlsymbis =
{
    PyModuleDef_HEAD_INIT,
    "testdlsymbis",     /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    TestDlSymMethods
};

PyMODINIT_FUNC PyInit_testdlsymbis(void)
{
    return PyModule_Create(&testdlsymbis);
}
