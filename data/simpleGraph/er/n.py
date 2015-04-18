#!/usr/bin/python

import networkx as nx
import random

import sys

r=random

G=nx.erdos_renyi_graph(int(sys.argv[1]), float(sys.argv[2]), int(sys.argv[3]), True)
#nx.write_adjlist(G, "tmp")
edges=G.edges()
for edge in edges:
    ran=r.randint(0,1)   
    (u,v)=edge
    if ran==0:
        G.remove_edge(u,v)
    else:
        G.remove_edge(v,u)
#g=nx.read_adjlist("tmp", create_using=nx.DiGraph())
C=nx.condensation(G)

nx.write_adjlist(C, "erg")

#G=nx.powerlaw_cluster_graph(100000,200,0.3)
#nx.write_adjlist(G, "powerlowc")


