/*
# 1. make_heap():
  This function initializes an empty Fibonacci Heap and returns a reference.
  It should run in O(1) amortized time complexity.

#2. is_empty(heap):
  This function takes the Fibonacci Heap as input and returns True if the
  heap is empty, otherwise False. It should run in O(1) amortized time complexity.

#3. insert(heap, key, value):
  This function inserts a new element with the given key and
  value into the Fibonacci Heap. It should run in O(1) amortized time complexity.

#4. extract_max(heap):
  This function extracts and returns the element with the maximum
  key from the Fibonacci Heap. It should run in O(log n) amortized time complexity.

#5. increase_key(heap, value, new_key):
  This function increases the key of the specified
  node of the given value to the new key. It should run in O(1) amortized time complexity.

#6. delete(heap, value):
  This function deletes the specified node of the given value from the
  Fibonacci Heap. It should run in O(log n) amortized time complexity.

#7. meld(heap1, heap2):
  This function melds two Fibonacci Heaps into one and returns it. It
  should run in O(1) amortized time complexity.

#8. find_max(heap):
  This function returns the maximum element in the Fibonacci Heap
  without extracting it. It should run in O(1) amortized time complexity.

#9. print(heap): This function will print the given heap. The output format is:
  Tree 1: (55, 3) -> (45, 5), (32, 4)
  (45, 5) -> (7, 8)
  Tree 2: (24, 7) -> (5, 10)
  Tree 3: ……………..
  Output explanation: The heap contains two trees. The first tree is rooted at (55, 3) (key,
  value pair) which has two children (45, 5) and (32, 4). The (45, 5) node has one child (7,
  8). The second tree is rooted at (24, 7) which has one child (5, 10)

#10. test():
  Test all the functionalities (mentioned above) of your implemented priority queue
  for all possible scenarios. Carefully think of all possible scenarios for each operation of
  the priority queue. Test your implementation with various scenarios, including inserting
  elements, extracting maximum elements, increasing keys, deleting elements, melding
  heaps, finding the maximum element, etc. Design test cases to validate the correctness
  of your implementation. Simulate those test cases by hand and using your code too. This
  function will print “passed” if all the test cases are passed (the expected output and the
  output from your called functions are the same), otherwise print “not passed”.
*/
#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
  int key;
  int value;
  Node *parent;
  Node *left;
  Node *right;
  Node *child;

  int rank;
  bool mark;

  Node()
  {
    key = 0;
    value = 0;
    rank = 0;
    mark = false;
    parent = NULL;
    left = NULL;
    right = NULL;
    child = NULL;
  }

  Node(int key, int value)
  {
    this->key = key;
    this->value = value;
    rank = 0;
    mark = false;
    parent = child = NULL;
    left = right = this;
  }
};

class FibHeap
{
  void clear()
  {
    while(!is_empty())
    {
      extract_max();
    }
  }
public:
  int size;
  Node *root; // also stores the max node
  // vector<Node *> hashMap;
  unordered_map<int, Node *> map;

  FibHeap()
  {
    size = 0;
    root = make_heap();
    map = unordered_map<int, Node *>();
    // hashMap = vector<Node *>(1000000, NULL);
    
  }

  // ~FibHeap()
  // {
  //   clear();
  // }

  FibHeap(Node *root, int size)
  {
    this->root = root;
    this->size = size;
  }
  Node *make_heap()
  {
    Node *node = NULL;
    return node;
  }
  bool  is_empty()
  {
    return size == 0;
  }
  Node *find_max()
  {
    return this->root;
  }

  void insert(int k, int v)
  {
    Node *x = new Node(k, v);

    if (root == NULL)
    {
      root = x;
    }
    else
    {
      Node *r = root->right;
      // add x to root's right element
      r->left = x;
      x->right = r;
      root->right = x;
      x->left = root;

      // update max if needed
      if (x->key > root->key)
      {
        root = x;
      }
    }
    map.insert({v, x});
    // insert done
    // increase size
    size++;
  }

  FibHeap *meld(FibHeap *heap1, FibHeap *heap2)
  {
    Node *H1 = heap1->root;
    Node *H2 = heap2->root;
    Node *temp;
    Node *H = make_heap();
    H = H1;
    Node *s1 = H->left;
    Node *s2 = H2->left;

    H1->left = s2;
    s2->right = H1;

    s1->right = H2;
    H2->left = s1;

    if (H1->key > H2->key)
    {
      H = H1;
    }
    else
    {
      H = H2;
    }
    FibHeap *fH = new FibHeap(H, heap1->size + heap2->size);

    fH->map = heap1->map;
    fH->map.insert(heap2->map.begin(), heap2->map.end());

    // vector<Node *> mergerdMap = heap1->hashMap;
    // for (int i = 0; i < heap2->hashMap.size(); i++)
    // {
    //   if (heap2->hashMap[i] != NULL)
    //   {
    //     mergerdMap[i] = heap2->hashMap[i];
    //   }
    // }
    // fH->hashMap = mergerdMap;
    // remove reference from H1 and H2
    heap1->root = NULL;
    heap2->root = NULL;
    heap1->size = 0;
    heap2->size = 0;
    heap1->map.clear();
    heap2->map.clear();
    return fH;
  }

  void Fib_link(Node *y, Node *z)
  {
    // cout<<"Before loop"<<endl;Display();
    Node *l = y->left;
    Node *r = y->right;

    l->right = y->right;
    r->left = y->left;

    if (z->right == z)
    {
      root = z;
    }

    y->left = y;
    y->right = y;
    y->parent = z;

    if (z->child == NULL)
    {
      z->child = y;
    }

    Node *zc = z->child;
    Node *zcl = z->child->left;

    y->right = z->child;
    zc->left = y;

    zcl->right = y;
    y->left = zcl;

    if ((y->key) > (z->child)->key)
    {
      z->child = y;
    }
    z->rank += 1;
    // z->rank ++;
    // cout<<"After loop"<<endl;Display();
  }

  void consolidate()
  {
    int d, i;
    float f = ceil(1.0 * log2(size));
    

    // cout<<f<<endl;
    // Display();
    int D = f+1;
    // cout<<"D"<<D<<endl;
    Node* A[D];

    for (int i = 0; i < D; i++)
    {
      A[i] = NULL;
    }
    Node *x = root;
    Node *y;
    Node *tmp;
    bool flag = false;
    // Node * r = x;

    do
    {
      // r = r->right;
      d = x->rank;

      while (A[d] != NULL)
      {
        y = A[d];
        flag = true;
        if (x->key < y->key)
        {
          // swap x,y
          tmp = x;
          x = y;
          y = tmp;
        }

        if (y == root)
        {
          root = x;
        }


        // cout<<"Before Fib_link --y ("<<y->key<<","<<y->value<<")"<<endl;
        // cout<<"Before Fib_link --x ("<<x->key<<","<<x->value<<")"<<endl;
        // Display();
        // if(map.find(y->key) != map.end() && map.find(x->key) != map.end())
        if(!(y->key == x->key && y->value == x->value))
          {Fib_link(y, x);}
        // cout<<"After Fib_link --y ("<<y->key<<","<<y->value<<")"<<endl;
        // cout<<"After Fib_link --x ("<<x->key<<","<<x->value<<")"<<endl;
        // Display();

        if (x->right == x)
        {
          root = x;
        }

        A[d] = NULL;
        d++;
        // if(d>=D)
        // {
        //   break;
        // }
        // cout<<"d "<<d<<endl;
      }
      A[d] = x;
      x = x->right;

    } while (x != root);

    root = NULL;

    for (int i = 0; i < D; i++)
    {
      if (A[i] != NULL)
      {
        A[i]->left = A[i];
        A[i]->right = A[i];

        if (root == NULL)
        {
          root = A[i];
        }
        else
        {
          Node *R = root->left;
          R->right = A[i];
          A[i]->right = root;
          A[i]->left = root->left;
          root->left = A[i];

          if (A[i]->key > root->key)
          {
            root = A[i];
          }
        }

        if (root == NULL)
        {
          root = A[i];
        }
        else if (A[i]->key > root->key)
        {
          root = A[i];
        }
      }
    }
  }

  Node *extract_max()
  {
    Node *z = root;
    if (z == NULL)
    {
      return z;
    }
    Node *mainRoot = z;
    Node *temp = z;

    Node *x;
    x = z->child;
    Node *np;

    if (x != NULL)
    {
      temp = x;
      do
      {
        np = x->right;
        (root->left)->right = x;
        x->right = root;
        x->left = root->left;
        root->left = x;

        if (x->key > root->key)
        {
          root = x;
        }
        x->parent = NULL;
        x = np;
      } while (np != temp);
    }

    (z->left)->right = z->right;
    (z->right)->left = z->left;
    root = z->right;

    // only one node in heap
    // Display();
    if (z == z->right && z->child == NULL)
    {
      root = NULL;
    }

    else
    {
      root = z->right;
    //   cout<<"Before consolidate"<<endl;
    //   Display();
      consolidate();
    //     cout<<"After consolidate"<<endl;
    //   Display();
    }
    size--;
    map.erase(z->value);
    // delete(z);
    return mainRoot;
  }

  void Cut(Node *x, Node *y)
  {
    // remove x from child list of y
    if (x == x->right)
    {
      y->child = NULL;
    }
    Node *xL = x->left;
    Node *xR = x->right;

    xL->right = xR;
    xR->left = xL;

    // child ptr at x
    if (x == y->child)
    {
      y->child = x->right;
    }

    // y rank--
    y->rank = y->rank - 1;

    // add x to root list
    x->right = x;
    x->left = x;
    Node *rL = root->left;

    rL->right = x;

    x->right = root;
    x->left = rL;

    root->left = x;

    // parent and mark adjustments
    x->mark = false;
    x->parent = NULL;
  }

  void Cascade_cut(Node *y)
  {
    Node *z = y->parent;
    if (z != NULL)
    {
      if (y->mark == false)
      {
        y->mark = true;
      }
      else
      {
        Cut(y, z);
        Cascade_cut(z);
      }
    }
  }

  void increase_key(int v, int new_key)
  {
    if (root == NULL)
    {
      cout << "Heap is empty" << endl;
      return;
    }
    Node *x = map[v];
    // Node *x = map.find(v)->second;
    // cout<<"x->key "<<x->key<<endl;
    if (x == NULL)
    {
      cout << "Node not found" << endl;
      return;
    }

    if (new_key < x->key)
    {
      cout << "New key is less than previous key" << endl;
      return;
    }

    // cout<<"inside increase_key => "<<new_key<<" "<<x->key<<endl;
    x->key = new_key;
    Node *y = x->parent;
    if (y != NULL && x->key > y->key)
    {
      Cut(x, y);
    //   cout<<"Before cut"<<endl;
    // Display();
      Cascade_cut(y);
    //   cout<<"After cut"<<endl;
    // Display();
    }

    if (x->key > root->key)
    {
      root = x;
    }
  }

  void deleteNode(int v)
  {
    if(root == NULL)
    {
        cout<<"Heap is empty"<<endl;
        return;
    }
    Node *x = map[v];
    // cout<<"x->key "<<x->key<<"x-> value"<<x->value<<endl;
    // Node *x = map.find(v)->second;
    if (x == NULL)
    {
      cout << "Error: delete is not possible" << endl;
      return;
    }
    // Display();
    increase_key(v, root->key + 1);
    // cout<<"After inc"<<endl;
    // Display();//kaj kore

    extract_max();
    // Display();
  }

  void printHelper(Node *curr, string indent)
  {
    if (curr == NULL)
    {
      return;
    }
    Node *x = curr;
    do
    {
      
      cout << "(" << x->key << "," << x->value << ")";

      x = x->right;
      if (x != curr)
      {
        cout << ',';
      }
      // cout<<endl;
      
    } while (x != curr);

    x = curr;
    do{
      if(x->child != NULL)
      {
        cout<<endl;
        cout <<indent<< "(" << x->key << "," << x->value << ")";
        cout<<"->";
        printHelper(x->child, indent+"        ");
      }
        x = x->right;
        // if(x != curr)
        //   cout<<endl;
    }
      while(x != curr);
  }

  void Display()
  {
    int cnt = 0;
    if (root == NULL)
    {
      cout << "Heap is empty" << endl;
      return;
    }

    Node *mainRoot = root;
    Node *curr = root;
    do
    {
      cout << "Tree " << ++cnt << ": (" << curr->key << "," << curr->value << ")";
      if (curr->child != NULL)
      {
        cout << "->";
        printHelper(curr->child, "        ");
      }
      curr = curr->right;
      cout << endl;
    } while (curr != mainRoot);
  }

};
