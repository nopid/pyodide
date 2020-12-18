from setuptools import setup, Extension


setup(
    name='hello',
    version='0.1',
    description='Python Package with Hello World C Extension',
    ext_modules=[
        Extension(
            'hello',
            sources=['greetmodule.c'],
            py_limited_api=True)
    ],
)
