
from graph import Graph

n = 6

G = Graph(n)
G.addedge(1,2)
G.addedge(2,3)
G.addedge(3,4)
G.addedge(4,5)

print(G.connected())

for i in range(1,n):
  G.addedge(0,i)

print(G.connected())

G.printmatrix()

c = G.threecolor()

print(c)
