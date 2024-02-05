#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int key;
    string value;
    int rank;
    bool isMark;
    Node *parent;
    Node *child;
    Node *left;
    Node *right;
    bool isVisited;
    Node()
    {
        key = 0;
        value = "";
        rank = 0;
        isMark = false;
        parent = nullptr;
        child = nullptr;
        left = this;
        right = this;
        isVisited = false;
    }
    Node(int key, string value)
    {
        this->key = key;
        this->value = value;
        rank = 0;
        isMark = false;
        parent = nullptr;
        child = nullptr;
        left = this;
        right = this;
        isVisited = false;
    }
    const Node &operator=(const Node &n)
    {
        key = n.key;
        value = n.value;
        rank = n.rank;
        isMark = n.isMark;
        parent = n.parent;
        child = n.child;
        left = n.left;
        right = n.right;
        isVisited = n.isVisited;
        return *this;
    }
};

class fibonacciHeap
{
public:
    int size;
    Node *minNode;
    Node *rootList;
    fibonacciHeap()
    {
        size = 0;
        rootList = minNode = nullptr;
    }

    ~fibonacciHeap()
    {
        // Release memory for nodes in the root list
        Node *current = rootList;
        Node *next;
        while (current != nullptr)
        {
            next = current->right;
            delete current;
            current = next;
        }
        size = 0;
        minNode = rootList = nullptr;
    }

    fibonacciHeap *initializeHeap()
    {
        fibonacciHeap *fHeap = new fibonacciHeap();
        return fHeap;
    }

    void insert(int key, string value)
    {
        Node *node = new Node(key, value);
        if (rootList == nullptr)
        {
            rootList = node;
        }
        else
        {
            node->left = rootList;
            node->right = rootList->right;
            rootList->right->left = node;
            rootList->right = node;
        }
        rootList = node;
        if (minNode == nullptr || node->key < minNode->key)
        {
            minNode = node;
        }
        size++;
    }

    void mergeRootList(Node *root1, Node *root2)
    {

        if (root1 == nullptr || root2 == nullptr) // Check for nullptr to avoid errors
            return;

        Node *st1 = root1->left;
        Node *st2 = root2->left;
        // root1->left->right = root2;
        // root2->left->left = root1;

        st1->left = root2;
        root2->right = st1;

        st2->left = root1;
        root1->right = st2;
    }

    void removeFromRootlist(Node *z)
    {
        if (z == nullptr) // Check for nullptr to avoid errors
            return;
        if (z == rootList)
        {
            if (z->right == z)
            {
                rootList = nullptr;
                return;
            }
            rootList = z->right;
        }

        Node *l = z->left;
        Node *r = z->right;
        z->parent = nullptr;
        l->right = r->left;
        r->left = l->right;
    }

    void makeChild(Node *y, Node *x)
    {
        if (x == nullptr || y == nullptr) // Check for nullptr to avoid errors
            return;

        if (x->child == nullptr)
        {
            x->child = y;
            y->parent = x;
            y->left = y;
            y->right = y;
            return;
        }
        Node *c = x->child;
        Node *r = c->right;
        y->parent = x;

        c->right = y;
        y->left = c;

        r->left = y;
        y->right = r;
    }

    static fibonacciHeap *heap_union(fibonacciHeap *H1, fibonacciHeap *H2)
    {
        // cout<<H1->minNode->value<<endl;
        if (H1 == nullptr && H2 != nullptr) // Check for nullptr to avoid errors
            return H1;
        else if (H1 != nullptr && H2 == nullptr) // Check for nullptr to avoid errors
            return H2;
        else if (H1 == nullptr && H2 == nullptr) // Check for nullptr to avoid errors
            return nullptr;

        fibonacciHeap *H = H->initializeHeap();
        cout << H1->minNode->value << endl;
        H->minNode = H1->minNode;
        H->rootList = H1->rootList;
        H->mergeRootList(H->rootList, H2->rootList);
        cout << H1->minNode->key << " " << H2->minNode->key << endl;
        if (H1->minNode == nullptr || (H2->minNode != nullptr && H2->minNode->key < H1->minNode->key))
        {
            H->minNode = H2->minNode;
        }

        H->size = H1->size + H2->size;
        return H;
    }

    Node *ExtractMin()
    {
        Node *z = this->minNode;
        if (z == nullptr)
            return z;
        // cout<<"1 ";
        // if (z != nullptr)
        // {
        // cout<<"2 ";
        Node *c = z->child;
        Node *firstChild = c;
        // c = c->right;
        // cout<<"3 ";
        while (c != nullptr)
        {
            Node *x = c;
            c = c->right;
            mergeRootList(this->rootList, x);
            x->parent = nullptr;
            if (c == firstChild)
                break;
        }
        removeFromRootlist(z);

        if (z == z->right && z->child == nullptr)
        {
            this->rootList = this->minNode = nullptr;
        }
        else
        {
            this->rootList = this->minNode = z->right;
            Consolidate();
        }
        size = size - 1;
        // }
        return z;
    }

    void Consolidate()
    {
        Node *a[size];
        for (int i = 0; i < size; i++)
        {
            a[i] = nullptr;
        }
        Node *root = rootList;
        Node *lastNode = root;
        // root = root->right;
        while (root != nullptr)
        {
            Node *x = root;
            root = root->right;
            int d = x->rank;
            while (a[d] != nullptr)
            {
                Node *y = a[d];
                if (x->key > y->key)
                {
                    Node *np = x;
                    x = y;
                    y = np;
                    // swap(x,y);
                }
                Fib_link(y, x);
                a[d] = nullptr;
                d = d + 1;
            }
            a[d] = x;
            if (root == lastNode)
                break;
        }
        minNode = nullptr;
        rootList = nullptr;

        for (int i = 0; i < size; i++)
        {
            if (a[i] != nullptr)
            {
                a[i]->left = a[i];
                a[i]->right = a[i];
                if (minNode == nullptr)
                {
                    minNode = rootList = a[i];
                    a[i]->left = a[i];
                    a[i]->right = a[i];
                }
                else
                {
                    Node *tmp = a[i];
                    tmp->left = rootList;
                    tmp->right = rootList->right;
                    rootList->right->left = tmp;
                    rootList->right = tmp;

                    if (tmp->key < minNode->key)
                    {
                        minNode = tmp;
                        cout << minNode->key << endl;
                        rootList = minNode;
                    }
                }
            }
        }
        // cout << "AFTER " << rootList->value << endl;
        // if(rootList==nullptr)
        //     cout<<"NULL"<<endl;
    }
//     void Consolidate() {
//         Node* H1 = rootList;
//         int nH = size;
//   int d, i;
//   float f = (log(nH)) / (log(2));
//   int D = f;
//   Node *A[D];

//   for (i = 0; i <= D; i++)
//     A[i] = NULL;

//   Node *x = H1;
//   Node *y;
//   Node *np;
//   Node *pt = x;

//   do {
//     pt = pt->right;

//     d = x->rank;

//     while (A[d] != NULL)

//     {
//       y = A[d];

//       if (x->key > y->key)

//       {
//         np = x;

//         x = y;

//         y = np;
//       }

//       if (y == H1)
//         H1 = x;
//       Fib_link(y, x);
//       if (x->right == x)
//         H1 = x;
//       A[d] = NULL;
//       d = d + 1;
//     }

//     A[d] = x;
//     x = x->right;

//   }
//   while (x != H1);
// Node* H = minNode;
//   H = NULL;
//   for (int j = 0; j <= D; j++) {
//     if (A[j] != NULL) {
//       A[j]->left = A[j];
//       A[j]->right = A[j];
//       if (H != NULL) {
//         (H->left)->right = A[j];
//         A[j]->right = H;
//         A[j]->left = H->left;
//         H->left = A[j];
//         if (A[j]->key < H->key)
//           H = A[j];
//       } else {
//         H = A[j];
//       }
//       if (H == NULL)
//         H = A[j];
//       else if (A[j]->key < H->key)
//         H = A[j];
//     }
//   }
// }

    void Fib_link(Node *y, Node *x)
    {
        removeFromRootlist(y);
        makeChild(y, x);
        y->isMark = false;
    }

    void printHelp(Node* curr)
    {
        if(curr==nullptr)
            return;
        cout<<curr->value<<" ";
        Node* child = curr->child;
        if(child!=nullptr)
        {
            printHelp(child);
            child = child->right;
            while(child!=curr->child)
            {
                printHelp(child);
                child = child->right;
            }
        }
    }

    void Display()
    {
        if(rootList)
            printHelp(rootList);

    }

};

int main()
{
    // Create a Fibonacci Heap
    fibonacciHeap *fHeap = new fibonacciHeap();

    // Insert some nodes
    fHeap->insert(5, "Node 5");
    // cout<<" x "<<endl;
    fHeap->insert(3, "Node 3");
    fHeap->insert(7, "Node 7");
    fHeap->insert(10, "Node 10");
    fHeap->Display();
    // cout<<"nice"<<endl;

    // // Extract minimum node
    // Node *minNode = fHeap->ExtractMin();
    // if (minNode != nullptr)
    // {
    //     cout << "Minimum Node: " << minNode->value << endl;
    //     delete minNode; // Free memory of extracted node
    // }
    // fHeap->Display();

    // Union two Fibonacci Heaps
    fibonacciHeap* anotherHeap = new fibonacciHeap();
    anotherHeap->insert(15, "Node 15");
    anotherHeap->insert(11, "Node 11");
    anotherHeap->Display();
    // Node *tmp = fHeap->ExtractMin();
    // if(tmp!=nullptr)
    //     cout<<"TMP: "<<tmp->value<<endl;
    // anotherHeap->insert(8, "Node 8");
    fibonacciHeap* mergedHeap = fHeap->heap_union(fHeap, anotherHeap);
    mergedHeap->Display();

    // // Extract minimum node from merged heap
    // Node* minNodeMerged = mergedHeap->ExtractMin();
    // if (minNodeMerged != nullptr) {
    //     cout << "Minimum Node from Merged Heap: " << minNodeMerged->value << endl;
    //     delete minNodeMerged; // Free memory of extracted node
    // }
    // mergedHeap->Display();
    // delete mergedHeap;

    // // Clean up memory
    // delete anotherHeap;
    delete fHeap;

    return 0;
}
