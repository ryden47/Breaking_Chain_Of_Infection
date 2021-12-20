#include <fstream>
#include <queue>
#include "../include/Session.h"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

Session::Session(const std::string &path) : g(), treeType(), agents(), infected(), virusAgentsNodes(), cycles(0) {
    ifstream file(path);
    json j;
    file >> j;
    auto& elem  = j["graph"];
    std::vector<std::vector<int>> matrix = elem;

    g = Graph(matrix);

    if(j["tree"] == "M") treeType = MaxRank;
    else if(j["tree"] == "C") treeType = Cycle;
    else treeType = Root;

    infected = queue<int>();
    virusAgentsNodes = vector<int>();

    for (auto& agentJson : j["agents"]){
        if(agentJson[0] == "V") {
            agents.push_back(new Virus(agentJson[1]));
            virusAgentsNodes.push_back(agentJson[1]);
        }
        else
            agents.push_back(new ContactTracer());
    }
}

Session::~Session(){
    for(Agent* agent : agents){
        delete agent;
    }
}

Session::Session(const Session &other) : g(other.g), treeType(other.treeType), agents(), infected(other.infected), virusAgentsNodes(other.virusAgentsNodes), cycles(other.cycles) {
    copyAgents(other.agents);
}

Session & Session::operator=(const Session &other) {
    if(&other != this) {
        infected = other.infected;
        virusAgentsNodes = other.virusAgentsNodes;
        g = Graph(other.g);
        treeType = other.treeType;
        cycles = other.cycles;

        for(Agent* agent : agents){
            delete agent;
        }
        copyAgents(other.agents);
    }
    return *this;
}

Session::Session(Session &&other) : g(other.g), treeType(other.treeType), agents(), infected(other.infected), virusAgentsNodes(other.virusAgentsNodes), cycles(other.cycles) {
    int counter = 0;
    for (Agent* agent : other.agents) {
        agents.push_back(agent);
        other.agents[counter] = nullptr;
        counter++;
    }
}

Session &Session::operator=(Session &&other) {
    if(this != &other){
        for (Agent* agent : agents) {
            delete agent;
        }
        treeType = other.treeType;
        g = other.g;
        infected = other.infected;
        virusAgentsNodes = other.virusAgentsNodes;
        cycles = other.cycles;

        int counter = 0;
        for (Agent* agent : other.agents) {
            agents.push_back(agent);
            other.agents[counter] = nullptr;
            counter++;
        }
    }
    return *this;
}

void Session::copyAgents(vector<Agent*> _agents) { //This function is used to copy the agents of other Session classes
    for (Agent* agent : _agents) {
        Agent* newAgent = agent->clone();
        agents.push_back(newAgent);
    }
}

TreeType Session::getTreeType() const {
    return treeType;
}

void Session::addAgent(const Agent &agent) {
    Agent * a = agent.clone();
    agents.push_back(a);
}

void Session::enqueueInfected(int infectedToAdd) {
    g.infectNode(infectedToAdd);
    infected.push(infectedToAdd);
}

int Session::dequeueInfected() {
    int ret = infected.front();
    infected.pop();
    return ret;
}

void Session::simulate() {
    int currAgents = 0;

    while (!g.VirusContained() | ((unsigned)agents.size() > (unsigned)currAgents)){ //While the virus isn't contained and there arent any agents in the vector that haven't acted yet
        currAgents = agents.size();
        for (int i = 0; i < currAgents; ++i) {
            Agent * agent = agents[i];
            agent->act(*this);
        }
        cycles++;
    }

    json j;
    j["graph"] = g.getEdges();
    j["infected"] = g.getInfectedNodes();
    ofstream file("./output.json");
    file << j;
}

Graph Session::getGraph() const {
    return g;
}

int Session::getCycles() const {
    return cycles;
}

void Session::removeEdge(int nodeToRemove, int node) {
   g.removeEdge(nodeToRemove, node);
}

int Session::infectedAmount() {
    return infected.size();
}

bool Session::isInInfectedQ(int vert) { //Sometimes we might need to know if a node is in the infected queue, so here we empty the queue into another to check for it, and then switch them
    queue<int> copy;
    bool isIn = false;
    while(!infected.empty()){
        int node = infected.front();
        infected.pop();
        if(node == vert)
            isIn = true;
        copy.push(node);
    }
    infected = copy;
    return isIn;
}

bool Session::isInViruses(int node) { //Sometimes we might need to check if a virus is in a node, so we save them in a vector and search for them here
    for (int i : virusAgentsNodes) {
        if(i == node)
            return true;
    }
    return false;
}

void Session::addVirusNode(int node) {
    virusAgentsNodes.push_back(node);
}



