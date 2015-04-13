#!/usr/bin/python

import networkx as nx

g=nx.read_adjlist("g", create_using=nx.DiGraph())
C=nx.condensation(g)
print C

nx.write_adjlist(C, "wssmall")
