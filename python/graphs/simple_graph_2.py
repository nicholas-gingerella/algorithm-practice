from collections import deque
from copy import deepcopy

#Graph - adj-list
#nodes
#edges
class Graph:
    'class documentation string'

    def __init__(self, g=None):
        if g is None:
            g = {}
        self._graphList = deepcopy(g)
        self._numNodes = len(self._graphList.keys())
    

    def getNumNodes(self):
        return self._numNodes
    

    def getNodes(self):
        return self._graphList.keys()


    def getEdges(self):
        edges = []
        for startNode, adjList in self._graphList.items():
            for endNode in adjList:
                edges.append((startNode, endNode))
        return edges
    

    def addEdge(self, start, end):
        if start in self._graphList and end in self._graphList:
            self._graphList[start].append(end)
            return True
        return False
    

    def addNode(self, label):
        if label not in self._graphList:
            self._graphList.setdefault(label, [])


    # Get path from start node to end node
    # returns list of nodes in traversal order
    def dfs(self, start, end):
        visited = []
        if start in self._graphList and end in self._graphList:
            self.dfs_imp(start, end, visited)
        return visited

    # Implementation details for dfs
    def dfs_imp(self, node, target, visited):
        if node not in visited:        
            visited.append(node)
        
        if node == target:
            return True
        
        for neighbor in self._graphList[node]:
            if neighbor not in visited:
                 found = self.dfs_imp(neighbor, target, visited)
                 if found:
                     return True

        visited.pop()
        return False


    def bfs_traverse(self, start):
        searchQueue = deque()
        visited = []
        if start in self._graphList:
            self.bfs_traverse_imp(start, visited, searchQueue)
        return visited


    def bfs_traverse_imp(self, node, visited, queue):
        visited.append(node)
        queue.append(node)
        while queue:
            currNode = queue.popleft()
            for neighbor in self._graphList[currNode]:
                if neighbor not in visited:
                    visited.append(neighbor)
                    queue.append(neighbor)            


    def print(self):
        print(self._graphList)

def main():
    print("hello from main()")
    print("Empty Graph:")
    g = Graph()
    g.print()

    print("non-empty graph:")
    dirG_2 = Graph({
    'a':['b', 'c'],
    'b':[],
    'c':['d'],
    'd':['e'],
    'e':['a', 'f'],
    'f':[]
    })
    
    dirG_2.addEdge('a', 'd')
    dirG_2.addNode('z')
    dirG_2.print()

    print("nodes:")
    for node in dirG_2.getNodes():
        print(node, end=' ')
    print()



    print("edges:")
    print(dirG_2.getEdges())

    # print(dirG_2.dfs('a', 'c'))
    # print(dirG_2.dfs('a', 'z'))
    # print(dirG_2.dfs('c', 'd'))
    # print(dirG_2.dfs('c', 'f'))
    print(dirG_2.bfs_traverse('c'))

if __name__ == "__main__":
    main()
