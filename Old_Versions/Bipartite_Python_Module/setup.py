from distutils.core import setup, Extension 

bip_module = Extension('bip_module', sources=['bip_py_module.c','bipartite_mod.c'])

setup(name='bip_module',
      version='0.1',
      description = 'Check if a graph is Bipartite or not',
      ext_modules = [bip_module])

