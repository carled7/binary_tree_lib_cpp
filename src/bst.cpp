#include "bst.h"

struct node
{
    int value, height, balance, nLeft, nRight, depth;
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

                    cout << "INSERINDO " << num << endl;
                    while (getUnbalanced() != NULL)
                        balanceTree(getUnbalanced());
                    sort();
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
                    cout << "INSERINDO " << num << endl;
                    while (getUnbalanced() != NULL)
                        balanceTree(getUnbalanced());
                    sort();
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
    // system("clear");
    cout << endl;
    sort(root);
    cout << "------------------------------------" << endl;
}

void BST::sort(node *aux)
{
    if (aux != NULL)
    {
        //"\tnLef: " << aux->nLeft << "\tnRig: " << aux->nRight << "\tnDep: " << aux->depth
        sort(aux->left);
        cout << aux->value << "\theight: " << aux->height
             << "\tbalance: " << aux->balance << endl;
        sort(aux->right);
    }
}

bool BST::isLeaf(node *aux)
{
    if (aux->left == NULL && aux->right == NULL)
        return true;
    else
        return false;
}

void BST::print()
{
    //Método em desenvolvimento
    int buffer = 0;
    for (int d = 0; d < root->height; d++)
    {
        print(root, d, &buffer);
        cout << endl;
    }
}

void BST::print(node *aux, int depth, int *buffer)
{
    //Método em desenvolvimento
    if (aux != NULL && aux->depth == depth)
    {
        int lNleft = aux->left == NULL ? 0 : aux->left->nLeft;
        int lNright = aux->left == NULL ? 0 : aux->left->nRight;
        int rNleft = aux->right == NULL ? 0 : aux->right->nLeft;
        int rNright = aux->right == NULL ? 0 : aux->right->nRight;

        /*for (int i = 0; i <= lNleft; i++)
            cout << "   ";
        cout << '|';
        for (int i = 0; i < lNright; i++)
            cout << "---";
        cout << aux->value;
        for (int i = 0; i < rNleft; i++)
            cout << "---";
        cout << '|';
        for (int i = 0; i <= rNright; i++)
            cout << "   ";*/
        if (!isLeaf(aux))
        {
            for (int i = 0; i <= aux->nLeft; i++)
            {
                cout << "   ";
            }
            cout << aux->value;
            for (int i = 0; i <= aux->nRight; i++)
            {
                cout << "   ";
            }
        }
        else
        {
            for (int i = 0; i <= getParent(aux->value, 2)->nLeft - 3; i++)
            {
                cout << " ";
            }
            cout << aux->value;
            for (int i = 0; i < *buffer; i++)
            {
                cout << "XXX";
            }
        }
        return;
    }
    else if (aux != NULL && aux->depth < depth)
    {
        //*buffer++;
        print(aux->left, depth, buffer);
        print(aux->right, depth, buffer);
    }
    else
        return;
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

int BST::getDepth(int num)
{
    node *aux = root;
    int depth = 0;
    while (aux != NULL)
    {
        if (num == aux->value)
            return depth;
        else if (num < aux->value)
        {
            depth++;
            aux = aux->left;
        }
        else if (num > aux->value)
        {
            depth++;
            aux = aux->right;
        }
    }
    return NULL;
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

node *BST::getNode(int num)
{
    node *buffer = NULL;

    return getNode(num, root, buffer);
}

node *BST::getNode(int num, node *aux, node *buffer)
{

    if (aux != NULL && aux->value == num)
        return aux;
    else if (aux != NULL)
    {
        buffer = getNode(num, aux->left, buffer);
        buffer = buffer == NULL ? getNode(num, aux->right, buffer) : buffer;
    }
    return buffer;
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

        aux->nLeft = aux->left != NULL ? aux->left->nLeft + aux->left->nRight + 1 : 0;
        aux->nRight = aux->right != NULL ? aux->right->nLeft + aux->right->nRight + 1 : 0;
        aux->depth = getDepth(aux->value);
    }
}

node *BST::getRoot()
{
    return root;
}

int BST::balanceTree(node *aux)
{

    if (aux != NULL && abs(aux->balance) > 1)
    {
        if (aux->balance < -1)
        { // desbalanceado à esquerda
            if (aux->right->balance < 0)
            { // rotação simples à direita
                cout << "Rotação simples à direita (" << aux->value << ")" << endl;
                rightSpin(aux);
            }
            else if (aux->right->balance > 0)
            { // rotação dupla à direita
                cout << "Rotação dupla à direita (" << aux->value << ")" << endl;
                leftSpin(aux->right, true);
                rightSpin(aux);
            }
        }
        else if (aux->balance > 1)
        { // desbalanceado à direita
            if (aux->left->balance > 0)
            { // rotação simples à esquerda
                cout << "Rotação simples à esquerda (" << aux->value << ")" << endl;
                leftSpin(aux);
            }
            else if (aux->left->balance < 0)
            { // rotação dupla à esquerda
                cout << "Rotação dupla à esquerda (" << aux->value << ")" << endl;
                rightSpin(aux->left, true);
                leftSpin(aux);
            }
        }

        updadeHeightBalance(root);
        balanceTree(aux->left);
        balanceTree(aux->right);
    }
    return -1;
}

node *BST::getUnbalanced()
{
    int buffer = -1;
    return getNode(getUnbalanced(&buffer, root));
}

int BST::getUnbalanced(int *num, node *aux)
{
    if (aux == NULL)
    {
        return *num;
    }
    else if (aux != NULL)
    {
        if (*num == -1 && abs(aux->balance) > 1)
        {
            *num = aux->value;
            return *num;
        }
        else
        {
            getUnbalanced(num, aux->left);
            if (*num == -1)
                getUnbalanced(num, aux->right);
        }
        return *num;
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

    if (aux == root)
        root = axis;
    else if (isDouble)
        parent->left = axis;
    else if (parent->value < axis->value)
        parent->right = axis;
    else if (parent->value > axis->value)
        parent->left = axis;
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

    if (aux == root)
        root = axis;
    else if (isDouble)
        parent->right = axis;
    else if (parent->value > axis->value)
        parent->left = axis;
    else if (parent->value < axis->value)
        parent->right = axis;
}

void BST::test(BST tree){
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        tree.insert(rand()%300);
    }
    tree.sort();
}