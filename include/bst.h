#include <iostream>
using namespace std;

struct node;

class BST
{
private:
    node *root;

public:
    BST();
    bool isEmpt();
    void insert(int num);
    void sort();
    void sort(node *aux);
    bool search(int num);
    node* getParent(int num, int degree = 1);
    void updadeHeightBalance();
    void updadeHeightBalance(node *aux);
    node* getRoot();
    void balanceTree (node *aux);
    void rightSpin(node *aux, bool isDouble = false);
    void leftSpin(node *aux,  bool isDouble = false);
};