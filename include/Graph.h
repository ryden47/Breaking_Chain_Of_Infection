#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>

using namespace std;

class Graph{
public:
    Graph();
    Graph(vector<vector<int>> matrix);

    void infectNode(int nodeInd);
    bool isInfected(int nodeInd);
    bool VirusContained();

    vector<vector<int>> getEdges() const;
    vector<int> getInfectedNodes() const;
    void removeEdge(int, int);
private:
    vector<vector<int>> edges;
    vector<int> infectedNodes;

    vector<int> DFS(int v, bool visited[], vector<int> compo);
};

#endif