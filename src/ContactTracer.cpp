#include "../include/Agent.h"
#include "../include/Tree.h"

ContactTracer::ContactTracer() = default;

void ContactTracer::act(Session &session) {
    if(session.infectedAmount() == 0) return; //if no node is in the infected queue do nothing
    int nodeInd = session.dequeueInfected();
    Tree *tree = Tree::createTree(session, nodeInd);
    int nodeToRemove = tree->traceTree(); //find the correct node to remove, using the pure virtual function traceTree
    int node = 0;
    vector<int> edgesOfInfected = session.getGraph().getEdges()[nodeToRemove];
    for(int i : edgesOfInfected){
        if(i == 1){
            session.removeEdge(nodeToRemove, node); //calling session to delete every edge connected to node
        }
        node++;
    }
    delete tree;
}

Agent * ContactTracer::clone() const{
    ContactTracer *newTracer;
    newTracer = new ContactTracer();
    return newTracer;
}