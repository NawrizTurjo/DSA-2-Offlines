#include <bits/stdc++.h>
#include "color.hpp"
using namespace std;
#define BLACK 0
#define RED 1

class Node
{
public:
    int data;
    string value;
    Node *parent;
    Node *left;
    Node *right;
    int color;

    Node(int data, string value, Node *parent, Node *left, Node *right)
    {
        this->data = data;
        this->value = value;
        this->parent = parent;
        this->left = left;
        this->right = right;
        color = BLACK;
    }

    Node(int data, string value, Node *parent, Node *left, Node *right, int color)
    {
        this->data = data;
        this->value = value;
        this->parent = parent;
        this->left = left;
        this->right = right;
        this->color = color;
    }

    // Node(int data,string value)
    // {
    //     this->data = data;
    //     this->value = value;
    //     this->parent = NULL;
    //     this->left = NULL;
    //     this->right = NULL;
    //     color = RED;
    // }

    Node()
    {
        this->data = 0;
        this->value = "";
        this->parent = NULL;
        this->left = NULL;
        this->right = NULL;
        color = BLACK;
    }
};

class RedBlackTree
{
public:
    Node *root;
    Node *NIL;
    RedBlackTree()
    {
        this->NIL = new Node();
        this->root = NIL;
    }

    void leftRotate(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;

        if (y->left != NIL)
        {
            y->left->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node *x)
    {
        Node *y = x->left;
        x->left = y->right;

        if (y->right != NIL)
        {
            y->right->parent = x;
        }

        y->parent = x->parent;

        if (x->parent == NULL)
        {
            root = y;
        }

        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }

        else
            x->parent->left = y;

        y->right = x;
        x->parent = y;
    }

    Node *search(Node *curr, int key)
    {
        if (curr->data == key || curr==NIL)
        {
            return curr;
        }

        else if (curr->data < key)
        {
            return search(curr->right, key);
        }

        return search(curr->left, key);
    }

    void insertFix(Node *z)
    {
        while (z->parent->color == RED)
        {
            if (z->parent == z->parent->parent->left) // parent is left child of grandparent
            {
                Node *y = z->parent->parent->right; // sibling y
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right) // L-R
                    {
                        z = z->parent;
                        leftRotate(z);
                    }
                    // R-R
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate(z->parent->parent);
                }
            }

            else // parent is right child of grandparent
            {
                Node *y = z->parent->parent->left; // sibling y
                if (y->color == RED)
                {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left) // R-L
                    {
                        z = z->parent;
                        rightRotate(z);
                    }
                    // L-L
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate(z->parent->parent);
                }
            }
            if(z == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }

    void insert(int key, string val)
    {
        Node *temp = search(root, key);
        if (temp != NIL)
        {
            temp->value = val;
            return;
        }

        Node *z = new Node(key, val, NIL, NIL, NIL, RED);

        Node *y = NIL;
        Node *x = root;

        while (x != NIL)
        {
            y = x;
            if (z->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == NIL)
        {
            root = z;
        }

        else if (z->data < y->data)
        {
            y->left = z;
        }

        else
        {
            y->right = z;
        }

        // z->left = NIL;
        // z->right = NIL;

        if(z->parent == NIL)
        {
            z->color = BLACK;
            return;
        }

        if(z->parent->parent == NIL)
        {
            return;
        }

        insertFix(z);
    }

    bool isEmpty()
    {
        return root == NIL;
    }

    void printHelper(Node *curr, string indent, bool last)
    {
        if (curr != NIL)
        {
            cout << indent;
            if (last)
            {
                cout << "R----";
                indent += "   ";
            }
            else
            {
                cout << "L----";
                indent += "|  ";
            }

            string sColor = curr->color ? "RED" : "BLACK";
            if (sColor == "RED")
                cout << hue::red << curr->data << "_" << curr->value;
            // cout << dye::red(sColor);
            else
                cout << hue::black << curr->data << "_" << curr->value;
            // cout << dye::black(sColor);
            cout << endl;
            printHelper(curr->left, indent, false);
            printHelper(curr->right, indent, true);
        }
    }

    void transplant(Node *u, Node *v)
    {
        if(u->parent == NIL)
        {
            root = v;
        }
        else if (u==u->parent->left)
        {
            u->parent->left = v;
        }
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    void erase(Node *z)
    {
        Node *x;
        Node * y = z;
        int ogColor = y->color;

        if(z->left == NIL)
        {
            x = z->right;
            transplant(z,z->right);
        }

        else if(z->right == NIL)
        {
            x = z->left;
            transplant(z,z->left);
        }
    }

    void printTree()
    {
        if (root)
        {
            printHelper(root, "", true);
        }
    }
};

int main()
{
    RedBlackTree bst;
    bst.printTree();
    bst.insert(10, "Thors");
    bst.printTree();
    bst.insert(34,"Canute");
    bst.printTree();
    bst.insert(43,"Olaf");
    bst.printTree();
    // bst.insert(15,"Einer");
    // bst.printTree();
    // bst.insert(40,"Olmar");
    // bst.printTree();
    // bst.insert(45,"Estrid");
    // bst.printTree();
    // bst.insert(53, "Floki");
    // bst.printTree();
    // bst.insert(90 ,"Thorfinn");
    // bst.printTree();
    // bst.insert(12, "Snake");
    // bst.printTree();
    // bst.insert(78, "Askeladd");
    // bst.printTree();
}
