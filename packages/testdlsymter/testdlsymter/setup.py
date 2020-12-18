from setuptools import setup, Extension


setup(
    name='testdlsymter',
    version='0.1',
    description='test_dlfcn_self as a Python package',
    ext_modules=[
        Extension(
            'testdlsymter',
            sources=['testmodule.c'],
            py_limited_api=True)
    ],
)
