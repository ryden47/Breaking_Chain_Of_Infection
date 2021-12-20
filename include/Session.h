#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include <queue>
#include "Graph.h"
#include "Agent.h"

class Agent;

using namespace std;

enum TreeType{
    Cycle,
    MaxRank,
    Root
};

class Session{
public:
    Session(const std::string& path);
    ~Session();
    Session(const Session &other);
    Session& operator=(const Session &other);
    Session(Session&& other);
    Session& operator=(Session&& other);

    void simulate();
    void addAgent(const Agent& agent);

    void enqueueInfected(int);
    int dequeueInfected();
    TreeType getTreeType() const;
    Graph getGraph() const;
    int getCycles() const;
    void removeEdge(int, int);
    int infectedAmount();
    bool isInInfectedQ(int);
    bool isInViruses(int);
    void addVirusNode(int);

private:
    void copyAgents(vector<Agent*> _agents);

    Graph g;
    TreeType treeType;
    vector<Agent*> agents;
    queue<int> infected;
    vector<int> virusAgentsNodes;
    int cycles;
};

#endif