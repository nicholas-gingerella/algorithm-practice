// File: simple_graph.cpp
// Author: Nick Gingerella
// Description:
// Implementation of a basic graph data structure and various graph algorithms
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>

// A graph is
// a set of nodes/vertices
// a set of edges (pairs of vertices)

class Graph
{
    private:

    protected:
        // a vertext in the graph contains:
        // a label: name to identify vertex
        // a degree: number of edges connected to vertex
        using vertex =  struct vertex
        {
            std::string label;
            int degree;
        };

        struct VertexCompare
        {
            bool operator() (const vertex& lhs, const vertex& rhs)
            {
                return lhs.label < rhs.label;
            }
        };
        
        // map where keys are vertices, and values are lists
        // of edges from the vertex (adjacency list).
        std::map<vertex, std::vector<vertex>, VertexCompare> m_adjacencyList;

        // type aliases
        using adjacencyListItr = std::map<vertex, std::vector<vertex>>::iterator;
        using edge = std::pair<vertex,vertex>;
        using edgeListItr = std::vector<edge>;

    public:

        Graph()
        {
            std::cout << "Graph Constructor" << std::endl;
        }

        ~Graph()
        {
            std::cout << "Graph Destructor" << std::endl;
        }

        // get vertices
        std::vector<vertex> get_vertices()
        {
            std::vector<vertex> retval;
            for (auto const& entry: m_adjacencyList) {
                retval.push_back(entry.first);
            }
            return retval;
        }

        // get edges
        std::vector<edge> get_edges()
        {
            std::vector<edge> retval;
            for (auto vertex_entry: m_adjacencyList)
            {
                std::cout << vertex_entry.first.label << std::endl;
                for(auto adjacent_vertex: vertex_entry.second)
                {
                    edge e = std::make_pair(vertex_entry.first, adjacent_vertex);
                    retval.push_back(e);
                }
            }

            return retval;
        }

        // add vertex
        bool add_vertex(std::string label)
        {
            int oldSize = m_adjacencyList.size();
            std::vector<vertex> e;
            vertex v = {label, 0};
            m_adjacencyList.insert({v,e});
            int newSize = m_adjacencyList.size();

            // if the size of the list increased, then the vertex
            // was added successfully
            if (oldSize < newSize)
            {
                return true;
            }

            return false;
        }

        // remove vertex*


        // add edge
        virtual bool add_edge(std::string label1, std::string label2)
        {
            
            adjacencyListItr itr_v1 = m_adjacencyList.find({label1});
            adjacencyListItr itr_v2 = m_adjacencyList.find({label2});
            if (itr_v1 != m_adjacencyList.end() && itr_v2 != m_adjacencyList.end())
            {
                // Both vertices exist in graph, this is a valid edge

                // first vertex in edge is a valid node, add edge to 
                // this node's list
                m_adjacencyList[{label1}].push_back({label2});
                m_adjacencyList[{label2}].push_back({label1});
            }

            return true;
        }


        // remove edge*
};

class DirectedGraph: public Graph
{
    private:

        // // type aliases
        // using adjacencyListItr = std::map<vertex, std::vector<vertex>>::iterator;
        // using edge = std::pair<vertex,vertex>;
        // using edgeListItr = std::vector<edge>;

    public:
    DirectedGraph()
    {
        std::cout << "Directed Graph Constructor" << std::endl;
    }
    
    ~DirectedGraph()
    {
        std::cout << "Directed Graph Destructor" << std::endl;
    }

    bool add_edge(std::string fromLabel, std::string toLabel) override
    {
        adjacencyListItr itr_v1 = m_adjacencyList.find({fromLabel});
        adjacencyListItr itr_v2 = m_adjacencyList.find({toLabel});
        if (itr_v1 != m_adjacencyList.end() && itr_v2 != m_adjacencyList.end())
        {
            // add edge from first node to secondn node (directed)
            m_adjacencyList[{fromLabel}].push_back({toLabel});
        }
        else
        {
            return false;
        }
        

        return true;
    }

};

int main (int argc, char** argv)
{
    Graph test_graph;
    std::cout << "test_graph instantiated" << std::endl;
    test_graph.add_vertex("A");
    test_graph.add_vertex("B");
    test_graph.add_vertex("C");
    test_graph.add_vertex("D");
    for (auto const& v : test_graph.get_vertices())
    {
        std::cout << v.label << "," << v.degree << std::endl;
    }

    test_graph.add_edge("A","B");
    test_graph.add_edge("B","C");
    test_graph.add_edge("B","D");

    std::cout << "Edges" << std::endl;
    for (auto const& e: test_graph.get_edges())
    {
        std::cout << e.first.label << e.second.label << std::endl;
    }



    DirectedGraph test_graph2;
    std::cout << "test_graph2 instantiated" << std::endl;
    test_graph2.add_vertex("A");
    test_graph2.add_vertex("B");
    test_graph2.add_vertex("C");
    test_graph2.add_vertex("D");
    for (auto const& v : test_graph2.get_vertices())
    {
        std::cout << v.label << "," << v.degree << std::endl;
    }

    test_graph2.add_edge("A","B");
    test_graph2.add_edge("B","C");
    test_graph2.add_edge("B","D");

    std::cout << "Edges" << std::endl;
    for (auto const& e: test_graph2.get_edges())
    {
        std::cout << e.first.label << e.second.label << std::endl;
    }

    return 0;
}