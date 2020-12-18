from setuptools import setup, Extension


setup(
    name='testdlsymbis',
    version='0.1',
    description='test_dlfcn_self as a Python package',
    ext_modules=[
        Extension(
            'testdlsymbis',
            sources=['testmodule.c'],
            py_limited_api=True)
    ],
)
