#!/usr/bin/python

import networkx as nx

#G=nx.star_graph(30)
#nx.write_adjlist(G, "./star")

G=nx.watts_strogatz_graph(10000,20, 0.3)
nx.write_adjlist(G, "tmp")
g=nx.read_adjlist("tmp", create_using=nx.DiGraph())
#C=nx.strongly_connected_components(G)
C=nx.condensation(g)
print C

nx.write_adjlist(C, "wssmall")

#G=nx.powerlaw_cluster_graph(100000,200,0.3)
#nx.write_adjlist(G, "powerlowc")


