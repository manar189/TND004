/*********************************************
*   MEMEBERS:                                *
*       Måns Aronsson, manar189              *
*       Nisse Bergman, nisbe033              *
*                                            *
* file:	~\tnd004\lab\lab4b\graph.h           *
* remark:implementation of undirected graphs *
**********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>  //assert
#include <limits>   //std::numeric_limits

// using namespace std;

#include "graph.h"
#include "edge.h"
#include "heap.h"
#include "dsets.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

// Create an empty graph with n vertices
Graph::Graph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
}

Graph::Graph(const std::vector<std::tuple<int, int, int>> &V, int n) : Graph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert undirected edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Graph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);
    table[v].insert(u, w);

    n_edges += 2;
}

// remove undirected edge (u, v)
void Graph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);
    table[v].remove(u);

    n_edges -= 2;
}

// Prim's minimum spanning tree algorithm
void Graph::mstPrim() const {

    std::vector<int> dist;
    std::vector<int> path;
    std::vector<int> done;

    dist.resize(size + 1);
    path.resize(size + 1);
    done.resize(size + 1);


    // Init with infinite dist, path 0
    
    dist[0] = std::numeric_limits<int>::max();
    for (int i = 1; i <= size; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        path[i] = 0;
        done[i] = false;
    }

    

    // Start vertex
    int totWeight = 0;
    int v = 1;
    dist[v] = 0;
    done[v] = true;

    while (true)
    {
        Node* u = table[v].getFirst();

        while (u != nullptr)
        {
            if (done[u->vertex] == false && dist[u->vertex] > u->weight)
            {
                dist[u->vertex] = u->weight;
                path[u->vertex] = v;
            }
            
            //u = table[u->vertex].getNext();
            u = table[v].getNext();
		}

        v = 0;
        for (int i = 1; i <= size; i++) {

            if (!done[i] && dist[i] < dist[v]) {
                v = i;
            }
        }

        if (v == 0) break;
        done[v] = true;
        totWeight += dist[v];

        // Output
        std::cout << "( " << path[v] << ", " << v << ", " << dist[v] << " )" << std::endl;
    }

    std::cout << "\nTotal Weight =  " << totWeight << std::endl;
}

// Kruskal's minimum spanning tree algorithm
void Graph::mstKruskal() const {

    Heap<Edge> H(size);
    DSets D(size);

    // Build heap with all the edges
    for (int v = 1; v <= size; v++) {
        Node* u = table[v].getFirst();

        while(u != nullptr) {

            // IF-statement to get equal output as testfile.
            if(u->vertex < v) H.insert(Edge(u->vertex, v, u->weight));

            u = table[v].getNext();
		}
	}

    int counter = 0, totWeight = 0;

    while (counter < size - 1)
    {
        Edge e = H.deleteMin();

        if (D.find(e.head) != D.find(e.tail))
        {
            totWeight += e.weight;
            std::cout << e << std::endl;
            D.join(D.find(e.head), D.find(e.tail));
            ++counter;
        }
    }

    std::cout << "\nTotal Weight = " << totWeight << std::endl;
}

// print graph
void Graph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                                            \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}


