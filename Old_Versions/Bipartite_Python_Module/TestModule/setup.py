from distutils.core import setup, Extension

cs670mod = Extension('cs670mod', sources=['cs670mod.c','proof.c'])

setup(name='cs670mod',
      version='0.1',
      description = 'Faster chromatic number',
      ext_modules = [cs670mod])

