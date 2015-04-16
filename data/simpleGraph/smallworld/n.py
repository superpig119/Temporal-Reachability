#!/usr/bin/python

import networkx as nx
import random

import sys

r=random

#G=nx.star_graph(30)
#nx.write_adjlist(G, "./star")
G=nx.watts_strogatz_graph(int(sys.argv[1]), int(sys.argv[2]), float(sys.argv[3]))
#D=nx.convert.convert_to_directed(G)
"""edges=G.edges()
for edge in edges:
    ran=r.randint(0,1)   
    (u,v)=edge
    if ran==0:
        D.remove_edge(u,v)
    else:
        D.remove_edge(v,u)"""
nx.write_adjlist(G, "tmp")
g=nx.read_adjlist("tmp", create_using=nx.DiGraph())
C=nx.condensation(g)

nx.write_adjlist(C, "wssmall")

#G=nx.powerlaw_cluster_graph(100000,200,0.3)
#nx.write_adjlist(G, "powerlowc")


