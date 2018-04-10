
from graph import Graph

n = 7

G = Graph(n)
G.addedge(3,5)
G.addedge(3,4)
G.addedge(3,6)

print(G.connected())

for i in range(1,n):
  G.addedge(0,i)

print(G.connected())

G.printmatrix()

