#include <bits/stdc++.h>
#include "Fibonacci-Heap.cpp"
using namespace std;

class Priority_queue
{
    // From StackOverflow
    bool compareFiles(const string &p1, const string &p2)
    {
        ifstream f1(p1, ifstream::binary | ifstream::ate);
        ifstream f2(p2, ifstream::binary | ifstream::ate);

        if (f1.fail() || f2.fail())
        {
            return false; // file problem
        }

        if (f1.tellg() != f2.tellg())
        {
            return false; // size mismatch
        }

        // seek back to beginning and use equal to compare contents
        f1.seekg(0, ifstream::beg);
        f2.seekg(0, ifstream::beg);
        return equal(istreambuf_iterator<char>(f1.rdbuf()),
                     istreambuf_iterator<char>(),
                     istreambuf_iterator<char>(f2.rdbuf()));
    }

public:
    // priority_queue()
    // {
    //     heap = new FibHeap();
    // }

    FibHeap *make_heap()
    {
        return new FibHeap();
    }

    bool is_empty(FibHeap *heap)
    {
        return heap->is_empty();
    }

    void insert(FibHeap *heap, int key, int value)
    {
        heap->insert(key, value);
    }

    Node *extract_max(FibHeap *heap)
    {
        return heap->extract_max();
    }

    void increase_key(FibHeap *heap, int value, int new_key)
    {
        heap->increase_key(value, new_key);
    }

    void Delete(FibHeap *heap, int value)
    {
        heap->deleteNode(value);
    }

    FibHeap *meld(FibHeap *heap1, FibHeap *heap2)
    {
        return heap1->meld(heap1, heap2);
    }

    Node *find_max(FibHeap *heap)
    {
        return heap->find_max();
    }

    void print_heap(FibHeap *heap)
    {
        heap->Display();
    }
    void test()
    {
        // FibHeap *fH = new FibHeap();
        // auto start_insert = chrono::high_resolution_clock::now();
        // for (int i = 1; i <= 1000000; i++)
        // {
        //     fH->insert(i, i);
        // }
        // auto stop_insert = chrono::high_resolution_clock::now();

        // // Start measuring time for the second loop
        // auto start_extract = chrono::high_resolution_clock::now();

        // for (int i = 1; i <= 1000000; i++)
        // {
        //     fH->extract_max();
        // }
        // auto stop_extract = chrono::high_resolution_clock::now();

        // // Calculate the duration for each loop
        // auto duration_insert = chrono::duration_cast<chrono::milliseconds>(stop_insert - start_insert);
        // auto duration_extract = chrono::duration_cast<chrono::milliseconds>(stop_extract - start_extract);
        // auto duration = chrono::duration_cast<chrono::milliseconds>(stop_extract - start_insert);

        // // Output the durations
        // // cout << "Time taken for insertion loop: " << duration_insert.count() << " milliseconds\n";
        // // cout << "Time taken for extraction loop: " << duration_extract.count() << " milliseconds\n";
        // // cout << "Total time taken: " << duration.count() << " milliseconds\n";

        // if(duration.count() < 1000)
        // {
        //     cout<<"Success"<<endl;
        // }
        // else
        // {
        //     cout<<"Fail"<<endl;
        // }
        freopen("heapOut.txt", "w", stdout);
        // FibHeap *Heap = new FibHeap();
        // for (int i = 1; i <= 100; i++)
        // {
        //     if (i % 2 == 0)
        //         Heap->insert(i, i * (-1));
        //     else
        //         Heap->insert(i, i);
        // }
        // cout << "Initial Heap after insertion" << endl;
        // Heap->Display();

        // cout << "Extracting max for 10 times" << endl;
        // for (int i = 1; i <= 10; i++)
        // {
        //     cout << "Extracting max...#" << i << "--->" << endl;
        //     Heap->extract_max();
        //     Heap->Display();
        // }

        // cout << "Increasing key of 10 to 100" << endl;
        // Heap->increase_key(10, 100);
        // Heap->Display();

        // cout << "Increasing key of 20 to 200" << endl;
        // Heap->increase_key(20, 200);
        // Heap->Display();

        // cout << "Deleting 10 elements" << endl;
        // for (int i = 5; i <= 15; i++)
        // {
        //     cout << "Deleting Node Containing value " << i << "--->" << endl;
        //     Heap->deleteNode(i);
        //     Heap->Display();
        // }

        // FibHeap *Heap2 = new FibHeap();
        // for (int i = -100; i < 0; i++)
        // {
        //     if (i % 2)
        //         Heap2->insert(i, i * (-1));
        //     else
        //         Heap2->insert(i, i);
        // }

        // for (int i = 0; i < 10; i++)
        // {
        //     Heap2->extract_max();
        // }

        // cout << "Heap 1 before melding...." << endl;
        // Heap->Display();
        // cout << "Heap 2 before melding...." << endl;
        // Heap2->Display();

        // cout << "Melding both heaps" << endl;
        // FibHeap *meldedHeap = Heap->meld(Heap, Heap2);
        // cout << "Melded Successful...displaying----->" << endl;
        // meldedHeap->Display();

        // cout << "FindMax from melded heap: " << endl;

        // Node *maxNode = meldedHeap->find_max();
        // cout << "\t\t{ key: " << maxNode->key << ", value: " << maxNode->value << " }" << endl;

        // cout << "Extracting max from melded heap and finding max for 15 times..." << endl;

        // for (int i = 1; i <= 15; i++)
        // {
        //     cout << "Extracting max...#" << i << "--->" << endl;
        //     meldedHeap->extract_max();
        //     maxNode = meldedHeap->find_max();
        //     cout << "\t\t{ key: " << maxNode->key << ", value: " << maxNode->value << " }" << endl;
        // }

        // cout << "Checking if melded heap is empty or not..." << endl;

        // meldedHeap->is_empty() ? cout << "Empty" << endl : cout << "Not Empty" << endl;

        FibHeap *heap1 = new FibHeap();
        for (int i = 1; i <= 16; i++)
        {
            heap1->insert(i, i);
        }

        print_heap(heap1);

        extract_max(heap1);
        print_heap(heap1);

        increase_key(heap1, 1,8);
        print_heap(heap1);

        increase_key(heap1,3,13);
        print_heap(heap1);

        increase_key(heap1, 5,14);
        print_heap(heap1);

        increase_key(heap1, 2,12);
        print_heap(heap1);

        Delete(heap1,2);
        print_heap(heap1);
        //# marked node check

        FibHeap *heap2 = make_heap();
        for(int i=1;i<=18;i++)
        {
            insert(heap2, i+16, i+16);
        }
        print_heap(heap2);

        extract_max(heap2);
        print_heap(heap2);
        
        extract_max(heap2);
        print_heap(heap2);
        
        extract_max(heap2);
        print_heap(heap2);
        
        extract_max(heap2);
        print_heap(heap2);
        
        extract_max(heap2);
        print_heap(heap2);
        
        Delete(heap2,24);
        print_heap(heap2);

        FibHeap *meldHeap = meld(heap1, heap2);
        print_heap(meldHeap);

        Delete(meldHeap, 4);
        print_heap(meldHeap);

        Delete(meldHeap, 11);
        print_heap(meldHeap);

        Delete(meldHeap, 10);
        print_heap(meldHeap);

        is_empty(meldHeap) ? cout << "Empty" << endl : cout << "Not Empty" << endl;

        Node* maxNode = find_max(meldHeap);
        cout << "Max Node: " << maxNode->key << " " << maxNode->value << endl;

        FibHeap *heap3 = new FibHeap();
        for (int i = 1; i <= 5; i++)
        {
            heap3->insert(i, i);
        }

        while(!(is_empty(heap3)))
        {
            extract_max(heap3);
            print_heap(heap3);
        }

        extract_max(heap3);
        print_heap(heap3);

        Delete(heap3, 1);
        print_heap(heap3);

        // fflush(stdout);

        // fclose(stdout);

        // freopen("CON", "w", stdout);

        // this_thread::sleep_for(chrono::milliseconds(2000));

        // string command = "fc heapOut.txt heapCheck.txt";

        // int result = system(command.c_str());

        // cout<<result<<endl;

        // if (result == 0) {
        //     cout << "Success {:>}" << endl;
        // } else {
        //     cout << "Unsuccessful {;<}" << endl;
        // }

        // if (compareFiles("heapOut.txt", "heapCheck.txt"))
        // {
        //     cout << "Successful" << endl;
        // }
        // else
        // {
        //     cout << "UnsuccessFul" << endl;
        // }

        // cout << "Testing Completed" << endl;
    }
};