#include <iostream>
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
};


class RedBlackTree
{
private:
    Node *root;
    Node *NIL;
    int size;

    // Preorder
    void preOrderHelper(Node *node)
    {
        if (node != NIL)
        {
            cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    // Inorder
    void inOrderHelper(Node *node)
    {
        if (node != NIL)
        {
            inOrderHelper(node->left);
            string sColor = node->color ? "RED" : "BLACK";
            if (sColor == "RED")
                cout << hue::red << node->data << " ⇒ " << node->value << hue::reset << endl;
            else
                cout << hue::white << node->data << " ⇒ " << node->value << hue::reset << endl;
            inOrderHelper(node->right);
        }
    }

    // Post order
    void postOrderHelper(Node *node)
    {
        if (node != NIL)
        {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            cout << node->data << " ";
        }
    }

    // Searching a node with given key
    Node *searchTreeHelper(Node *node, int key)
    {
        while (node != NIL && key != node->data)
        {
            if (key < node->data)
            {
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }
        return node;
    }

    // For balancing the tree after deletion
    void deleteTreeFix(Node *x)
    {
        Node *s;
        while (x != root && x->color == BLACK)
        {
            if (x == x->parent->left)
            {
                s = x->parent->right;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                s = x->parent->left;
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = BLACK;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void rbTransplant(Node *u, Node *v)
    {
        if (u->parent == nullptr)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(Node *node, int key, bool arg = true)
    {
        Node *z = NIL;
        Node *x;
        Node *y;
        while (node != NIL)
        {
            if (node->data == key)
            {
                z = node;
            }

            if (node->data <= key)
            {
                node = node->right;
            }
            else
            {
                node = node->left;
            }
        }

        if (z == NIL)
        {
            cout << key << " not found" << endl;
            return;
        }
        size--;

        y = z;
        int y_original_color = y->color;
        if (z->left == NIL)
        {
            x = z->right;
            rbTransplant(z, z->right);
        }
        else if (z->right == NIL)
        {
            x = z->left;
            rbTransplant(z, z->left);
        }
        else
        {
            y = maximum(z->left);
            y_original_color = y->color;
            x = y->left;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                rbTransplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            rbTransplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK)
        {
            deleteTreeFix(x);
        }
        if (arg)
            printTree();
    }

    // For balancing the tree after insertion
    void insertFix(Node *k)
    {
        Node *u;
        while (k->parent->color == RED)
        {
            if (k->parent == k->parent->parent->right)
            {
                u = k->parent->parent->left;
                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->left)
                    {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            else
            {
                u = k->parent->parent->right;

                if (u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                }
                else
                {
                    if (k == k->parent->right)
                    {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }

    void printHelper(Node *root, string indent, bool last)
    {
        if (root != NIL)
        {
            string sColor = root->color ? "RED" : "BLACK";
            if (sColor == "RED")
                cout << hue::red << root->data << "_" << root->value << hue::reset;

            else
                cout << root->data << "_" << root->value;

            if (root->left != NIL || root->right != NIL)
            {
                cout << "(";
            }
            printHelper(root->left, "", false);
            if (root->left != NIL || root->right != NIL)
            {
                cout << ",";
            }
            printHelper(root->right, "", true);
            if (root->left != NIL || root->right != NIL)
            {
                cout << ")";
            }
        }
    }

public:
    RedBlackTree()
    {
        NIL = new Node;
        NIL->color = BLACK;
        NIL->left = nullptr;
        NIL->right = nullptr;
        root = NIL;
        size = 0;
    }

    int getSize()
    {
        return this->size;
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void preorder()
    {
        preOrderHelper(this->root);
    }

    void inorder()
    {
        inOrderHelper(this->root);
    }

    void postorder()
    {
        postOrderHelper(this->root);
    }

    Node *searchTree(int k)
    {
        return searchTreeHelper(this->root, k);
    }

    Node *minimum(Node *node)
    {
        while (node->left != NIL)
        {
            node = node->left;
        }
        return node;
    }

    Node *maximum(Node *node)
    {
        while (node->right != NIL)
        {
            node = node->right;
        }
        return node;
    }

    Node *successor(Node *x)
    {
        if (x->right != NIL)
        {
            return minimum(x->right);
        }

        Node *y = x->parent;
        while (y != NIL && x == y->right)
        {
            x = y;
            y = y->parent;
        }
        return y;
    }

    Node *predecessor(Node *x)
    {
        if (x->left != NIL)
        {
            return maximum(x->left);
        }

        Node *y = x->parent;
        while (y != NIL && x == y->left)
        {
            x = y;
            y = y->parent;
        }

        return y;
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
        if (x->parent == nullptr)
        {
            this->root = y;
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
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // Inserting a node
    void insert(int key, string val)
    {
        Node *res = searchTreeHelper(root, key);
        if (res != NIL)
        {
            res->value = val;
            return;
        }
        size++;
        Node *node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = NIL;
        node->right = NIL;
        node->color = RED;
        node->value = val;

        Node *y = nullptr;
        Node *x = this->root;

        while (x != NIL)
        {
            y = x;
            if (node->data < x->data)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr)
        {
            root = node;
        }
        else if (node->data < y->data)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }

        if (node->parent == nullptr)
        {
            node->color = BLACK;
            return;
        }

        if (node->parent->parent == nullptr)
        {
            return;
        }

        insertFix(node);
    }

    Node *getRoot()
    {
        return this->root;
    }

    void deleteNode(int data, bool arg = true)
    {
        deleteNodeHelper(this->root, data, arg);
    }

    void printTree()
    {
        if (root)
        {
            printHelper(this->root, "", true);
            cout << endl;
        }
    }

    void clear()
    {
        if (root == NIL)
        {
            cout << "unsuccessful" << endl;
            return;
        }
        while (root != NIL)
        {
            deleteNode(root->data, false);
        }
        cout << "successful" << endl;
    }

    void search(int key)
    {
        Node *res = searchTreeHelper(root, key);
        if (res == NIL)
        {
            cout << key << " not found" << endl;
        }
        else
        {
            cout << key << " found" << endl;
        }
    }
};