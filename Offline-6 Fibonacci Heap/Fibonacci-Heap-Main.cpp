#include<bits/stdc++.h>
#include "Prirority-Queue.hpp"
using namespace std;

int main()
{
    Priority_queue pq;
    FibHeap *heap = pq.make_heap();

    pq.insert(heap, -10, 10);
    pq.insert(heap, -20, 20);
    pq.insert(heap, 30, 30);
    pq.insert(heap, 40, 40);
    pq.insert(heap, -50, 50);
    pq.insert(heap, 60, 60);
    pq.insert(heap, -70, 70);
    pq.insert(heap, 80, 80);

    pq.print_heap(heap);
    // while(!pq.is_empty(heap))
    // {
    //     pq.extract_max(heap);
    //     pq.print_heap(heap);
    //     cout<<endl<<endl;
    // }

    pq.extract_max(heap);
    pq.print_heap(heap);
    // cout<<pq.extract_max(heap)->key<<endl;

    // pq.increase_key(heap, 10, 60);
    // pq.increase_key(heap, 10, 50);

    pq.Delete(heap, 20);

    pq.print_heap(heap);

    pq.Delete(heap, 50);
    pq.print_heap(heap);
    // cout<<endl<<endl<<endl<<endl<<endl;

    // pq.Delete(heap, 70);
    // pq.print_heap(heap);

    // cout<<pq.find_max(heap)->value<<endl;

    // pq.test();


    return 0;
}