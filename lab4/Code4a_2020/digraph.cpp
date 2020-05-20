/*********************************************
*   MEMEBERS:                                *
*       Måns Aronsson, manar189              *
*       Nisse Bergman, nisbe033              *
*                                            *
* file:	~\tnd004\lab\lab4a\digraph.cpp       *
* remark: implementation of directed graphs  *
**********************************************/

#include <iostream>
#include <iomanip>
#include <cassert>

// using namespace std;

#include "digraph.h"
#include "queue.h"

// Note: graph vertices are numbered from 1 -- i.e. there is no vertex zero

// -- CONSTRUCTORS

Digraph::Digraph(int n) : size{n}, n_edges{0} {
    assert(n >= 1);

    table.resize(size + 1);
    dist.resize(size + 1);
    path.resize(size + 1);
    done.resize(size + 1);
}

// Create a digraph with n vertices and the edges in V
Digraph::Digraph(const std::vector<std::tuple<int, int, int>> &V, int n) : Digraph{n} {
    for (auto [u, v, w] : V)  // C++17
    {
        insertEdge(u, v, w);
    }
}

// -- MEMBER FUNCTIONS

// insert directed edge (u, v) with weight w
// update weight w if edge (u, v) is present
void Digraph::insertEdge(int u, int v, int w) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].insert(v, w);

    n_edges += 1;
}

// remove directed edge (u, v)
void Digraph::removeEdge(int u, int v) {
    assert(u >= 1 && u <= size);
    assert(v >= 1 && v <= size);
    table[u].remove(v);

    n_edges -= 1;
}

// unweighted single source shortest paths
void Digraph::uwsssp(int s) const {
    if (s < 1 || s > size) {
        std::cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }


    Queue<int> Q;

    // Init with infinite dist, path 0
    for (int i = 1; i <= size; i++) 
    {
        dist[i] = std::numeric_limits<int>::max();
        path[i] = 0;
	}

    dist[s] = 0;

    Q.enqueue(s);

    while (!Q.isEmpty())
    {
        int v = Q.getFront();
        Q.dequeue();

        Node* p = table[v].getFirst();
        while (p != nullptr)
        {

            if (dist[p->vertex] == std::numeric_limits<int>::max())
            {
                dist[p->vertex] = dist[v] + 1;
                path[p->vertex] = v;
                Q.enqueue(p->vertex);
            }
            
            p = table[v].getNext();
            
        }
    }
}

// positive weighted single source shortest paths
// Dijktra’s algorithm
void Digraph::pwsssp(int s) const {
    if (s < 1 || s > size) {
        cout << "\nERROR: expected source s in range 1.." << size << " !\n";
        return;
    }

    // Init with infinite dist, path 0
    for (int i = 1; i <= size; i++)
    {
        dist[i] = std::numeric_limits<int>::max();
        path[i] = 0;
        done[i] = false;
    }

    dist[s] = 0;
    done[s] = true;
    int v = s;

    while (true)
    {
        Node* u = table[v].getFirst();

        while (u != nullptr)
        {
            if (done[u->vertex] == false && dist[u->vertex] > dist[v] + u->weight)
            {
                dist[u->vertex] = dist[v] + u->weight;
                path[u->vertex] = v;
            }
            
            //u = table[u->vertex].getNext();
            u = table[v].getNext();
		}

        v = find_smallest_undone_distance_vertex();
        if (v == 0) break;
        done[v] = true;
    }
}

// print graph
void Digraph::printGraph() const {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "vertex  adjacency list                  \n";
    std::cout << "------------------------------------------------------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << setw(4) << v << " : ";
        table[v].print();
    }

    std::cout << "------------------------------------------------------------------\n";
}

// print shortest path tree for s
void Digraph::printTree() const {
    std::cout << "----------------------\n";
    std::cout << "vertex    dist    path\n";
    std::cout << "----------------------\n";

    for (int v = 1; v <= size; v++) {
        std::cout << std::setw(4) << v << " :" << std::setw(8)
                  << ((dist[v] == std::numeric_limits<int>::max()) ? -1 : dist[v]) << std::setw(8)
                  << path[v] << "\n";
    }

    std::cout << "----------------------\n";
}

// print shortest path from s to t
void Digraph::printPath(int t) const {
    if (t < 1 || t > size) {
        std::cout << "\nERROR: expected target t in range 1.." << size << " !\n";
        return;
    }

    printRecursive(t);
    cout << " (" << (dist[t]) << ")";
}

void Digraph::printRecursive(int t) const {
    

    if (path[t] == 0)
    {
        std::cout << " " << t;
        return;
    }

    printRecursive(path[t]);
    std::cout << " " << t;
}

int Digraph::find_smallest_undone_distance_vertex() const {

    int v = 0;
    dist[v] = std::numeric_limits<int>::max();

    for (int i = 1; i <= size; i++) {
        
        if (!done[i] && dist[i] < dist[v]) {
            v = i;
        }
    }
    return v;
}

