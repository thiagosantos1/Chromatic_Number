from distutils.core import setup, Extension 

bip_py_module = Extension('bip_py_module', sources=['bip_py_module.c'])

setup(name='bip_py_module',
      version='0.1',
      description = 'Check if a graph is Bipartite or not',
      ext_modules = [bip_py_module])

