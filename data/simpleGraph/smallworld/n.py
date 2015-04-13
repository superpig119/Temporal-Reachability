#!/usr/bin/python

import networkx as nx

#G=nx.star_graph(30)
#nx.write_adjlist(G, "./star")

G=nx.watts_strogatz_graph(10000,20, 0.3)
#nx.write_adjlist(G, "wssmall")

#G=nx.powerlaw_cluster_graph(100000,200,0.3)
nx.write_adjlist(G, "powerlowc")


