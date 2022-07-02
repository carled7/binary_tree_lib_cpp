#include <iostream>
using namespace std;

struct node;

class BST
{
private:
    node *root;

    int getUnbalanced(int *num, node *aux);
    node *getNode(int num, node *aux, node *buffer);
    void updadeHeightBalance(node *aux);
    void sort(node *aux);
    int getDepth(int num);
    void print(node *aux, int depth, int *buffer);

public:
    BST();
    bool isEmpt();
    void insert(int num);
    void sort();
    bool search(int num);
    bool isLeaf(node *aux);
    node *getParent(int num, int degree = 1);
    node *getNode(int num);
    void updadeHeightBalance();
    node *getRoot();
    void print();
    int balanceTree(node *aux);
    node *getUnbalanced();
    void rightSpin(node *aux, bool isDouble = false);
    void leftSpin(node *aux, bool isDouble = false);
    void test(BST tree);
};