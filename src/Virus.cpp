
#include "../include/Agent.h"

Virus::Virus(int nodeInd) : nodeInd(nodeInd) { }

void Virus::act(Session &session) {
    if (!session.getGraph().isInfected(nodeInd))
        session.enqueueInfected(nodeInd);
    int vert = 0;

    vector<int> edgesOfInfected = session.getGraph().getEdges()[nodeInd];
    for (int node : edgesOfInfected) { //We go through every node this node is connected to
        if(node == 1){
            if(!session.getGraph().isInfected(vert) & !session.isInInfectedQ(vert) & !session.isInViruses(vert)){ //We check if it hasn't been infected yet and then we spread to it
                Agent * newVirus = new Virus(vert);
                session.addAgent(*newVirus);
                session.addVirusNode(vert);
                delete newVirus;
                break;
            }
        }
        vert++;
    }
}

Agent * Virus::clone() const{
    Virus *newVirus;
    newVirus = new Virus(nodeInd);
    return newVirus;
}

