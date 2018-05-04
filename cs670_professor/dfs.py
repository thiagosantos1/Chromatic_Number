#!/usr/bin/env python3

#
# Recursive coloring procedure to verify claim that g627 does not admit a 4-coloring
# in which the first three vertices are monochromatic.  Takes 2.3 seconds on my i7 NUC.
#
#      - Geoffrey Exoo, Apr 29, 2018
#

import sys                  # for exit

from g627 import v627       # needs the data module for the coordiates of g627

rad = [3,11,1,33]           # coordinate radicals

def lenSquared(v):          # memoized length squared computation
   global rad, lenhash

   key = str(v)
   if key in lenhash:
      return lenhash[key]
   a = sum([rad[i]*v[i]**2 for i in range(4)])   # distance squared will be a + b*sqrt(33)
   b = 2*v[0]*v[1] + 2*v[2]*v[3]
   val = (a,b)
   lenhash[key] = val
   return val

def distBetween(u,v):       # distance squared between a pair of vertices

   return lenSquared([u[i] - v[i] for i in range(4)])

def mycopy1(src):            # deep copy a list of lists (faster than copy module)
   dst = []
   for u in src:
      tmp = []
      for v in u:
         tmp.append(v)
      dst.append(set(tmp))   # forgot about this in version 1
   return dst

def mycopy2(src):            # deep copy a list
   dst = []
   for u in src:
      dst.append(u)
   return dst

def colorvertex(v,c):        # try to color vertex v with c, consider the consequences
   global alist,color

   color[v] = c
   for u in alist[v]:                # for each neighbor
      if color[u] == c:                        # already colored c?  give up.
         return False
      if (color[u] < 0) and (c in avail[u]):   # uncolored and c feasible?
         avail[u] -= {c}                           # no longer feasible
         if len(avail[u]) == 0:                    # out of color options? give up
            return False
         elif len(avail[u]) == 1:              # only one color option?  use it
            d = avail[u].pop()
            if not colorvertex(u,d):               # can't use it?  give up
               return False
            avail[u].add(d)
   return True

def dfs(v):
   global alist, color, avail, vmax

   if v > vmax:                                # entertainment
      vmax = v
      n = 0
      for i in range(627):
         if color[i] >= 0:
            n += 1
      print("depth =", vmax, " vertices colored =",n)
      sys.stdout.flush()                       # in case we divert output and want to watch

   if v == 627:                                # all vertices colored? save coloring
      print("Coloring found?")
      print(color)
      for u in range(n):                       # recheck coloring
         for v in alist[u]:
            if color[u] == color[v]:
               print("conflict at",u,v)
      sys.exit(0)
   if color[v] >= 0:                           # color already forced?  on to next vertex
      dfs(v+1)
      return
   tmpavail = mycopy1(avail)                   # save state -- this part is 100+ times faster in C
   tmpcolor = mycopy2(color)
   for c in tmpavail[v]:                       # try each feasible color
      if colorvertex(v,c):
         dfs(v+1)
      avail = mycopy1(tmpavail)                # restore state
      color = mycopy2(tmpcolor)

if __name__ == "__main__":

   lenhash = {}                                # init hash length memoization
   n = len(v627)                               # vertex count
   m = 0                                       # edge count init
   alist = []                                  # becomes adjacency list
   for u in range(n):
      nbrs = []                                # init list of neighbors for u
      for v in range(n):
         if u == v:
            continue
         d = distBetween(v627[u], v627[v])
         if d[0] == 1296 and d[1] == 0:        # 36 is our unit distance (36*36 == 1296)
            nbrs.append(v)
            m += 1
      alist.append(nbrs)

   print(n, "vertices", m//2, "edges")

   color = [-1 for i in range(n)]              # everyone is uncolored (-1)
   avail = []
   for i in range(n):
      avail.append({0,1,2,3})                  # all colors available for everyone

   for i in range(3):                          # color the first three vertices in color 0
      colorvertex(i,0)

   vmax = 0                                    # max depth of recursion -- something to watch while it runs
   dfs(3)
   print("No colorings found.")

