#include <bits/stdc++.h>
#include "Fibonacci-Heap.cpp"
using namespace std;

class priority_queue
{
    FibHeap *heap;

public:
    priority_queue()
    {
        heap = new FibHeap();
    }
    void test()
    {
        FibHeap *fH = new FibHeap();
        auto start_insert = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= 1000000; i++)
        {
            fH->insert(i, i);
        }
        auto stop_insert = std::chrono::high_resolution_clock::now();

        // Start measuring time for the second loop
        auto start_extract = std::chrono::high_resolution_clock::now();

        for (int i = 1; i <= 1000000; i++)
        {
            fH->extract_max();
        }
        auto stop_extract = std::chrono::high_resolution_clock::now();

        // Calculate the duration for each loop
        auto duration_insert = std::chrono::duration_cast<std::chrono::milliseconds>(stop_insert - start_insert);
        auto duration_extract = std::chrono::duration_cast<std::chrono::milliseconds>(stop_extract - start_extract);
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop_extract - start_insert);

        // Output the durations
        // std::cout << "Time taken for insertion loop: " << duration_insert.count() << " milliseconds\n";
        // std::cout << "Time taken for extraction loop: " << duration_extract.count() << " milliseconds\n";
        // std::cout << "Total time taken: " << duration.count() << " milliseconds\n";

        if(duration.count() < 1000)
        {
            cout<<"Success"<<endl;
        }
        else
        {
            cout<<"Fail"<<endl;
        }

        // fH->Display();
    }
};