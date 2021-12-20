#include <queue>
#include "../include/Tree.h"

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) { }

int MaxRankTree::traceTree() { //traceTree for MaxRankTree returns the node in the tree with the most children
    int maxChildrenInd = getNode();
    int signed maxChildrenCount = getChild(maxChildrenInd).getChildren().size();

    queue<int> indQ;
    indQ.push(getNode());

    while (!indQ.empty()){ //We go through the tree layer by layer
        int nodeId = indQ.front();
        indQ.pop();

        if((signed)getChild(nodeId).getChildren().size() > maxChildrenCount){ //Updating the max rank node
            maxChildrenInd = nodeId;
            maxChildrenCount = getChild(nodeId).getChildren().size();
        }

        for (Tree *i : getChild(nodeId).getChildren()) {
            indQ.push(i->getNode());
        }
    }

    return maxChildrenInd;
}

Tree *MaxRankTree::clone() const {
    MaxRankTree *newTree;
    newTree = new MaxRankTree(getNode());
    for (Tree *child : getChildren()) {
        newTree->addChild(*(child->clone()));
    }
    return newTree;
}