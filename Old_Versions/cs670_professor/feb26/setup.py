from distutils.core import setup, Extension
setup(name='ab', version='1.0', ext_modules=[Extension('ab', ['nonsense.c'])])
