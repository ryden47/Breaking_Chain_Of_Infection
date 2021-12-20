#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;
using namespace std;

class Tree{
public:
    Tree();
    Tree(int rootLabel);
    virtual ~Tree();
    Tree(const Tree &other);
    Tree& operator=(const Tree &other);
    Tree(Tree&& other);
    Tree& operator=(Tree&& other);

    void addChild(const Tree& child);
    virtual Tree * clone() const = 0;

    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree() = 0;

    int getNode() const;
    Tree& getChild(int ind) const;
    const vector<Tree*>& getChildren() const;

private:
    int node;
    std::vector<Tree*> children;

    void clear();
    void copyChildren(vector<Tree*> _children);
    void BFS(const Session& session, int root, bool *visited);
};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();
    virtual Tree* clone() const;
private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();
    virtual Tree* clone() const;
};

#endif