#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <queue>
#include <vector>
using namespace std;


template<typename Type>
class Graph;

template<typename Type>
ostream &operator <<(ostream &out, const Graph<Type> &g);

template<typename Type>
class Graph {
public:
    Graph();

    void addVertex(Type vertex);

    void addEdge(Type, Type);

    int getVertexPos(Type item);

    int getNumVertices() const;

    bool isEdge(Type, Type);

    friend ostream &operator <<<>(ostream &out, const Graph<Type> &g);

    vector<Type> getPath(Type, Type);

private:
    vector<Type> verticies;
    vector<vector<Type> > edges;
};


/*********************************************
* Constructs an empty graph
*********************************************/
template<typename Type>
Graph<Type>::Graph() {
}

/*********************************************
* Adds a Vertex to the Graphs. Note that the vertex may not be an int value
*********************************************/
template<typename Type>
void Graph<Type>::addVertex(Type vertex) {
    verticies.push_back(vertex);
    vector<Type> lst;
    edges.push_back(lst);
}

/*********************************************
* Returns the current number of vertices
*********************************************/
template<typename Type>
int Graph<Type>::getNumVertices() const {
    return verticies.size();
}


/*********************************************
* Returns the position in the vertices list where the given vertex is located, -1 if not found.
*********************************************/
template<typename Type>
int Graph<Type>::getVertexPos(Type item) {
    for (unsigned int i = 0; i < verticies.size(); i++) {
        if (item == verticies[i]) {
            return i;
        }
    }

    return -1;
}

/*********************************************
* Adds an edge going in the direction of source going to target
*********************************************/
template<typename Type>
void Graph<Type>::addEdge(Type source, Type target) {
    int srcPos = getVertexPos(source);
    if (srcPos < 0) {
        throw runtime_error("Vertex no existy");
    }
    edges[srcPos].push_back(target);
}

template<typename Type>
bool Graph<Type>::isEdge(Type source, Type dest) {
    int srcPos = getVertexPos(source);
    if (srcPos < 0) {
        throw runtime_error("Vertex no existy");
    }

    for (unsigned int i = 0; i < edges[i].size(); i++) {
        if (edges[srcPos][i] == dest) {
            return true;
        }
    }

    return false;
}


/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
* Note: This is not a traversal, just output
*********************************************/
template<typename Type>
ostream &operator <<(ostream &out, const Graph<Type> &g) {
    for (unsigned int i = 0; i < g.verticies.size(); i++) {
        out << g.verticies[i] << ": ";
        for (unsigned int e = 0; e < g.edges[i].size(); e++) {
            out << g.edges[i][e] << " ";
        }
        out << endl;
    }
    return out;
}

/*
  getPath will return the shortest path from source to dest.
  You are welcome to use any solution not limited to the following, depth first search to traverse
  graph to find the solution, breadth first, shortest path first, or any
  other graph algorithm.

  You will return a vector with the solution from the source to the destination.
  IE: The source will be in position 1 the destination is in the last position of the solution, and each node in between
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.
*/

template<typename Type>
vector<Type> Graph<Type>::getPath(Type source, Type dest) {
    stack<Type> unvisited; // Using a breadth first traversal
    vector<bool> visited(getNumVertices(), false); // Tracks index of what's been visited
    vector<Type> parents(getNumVertices());
    vector<Type> solution;
    Type curr;

    // Traversal //
    unvisited.push(source);

    while (!unvisited.empty()) {
        curr = unvisited.top();
        unvisited.pop();

        if (curr == dest) { // Destination node check
            break;
        }

        if (visited[getVertexPos(curr)] == true) {
            continue; // Breaks out of current iteration to the next one
        }

        visited[getVertexPos(curr)] = true; // Mark current node as visited

        for (int i=0; i<edges[getVertexPos(curr)].size(); i++) { // Iterates through the children
            Type currChild = edges[getVertexPos(curr)][i]; // i

            // child visited check
            if (visited[getVertexPos(currChild)] == false) { // if child is not visited
                unvisited.push(currChild);
                parents[getVertexPos(currChild)] = curr;
            }
        }
    }

    // Adds the path to solution
    curr = dest;
    while (curr != source) {
        solution.push_back(curr);
        curr = parents[getVertexPos(curr)];
    }
    solution.push_back(source);
    // Reverse solution list
    reverse(solution.begin(), solution.end());
    return solution;
}
