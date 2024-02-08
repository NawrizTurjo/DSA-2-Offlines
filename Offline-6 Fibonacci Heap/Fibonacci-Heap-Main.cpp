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
    while(!pq.is_empty(heap))
    {
        pq.extract_max(heap);
        pq.print_heap(heap);
        cout<<endl<<endl;
    }
    // cout<<"done"<<endl;

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

    // FibHeap *heap = pq.make_heap();
    // for(int i=1;i<=16;i++)
    // {
    //     pq.insert(heap, i, i);
    // }
    // pq.print_heap(heap);

    // pq.extract_max(heap);
    // pq.print_heap(heap);

    // pq.increase_key(heap, 1,8);
    // pq.print_heap(heap);

    // pq.increase_key(heap,3,13);
    // pq.print_heap(heap);

    // pq.increase_key(heap, 5,14);
    // pq.print_heap(heap);

    // pq.increase_key(heap, 2,12);
    // pq.print_heap(heap);

    // pq.Delete(heap,2);
    // pq.print_heap(heap);

    // FibHeap *heap2 = pq.make_heap();
    // for(int i=1;i<=18;i++)
    // {
    //     pq.insert(heap2, i+16, i+16);
    // }
    // pq.print_heap(heap2);

    // pq.extract_max(heap2);
    // pq.print_heap(heap2);

    // pq.extract_max(heap2);
    // pq.print_heap(heap2);

    // pq.extract_max(heap2);
    // pq.print_heap(heap2);

    // pq.extract_max(heap2);
    // pq.print_heap(heap2);

    // pq.extract_max(heap2);
    // pq.print_heap(heap2);

    // pq.Delete(heap2,24);
    // pq.print_heap(heap2);

    // FibHeap *meldHeap = pq.meld(heap, heap2);
    // pq.print_heap(meldHeap);

    // pq.Delete(meldHeap, 4);
    // pq.print_heap(meldHeap);

    // pq.Delete(meldHeap, 11);
    // pq.print_heap(meldHeap);

    // pq.Delete(meldHeap, 10);
    // pq.print_heap(meldHeap);

    // pq.is_empty(meldHeap) ? cout<<"Empty"<<endl : cout<<"Not Empty"<<endl;

    // Node *maxNode = pq.find_max(meldHeap);
    // cout<<"maxNode= { \"Key\": "<<maxNode->key<<", \"value\":"<<maxNode->value<<" }"<<endl;




    // while(!(pq.is_empty(heap)))
    // {
    //     pq.extract_max(heap);
    //     pq.print_heap(heap);
    //     cout<<endl<<endl;
    // }

    // pq.insert(heap, 1, 1);
    // pq.print_heap(heap);
    // pq.insert(heap, 2, 2);
    // pq.print_heap(heap);

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

    // pq.test();

    // pq.test();

    // FibHeap *heap = pq.make_heap();
    // for(int i=1;i<=16;i++)
    // {
    //     pq.insert(heap, i, i);
    // }
    // FibHeap *heap2 = pq.make_heap();
    // for(int i=1;i<=18;i++)
    // {
    //     pq.insert(heap2, i+16, i+16);
    // }

    // FibHeap *meldHeap = pq.meld(heap, heap2);
    // pq.print_heap(meldHeap);
    // while(!(pq.is_empty(meldHeap)))
    // {
    //     pq.extract_max(meldHeap);
    //     pq.print_heap(meldHeap);
    //     cout<<endl<<endl;
    // }

    // FibHeap *heap = pq.make_heap();
    // for(int i=1;i<=5;i++)
    // {
    //     pq.insert(heap, i, i);
    // }
    // FibHeap *heap2 = pq.make_heap();
    // for(int i=6;i<=10;i++)
    // {
    //     pq.insert(heap2, i, i);
    // }

    // FibHeap *meldHeap = pq.meld(heap, heap2);
    // pq.print_heap(meldHeap);
    // while(!(pq.is_empty(meldHeap)))
    // {
    //     pq.print_heap(meldHeap);
    //     pq.extract_max(meldHeap);
    //     cout<<endl<<endl;
    // }


    pq.test();


    return 0;
}