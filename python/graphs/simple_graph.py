# File: simple_graph.py
# Author: Nick Gingerella
# Description:
# Simple implementation of a graph data structure and various graph algorithms
from collections import deque

# adjacency list
graph = {
    'A': ['B', 'C'], # node A connects to nodes B and C
    'B': ['D', 'E'], # node B connects to nodes D and E
    'C': ['B'],
    'D': ['E']
}

def find_path(graph, start, end, path=[]):
    path = path + [start] # creates a new list with start node to path
    if start == end:
        return path # start and end refer to the same node
    if start not in graph:
        return None # the start node does not exist on the graph
    
    for node in graph[start]:
        if node not in path:
            newpath  = find_path(graph, node, end, path)
            if newpath:
                return newpath
    return None


def find_all_paths(graph, start, end, path=[]):
    path = path + [start] # creates a new list with start node to path
    if start == end:
        return [path] # start and end refer to the same node
    if start not in graph:
        return []
    paths = []
    for node in graph[start]:
        if node not in path:
            newpaths  = find_all_paths(graph, node, end, path)
            for newpath in newpaths:
                paths.append(newpath)
    return paths

""" Python Class
A simple Python graph class, demonstrating the essential
facts and functionalities of graphs
"""

class Graph():
    def __init__(self, graph_dict=None):
        """ init graph object
            If no dictionary or None is given,
            an empty dictionary will be used
        """
        if graph_dict == None:
            graph_dict = {}
        self.__graph_dict = graph_dict

    
    def vertices(self):
        """ returns the vertices of the graph """
        return list(self.__graph_dict.keys())
    
    def edges(self):
        """ returns the edges of the graph """
        return list(self.__generate_edges())
    
    def add_vertex(self, vertex):
        """ If the vertex "vertex" is not in
            self.__graph_dict, a key "vertex" with an empty
            list as a value is added to the dictionary.
            Otherwise nothing has to be done
        """
        if vertex not in self.__graph_dict:
            self.__graph_dict[vertex] = []
    
    def add_edge(self, edge):
        """ assumes that edge is a type set, tuple or list;
            between two vertices can be multiple edges.
        """
        edge = set(edge)
        (vertex1, vertex2) = tuple(edge)
        if vertex1 in self.__graph_dict:
            self.__graph_dict[vertex1].append(vertex2)
        else:
            self.__graph_dict[vertex1] = [vertex2]

    def get_adj_nodes(self, node):
        return self.__graph_dict[node]

    def __generate_edges(self):
        """ A static method for generating the edges of the
            graph "graph". Edges are represented as sets with
            one (a loop back to the vertex) or two vertices
        """
        edges = []
        for vertex in self.__graph_dict:
            for neighbor in self.__graph_dict[vertex]:
                if (neighbor, vertex) not in edges:
                    edges.append((vertex, neighbor))
        return edges

    def __str__(self):
        res = "vertices: "
        for k in self.__graph_dict:
            res += str(k) + " "
        res += "\nedges: "
        for edge in self.__generate_edges():
            res += str(edge) + " "
        return res

if __name__ == "__main__":
    g = {
        'a':['b','c','d'],
        'b':['a','e'],
        'c':['a','f'],
        'd':['g','a'],
        'e':['b','f'],
        'f':['c','g'],
        'g':['d','f']
    }
    graph = Graph(g)
    print("graph:")
    print(graph)
