# <font color = "grgreen"> Fibonacci Heap Operations</font>

## <font color = "cyan">1. make_heap()</font>
   - Initializes an empty Fibonacci Heap and returns a reference.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">2. is_empty(heap)</font>
   - Takes the Fibonacci Heap as input and returns True if the heap is empty, otherwise False.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">3. insert(heap, key, value)</font>
   - Inserts a new element with the given key and value into the Fibonacci Heap.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">4. extract_max(heap)</font>
   - Extracts and returns the element with the maximum key from the Fibonacci Heap.
   - Runs in `O(log n)` amortized time complexity.

## <font color = "cyan">5. increase_key(heap, value, new_key)</font>
   - Increases the key of the specified node of the given value to the new key.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">6. delete(heap, value)</font>
   - Deletes the specified node of the given value from the Fibonacci Heap.
   - Runs in `O(log n)` amortized time complexity.

## <font color = "cyan">7. meld(heap1, heap2)</font>
   - Melds two Fibonacci Heaps into one and returns it.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">8. find_max(heap)</font>
   - Returns the maximum element in the Fibonacci Heap without extracting it.
   - Runs in `O(1)` amortized time complexity.

## <font color = "cyan">9. print(heap)</font>
   - Prints the given heap in a specified format.
   - Output explanation is provided within the function description.

   <font color="red">**Test Case:**</font>
   ```python
   heap = FibonacciHeap()
   heap.insert(55, 3)
   heap.insert(45, 5)
   heap.insert(32, 4)
   heap.insert(7, 8)
   heap.insert(24, 7)
   heap.insert(5, 10)
   heap.print()

Tree 1: (55, 3) -> (45, 5), (32, 4)
(45, 5) -> (7, 8)
Tree 2: (24, 7) -> (5, 10)
   ``````


## <font color = "cyan">10. test()</font>
   - Tests all the functionalities of the implemented priority queue for all possible scenarios.
   - Prints <font color="grgreen">"passed"</font> if all test cases are passed, otherwise prints <font color=" red">"not passed"</font>.



