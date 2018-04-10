from distutils.core import setup, Extension

simplemod = Extension('simplemod', sources=['simplemod.c'])

setup(name='simplemod',
      version='0.1',
      description = 'Sum a list of integers',
      ext_modules = [simplemod])

