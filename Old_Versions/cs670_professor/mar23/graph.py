
class VertexException(Exception):
   pass

class Graph:
   """This is the documentation string."""
   def __init__(self, n):

      self.n = n
      self.alist = [[] for i in range(n)]
      self.elist = []
      self.matrix = [[0 for i in range(n)] for j in range(n)]

   def addedge(self, u, v):

      if u < 0 or u >= self.n:
         raise VertexException("vertex {0:d} is out of range".format(u))
         return
      if v < 0 or v >= self.n:
         raise VertexException("vertex {0:d} is out of range".format(v))
         return
      if u == v:
         raise VertexException("loops are not allowed")
         return
      if self.matrix[u][v] != 0:
         raise VertexException("edge {0:d}-{1:d} is already present".format(u,v))
         return
      self.elist.append([u,v])
      self.alist[u].append(v)
      self.alist[v].append(u)
      self.matrix[u][v] = 1
      self.matrix[v][u] = 1

   def printmatrix(self):
      for i in range(self.n):
         s = ""
         for j in range(self.n):
            s += "{0:2d}".format(self.matrix[i][j])
         print(s)
 
   def order(self):
      return self.n
 
   def size(self):
      return len(self.elist)

   def edgelist(self):
      return self.elist

   def connected(self):
      n = self.n
      vis = [False for i in range(n)]
      sca = [False for i in range(n)]
      vis[0] = True
      nscanned = 0
      while True:
         u = Graph.findVisitedNotScanned(vis,sca)
         if u == None:
            break
         sca[u] = True
         nscanned += 1
         for v in self.alist[u]:
            if not vis[v]:
               vis[v] = True
      return (n == nscanned)

   @classmethod
   def findVisitedNotScanned(cls, vis, sca):
      for i in range(len(vis)):
         if vis[i] and not sca[i]:
            return i
      return None

