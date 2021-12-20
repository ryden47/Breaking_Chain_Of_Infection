#include <algorithm>
#include <utility>
#include "../include/Graph.h"

using namespace std;

Graph::Graph() : edges(), infectedNodes(){

}

Graph::Graph(vector<vector<int>> matrix) : edges(std::move(matrix)), infectedNodes() {
}

bool Graph::isInfected(int nodeInd) { //This function returns whether a node is infected
    for (int node : infectedNodes) {
        if(node == nodeInd)
            return true;
    }
    return false;
}

void Graph::infectNode(int nodeInd) { //This function adds a new node to the infected vector, if it isn't there already
    if(count(infectedNodes.begin(), infectedNodes.end(), nodeInd) == 0)
        infectedNodes.push_back(nodeInd);
}

bool Graph::VirusContained() { //This function checks if the virus in the graph has been contained, which means that in every connected component C, every node in C is either infected or not
    int vertices = edges.size();
    bool contained = true;

    bool* visited = new bool[vertices]; //making a visited array
    for (int v = 0; v < vertices; v++)
        visited[v] = false;

    vector<int> compo;
    for (int v = 0; (v < vertices) & contained; v++) {  //we find the connected component for every node in the graph
        if (!visited[v]) {
            compo = DFS(v, visited, compo);
            int signed infectedCounter = 0;
            int signed notInfectedCounter = 0;
            for(int node : compo) {
                if(isInfected(node)) infectedCounter++;
                else notInfectedCounter++;
            }
            if(notInfectedCounter != (signed)compo.size() && infectedCounter != (signed)compo.size()) contained = false; //checking if every node is either infected or not
            compo = vector<int>();
        }
    }
    delete[] visited;
    return contained;
}

vector<int> Graph::DFS(int v, bool *visited, vector<int> compo) { //A DFS function
    visited[v] = true;
    compo.push_back(v);

    int vert = 0;
    for (int i : edges[v]) {
        if (i == 1 && !visited[vert])
            compo = DFS(vert, visited, compo);
        vert++;
    }

    return compo;
}

vector<vector<int>> Graph::getEdges() const {
    return edges;
}

vector<int> Graph::getInfectedNodes() const {
    return infectedNodes;
}

void Graph::removeEdge(int nodeToRemove, int node) {
    edges[nodeToRemove][node] = 0;
    edges[node][nodeToRemove] = 0;
}


