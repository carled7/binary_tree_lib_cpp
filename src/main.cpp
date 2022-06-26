#include "bst.h"

using namespace std;

int main()
{
    BST tree = BST();

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(35);
    tree.insert(33);
    tree.insert(40);
    tree.insert(30);
    tree.insert(25);
    tree.insert(20);
    tree.insert(24);
    tree.insert(70);
    tree.insert(50);
    tree.insert(80);
    tree.insert(75);
    tree.insert(72);
    tree.insert(85);
    //tree.insert(90);

	tree.updadeHeightBalance(tree.getRoot());

   tree.sort();

    
    return 0;
}