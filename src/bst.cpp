#include "bst.h"

struct node
{
    int value, height, balance;
    node *left, *right;

    node(int _x)
    {
        value = _x;
        left = NULL;
        right = NULL;
    }
};

BST::BST()
{
    root = NULL;
}

bool BST::isEmpt()
{
    return (root == NULL);
}

void BST::insert(int num)
{
    if (isEmpt())
    {
        root = new node(num);
        root->balance = 0;
        root->height = 1;
    }
    else
    {
        node *aux = root;
        do
        {
            if (num < aux->value)
            {
                if (aux->left == NULL)
                {
                    aux->left = new node(num);
                    aux->left->height = 1;
                    aux->left->balance = 0;
                    updadeHeightBalance(root);
                    balanceTree(getParent(aux->value, 3));

                    return;
                }
                else
                {
                    aux = aux->left;
                }
            }
            else if (num > aux->value)
            {
                if (aux->right == NULL)
                {
                    aux->right = new node(num);
                    aux->right->height = 1;
                    aux->right->balance = 0;
                    updadeHeightBalance(root);
                    balanceTree(getParent(aux->value, 3));
                    return;
                }
                else
                {
                    aux = aux->right;
                }
            }
            else
                return;

        } while (aux != NULL);
    }
}

void BST::sort()
{
    system("clear");
    sort(root);
    cout << endl;
}

void BST::sort(node *aux)
{
    if (aux != NULL)
    {
        sort(aux->left);
        cout << aux->value << "\theight: " << aux->height
             << "\tbalance: " << aux->balance << endl;
        sort(aux->right);
    }
}

bool BST::search(int num)
{
    if (!isEmpt())
    {
        node *aux = root;
        while (aux != NULL)
        {
            if (num == aux->value)
            {
                return true;
            }
            else if (num < aux->value)
            {
                aux = aux->left;
            }
            else if (num > aux->value)
            {
                aux = aux->right;
            }
        }
        return false;
    }
    return false;
}

node *BST::getParent(int num, int degree)
{
    if (!isEmpt())
    {

        if (degree == 1)
        {
            node *aux = root, *parent = root;
            while (aux != NULL)
            {
                if (num == aux->value)
                {
                    return parent;
                }
                else if (num < aux->value)
                {
                    parent = aux;
                    aux = aux->left;
                }
                else if (num > aux->value)
                {
                    parent = aux;
                    aux = aux->right;
                }
            }
        }
        else
        {
            node *temp = new node(num);
            for (int i = 1; i < degree; i++)
            {
                temp = getParent(temp->value);
            }
            return temp;
        }
        return 0;
    }
    return 0;
}

void BST::updadeHeightBalance()
{
    updadeHeightBalance(root);
}

void BST::updadeHeightBalance(node *aux)
{

    if (aux != NULL)
    {

        updadeHeightBalance(aux->left);
        updadeHeightBalance(aux->right);

        int leftHeight = aux->left == NULL ? 0 : aux->left->height;
        int rightHeight = aux->right == NULL ? 0 : aux->right->height;

        aux->height = max(leftHeight, rightHeight) + 1;
        aux->balance = leftHeight - rightHeight;
    }
}

node *BST::getRoot()
{
    return root;
}

void BST::balanceTree(node *aux)
{

    if (aux != NULL && abs(aux->balance) > 1)
    {
        // sort();

        if (aux->balance < -1)
        { // desbalanceado à esquerda
            if (aux->right->balance < 0)
            { // rotação simples à direita
                rightSpin(aux);
            }
            else if (aux->right->balance > 0)
            { // rotação dupla à direita
                leftSpin(aux->right, true);
                rightSpin(aux);
            }
        }
        else if (aux->balance > 1)
        { // desbalanceado à direita
            if (aux->left->balance > 0)
            { // rotação simples à esquerda
                leftSpin(aux);
            }
            else if (aux->left->balance < 0)
            { // rotação dupla à esquerda
                rightSpin(aux->left, true);
                leftSpin(aux);
            }
        }

        updadeHeightBalance(root);
        balanceTree(aux->left);
        balanceTree(aux->right);
    }
}

void BST::rightSpin(node *aux, bool isDouble)
{

    node *parent, *axis;

    parent = getParent(aux->value);
    axis = aux->right;

    if (axis->left != NULL)
    {
        aux->right = axis->left;
    }
    else
    {
        aux->right = NULL;
    }

    axis->left = aux;

    if (parent == root)
        root = axis;
    else if (isDouble)
        parent->left = axis;
    else
        parent->right = axis;
}

void BST::leftSpin(node *aux, bool isDouble)
{

    node *parent, *axis;

    parent = getParent(aux->value);
    axis = aux->left;

    if (axis->right != NULL)
    {
        aux->left = axis->right;
    }
    else
    {
        aux->left = NULL;
    }

    axis->right = aux;

    if (parent == root)
        root = axis;
    else if (isDouble)
        parent->right = axis;
    else
        parent->left = axis;
}

// se o parent for root, então axis sera o root
// verificar os nos filhos do no aux depois do balanceamento