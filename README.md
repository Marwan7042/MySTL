# MySTL

A high-performance, custom-built C++ Standard Template Library (STL) implemented completely from scratch. 

This project was built to deeply understand the low-level memory management, algorithmic complexity, and pointer mechanics that power the real C++ STL. Every data structure is templated, leak-free, and protected by the Rule of Five.

## CPU Cache & Performance Optimizations
A primary focus of this library is **Cache Locality**. Modern CPUs read memory in blocks (cache lines), making contiguous memory significantly faster than scattered pointers.

* **Stack & Queue**: Instead of using Linked Lists, the `mstd::stack` is built entirely on top of `mstd::vector` for perfect spatial locality. The `mstd::queue` is engineered as a mathematically complex **Circular Buffer** over a raw array, achieving $O(1)$ push/pop while guaranteeing zero cache misses.
* **1D Flattened Matrix**: The custom `Matrix` class completely abandons the traditional `vector<vector<float>>` (Array of Pointers) approach. Instead, it utilizes a flattened 1D `mstd::vector<float>` and maps 2D coordinates `(i, j)` to 1D physical RAM using `(i * cols) + j`. This guarantees that rows are perfectly contiguous in memory, drastically accelerating hardware-level prefetching during Matrix Multiplication.

## Data Structures Implemented

### 1. Vector (`mstd::vector`)
A dynamic, contiguous array with automatic resizing.
* Built from a raw `T* data` array.
* $O(1)$ amortized `push_back()`.
* Fully supports Range-Based For Loops (`for auto item : vector`).
* Memory-safe Move Semantics and self-assignment protection.

### 2. Matrix (`mstd::Matrix`)
A highly optimized, cache-friendly linear algebra structure.
* Flattened 1D underlying memory layout.
* Implements core operations: Addition (`operator+`), Multiplication (`operator*`), and Transposition (`.T()`).
* Safe bounds-checking and overloaded functor access (`operator()(i, j)`).

### 3. Hash Map (`mstd::unordered_map`)
A lightning-fast, collision-resistant Hash Map.
* **Architecture**: An Array of Singly-Linked Lists of Pairs `mstd::vector<mstd::forward_list<mstd::pair<K, V>>>`.
* Resolves collisions using Forward Lists.
* Implements the `std::hash` fallback mapped safely into buckets using Modulo Array compression `hash % _capacity`.
* Features true C++ STL Lazy Instantiation via `operator[]`.

### 4. Stack & Queue (`mstd::stack`, `mstd::queue`)
* **Stack**: Vector-backed LIFO architecture.
* **Circular Queue**: Array-backed FIFO architecture utilizing `(head + 1) % capacity` wrap-around pointers.

### 5. Linked Lists (`mstd::list`, `mstd::forward_list`)
* **Doubly Linked List**: Bidirectional nodes with $O(1)$ `push_front` and `push_back`.
* **Singly Linked List**: Unidirectional memory-efficient nodes featuring a custom Iterator Wrapper (`mstd::forward_list<T>::iterator`).

## Algorithms Implemented
* **Quick Sort**: Recursive Divide-and-Conquer $O(N \log N)$ sorting.
* **Insertion Sort**: In-place fast sorting for nearly sorted arrays.
* **Binary Search**: $O(\log N)$ targeted searching algorithm.

## Compilation & Testing
This project utilizes a `CMake` build system to manage its custom test suite.
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
* **Namespace Isolation:** All core data structures are wrapped safely inside the `mstd::` namespace.
