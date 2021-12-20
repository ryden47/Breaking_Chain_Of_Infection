#include "../include/Tree.h"

CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {
}

int CycleTree::traceTree() {
    Tree *currTree = &getChild(getNode());
    for (int i = 0; !currTree->getChildren().empty() & (i < currCycle); ++i) { //traceTree for CycleTree gets the left most node cycles times (or less if there isn't anymore) and returns it
        currTree = currTree->getChildren()[0]; //the leftmost node is always at index 0
    }
    int remove = currTree->getNode();
    return remove;
}

Tree *CycleTree::clone() const {
    CycleTree *newTree;
    newTree = new CycleTree(getNode(), currCycle);
    for (Tree *child : getChildren()) {
        newTree->addChild(*(child->clone()));
    }
    return newTree;
}
