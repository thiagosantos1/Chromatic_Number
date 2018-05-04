
def chronum(filename):
  fd = open(filename,"r")
  li = fd.readlines()
  fd.close()
  edges = []
  for l in li:
    pi = l.split()
    edges.append((int(pi[0]),int(pi[1])))
  G = Graph(edges)
  print("order: ",G.order())
  print("size: ",G.size())
  print("girth: ",G.girth())
  print("diameter: ",G.diameter())
  print("chro num: ",G.chromatic_number())

