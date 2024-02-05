#include<bits/stdc++.h>
#include "Priority-Queue.hpp"
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

    pq.increase_key(heap, 70, 60);
    pq.print_heap(heap);

    pq.increase_key(heap, 10, -5);
    pq.print_heap(heap);

    pq.increase_key(heap, 50, 12);
    pq.print_heap(heap);

    pq.extract_max(heap);
    pq.print_heap(heap);

    FibHeap *heap2 = pq.make_heap();
    pq.insert(heap2, 100, 100);
    pq.insert(heap2, 200, 200);
    pq.insert(heap2, 300, 300);
    pq.insert(heap2, 400, 400);

    pq.print_heap(heap2);

    pq.extract_max(heap2);

    FibHeap *meldHeap = pq.meld(heap, heap2);
    pq.print_heap(meldHeap);

    pq.extract_max(meldHeap);
    pq.print_heap(meldHeap);

    pq.Delete(meldHeap, 10);
    pq.print_heap(meldHeap);

    cout<<pq.find_max(meldHeap)->key<<endl;

    while(!pq.is_empty(meldHeap))
    {
        pq.extract_max(meldHeap);
        pq.print_heap(meldHeap);
        cout<<endl<<endl;
    }


    // cout<<pq.extract_max(heap)->key<<endl;

    // pq.increase_key(heap, 10, 60);
    // pq.increase_key(heap, 10, 50);

    // pq.Delete(heap, 20);

    // pq.print_heap(heap);

    // pq.Delete(heap, 50);
    // pq.print_heap(heap);
    // cout<<endl<<endl<<endl<<endl<<endl;

    // pq.Delete(heap, 70);
    // pq.print_heap(heap);

    // pq.Delete(heap, 10);
    // pq.print_heap(heap);

    // pq.Delete(heap, 40);
    // pq.print_heap(heap);

    // pq.Delete(heap, 30);
    // pq.print_heap(heap);

    // pq.Delete(heap, 60);
    // pq.print_heap(heap);

    // pq.Delete(heap, 80);
    // pq.print_heap(heap);

    // cout<<pq.find_max(heap)->value<<endl;

    // pq.test();


    return 0;
}