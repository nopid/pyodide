#include <Python.h>
#include <stdio.h>
#include <dlfcn.h>
#include <emscripten.h>

int EMSCRIPTEN_KEEPALIVE global = 123;

EMSCRIPTEN_KEEPALIVE void foo(int x) {
	char buffer[64];
        sprintf(buffer,"print(%d)", x);
	PyRun_SimpleString(buffer);
}

EMSCRIPTEN_KEEPALIVE void repeatable() {
	char buffer[1024];
        void* self = dlopen("/lib/python3.8/site-packages/testdlsym.so", RTLD_LAZY);
        int* global_ptr = (int*)dlsym(self, "global");
        void (*foo_ptr)(int) = (void (*)(int))dlsym(self, "foo");
        if (!foo_ptr) {
          sprintf(buffer,"print('''dlsym failed: %s''')", dlerror());
	  PyRun_SimpleString(buffer);
          return;
        }
        foo_ptr(*global_ptr);
	(*global_ptr)++;
        dlclose(self);
}

static PyObject *
runtest(PyObject *self, PyObject *args)
{
    repeatable();
    repeatable();

    Py_RETURN_NONE;
}

static PyMethodDef TestDlSymMethods[] = {
    {"run", runtest, METH_VARARGS, "run dlsym tests"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef testdlsym =
{
    PyModuleDef_HEAD_INIT,
    "testdlsym",     /* name of module */
    "",          /* module documentation, may be NULL */
    -1,          /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    TestDlSymMethods
};

PyMODINIT_FUNC PyInit_testdlsym(void)
{
    global=54;
    return PyModule_Create(&testdlsym);
}
