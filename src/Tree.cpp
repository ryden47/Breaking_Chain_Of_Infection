#include <algorithm>
#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;

Tree::Tree() : node(0), children() {
}

Tree::Tree(int rootLabel) : node(rootLabel), children() {
}

Tree::~Tree() {
    clear();
    for (Tree *child : children) {
        delete child;
    }
    children.clear();
}

void Tree::clear() {
    for (unsigned int i = 0; i < children.size(); ++i) {
        if(children[i] != nullptr){
            delete children[i];
            children[i] = nullptr;
        }
    }
    children.clear();
}

Tree::Tree(const Tree &other) : node(other.node), children(){
    clear();
    copyChildren(other.children);
}

void Tree::copyChildren(vector<Tree *> _children) {
    for (Tree *child : _children) {
        addChild(*child);
        copyChildren(child->children);
    }
    sort(children.begin(), children.end());
}

Tree &Tree::operator=(const Tree &other) {
    if(&other != this) {
        node = other.node;

        clear();
        copyChildren(other.children);
    }
    return *this;
}

Tree::Tree(Tree &&other) : node(other.node), children() {
    clear();
    copyChildren(other.children);

    other.node = 0;
    other.clear();
}

Tree &Tree::operator=(Tree &&other) {
    if(this != &other){
        clear();
        node = other.node;
        copyChildren(other.children);

        other.node = 0;
        other.clear();
    }
    return *this;
}

int Tree::getNode() const {
    return node;
}

void Tree::addChild(const Tree &child) {
    Tree * t = child.clone();
    children.push_back(t);
}

Tree *Tree::createTree(const Session &session, int rootLabel) { //createTree uses a BFS algorithm to find a tree in the graph
    int vertices = session.getGraph().getEdges().size();
    bool* visited = new bool[vertices];
    for (int v = 0; v < vertices; v++)
        visited[v] = false;

    if(session.getTreeType() == Root){
        RootTree* tree = new RootTree(rootLabel);
        tree->BFS(session, rootLabel, visited);
        delete[] visited;
        return tree;
    }
    else if (session.getTreeType() == MaxRank){
        MaxRankTree* tree = new MaxRankTree(rootLabel);
        tree->BFS(session, rootLabel, visited);
        delete[] visited;
        return tree;
    }
    else{
        CycleTree* tree = new CycleTree(rootLabel, session.getCycles());
        tree->BFS(session, rootLabel, visited);
        delete[] visited;
        return tree;
    }
}

void Tree::BFS(const Session &session, int root, bool *visited) {
    visited[root] = true;
    bool firstItr = true;

    queue<int> bfsQ;
    bfsQ.push(root);

    while(!bfsQ.empty()){
        root = bfsQ.front();
        bfsQ.pop();

        Tree *tree = this;

        if(!firstItr)
            tree = &getChild(root);

        firstItr = false;


        int nodeId = 0;
        vector<int> edgesOfRoot = session.getGraph().getEdges()[root];
        for (int i : edgesOfRoot) {
             if(!visited[nodeId] && i == 1){
                visited[nodeId] = true;
                if(session.getTreeType() == Root) {
                    RootTree *t = new RootTree(nodeId);
                    tree->addChild(*t);
                    delete t;
                }
                else if (session.getTreeType() == MaxRank) {
                    MaxRankTree *t = new MaxRankTree(nodeId);
                    tree->addChild(*t);
                    delete t;
                }
                else {
                    CycleTree *t = new CycleTree(nodeId, session.getCycles());
                    tree->addChild(*t);
                    delete t;
                }
                bfsQ.push(nodeId);
             }
             nodeId++;
        }
    }
}

Tree &Tree::getChild(int ind) const { //This function returns the a subtree with the index ind in the Tree
    if(getNode() == ind) return const_cast<Tree &>(*this);
    for (Tree* tree : children) {
        if (tree->node == ind)
            return *tree;
        else {
            if (tree->children.size() > 0) {
                Tree *toReturn = &(tree->getChild(ind));
                if (toReturn->getNode() == ind) {
                    if (toReturn->children.size() == 0)
                        return *toReturn;
                    if (toReturn->children.size() > 0 && toReturn->children.size() < INT32_MAX)
                        return *toReturn;
                }
            }
        }
    }
    return const_cast<Tree &>(*this);
}

const vector<Tree *> & Tree::getChildren() const {
    return children;
}