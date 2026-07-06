# MySTL

A high-performance, custom-built C++ Standard Template Library (STL) implemented completely from scratch. 

This project was built to deeply understand the low-level memory management, algorithmic complexity, and pointer mechanics that power the real C++ STL. Every data structure is templated, leak-free, and protected by the Rule of Five.

## Data Structures Implemented

### 1. Vector (`mstd::vector`)
A dynamic, contiguous array with automatic resizing.
* Built from a raw `T* data` array.
* $O(1)$ amortized `push_back()`.
* Fully supports Range-Based For Loops (`for auto item : vector`).
* Memory-safe Move Semantics and self-assignment protection.

### 2. Doubly Linked List (`mstd::list`)
A bidirectional linked list.
* Custom `node<T>` struct with `next` and `prev` pointers.
* $O(1)$ `push_front()` and `push_back()`.
* Protected against shallow-copy Double Free Segfaults.

### 3. Singly Linked List (`mstd::forward_list`)
A highly memory-efficient unidirectional list.
* Perfect for Hash Map collision chaining.
* Custom Iterator Wrapper (`mstd::forward_list<T>::iterator`).

### 4. Stack & Queue (`mstd::stack`, `mstd::queue`)
* **Stack**: Built purely on top of `mstd::vector` for $O(1)$ contiguous memory cache hits.
* **Circular Queue**: Built completely from scratch using a raw array and modulo math `(head + 1) % capacity` to achieve true $O(1)$ operations without shifting elements.

### 5. Hash Map (`mstd::unordered_map`)
A lightning-fast, collision-resistant Hash Map.
* **Architecture**: An Array of Singly-Linked Lists of Pairs `mstd::vector<mstd::forward_list<mstd::pair<K, V>>>`.
* Resolves collisions using Forward Lists.
* Implements the `std::hash` fallback (or custom `djb2` strings) mapped safely into buckets using Modulo Array compression `hash % _capacity`.
* Features true C++ STL Lazy Instantiation via `operator[]`.

## Algorithms Implemented
* **Quick Sort**: Recursive Divide-and-Conquer $O(N \log N)$ sorting.
* **Insertion Sort**: In-place fast sorting for nearly sorted arrays.
* **Binary Search**: $O(\log N)$ targeted searching algorithm.

## Compilation & Testing
This project utilizes a `CMake` build system to manage its massive custom test suite.
```bash
mkdir build
cd build
cmake ..
make
./run_tests
```

## Engineering Highlights
* **Zero Memory Leaks:** Every structure utilizes strict Destructors and `clear()` helpers.
* **Rule of Five Compliance:** All complex structures safely implement Deep Copies, Move Semantics, and Assignment protections.
* **Namespace Isolation:** All code is wrapped safely inside the `mstd::` namespace.
