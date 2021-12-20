#include "../include/Tree.h"

RootTree::RootTree(int rootLabel) : Tree(rootLabel) { }

int RootTree::traceTree() { //traceTree for RootTree just returns the root
    return getNode();
}

Tree *RootTree::clone() const {
    RootTree *newTree;
    newTree = new RootTree(getNode());
    for (Tree *child : getChildren()) {
        newTree->addChild(*(child->clone()));
    }
    return newTree;
}
