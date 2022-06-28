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

public:
    BST();

    bool isEmpt();
    void insert(int num);
    void sort();
    bool search(int num);
    node *getParent(int num, int degree = 1);
    node *getNode(int num);
    void updadeHeightBalance();
    node *getRoot();
    int balanceTree(node *aux);
    node *getUnbalanced(node *aux);
    void rightSpin(node *aux, bool isDouble = false);
    void leftSpin(node *aux, bool isDouble = false);
};