#include <iostream>
#include <string>
#include <stdexcept>
#include "vector.h"
#include "list.h"
#include "forward_list.h"
#include "stack.h"
#include "queue.h"
#include "matrix.h"
#include "algorithm.h"

int tests_passed = 0;
int tests_failed = 0;

#define EXPECT_EQ(actual, expected) \
    if ((actual) != (expected)) { \
        std::cerr << "FAIL: Expected " << (expected) << " but got " << (actual) << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
        tests_failed++; \
    } else { tests_passed++; }

#define EXPECT_TRUE(cond) \
    if (!(cond)) { \
        std::cerr << "FAIL: Condition " << #cond << " is false at " << __FILE__ << ":" << __LINE__ << "\n"; \
        tests_failed++; \
    } else { tests_passed++; }

#define EXPECT_FALSE(cond) \
    if (cond) { \
        std::cerr << "FAIL: Condition " << #cond << " is true at " << __FILE__ << ":" << __LINE__ << "\n"; \
        tests_failed++; \
    } else { tests_passed++; }

#define EXPECT_THROWS(expr) \
    { \
        bool threw = false; \
        try { expr; } catch(...) { threw = true; } \
        if (!threw) { \
            std::cerr << "FAIL: Expected exception from " << #expr << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
            tests_failed++; \
        } else { tests_passed++; } \
    }

void test_vector() {
    std::cout << "[Running vector tests...]\n";
    mstd::vector<int> v;
    EXPECT_TRUE(v.isEmpty());
    EXPECT_EQ(v.size(), (size_t)0);

    // Push back and automatic resize
    for (int i = 0; i < 1000; i++) v.push_back(i);
    EXPECT_EQ(v.size(), (size_t)1000);
    EXPECT_EQ(v[500], 500);
    EXPECT_EQ(v.front(), 0);
    EXPECT_EQ(v.back(), 999);

    // Out of bounds
    EXPECT_THROWS(v[1000]);

    // Insert
    v.insert(0, -1);
    EXPECT_EQ(v[0], -1);
    EXPECT_EQ(v[1], 0);
    EXPECT_EQ(v.size(), (size_t)1001);

    v.insert(500, 9999);
    EXPECT_EQ(v[500], 9999);
    EXPECT_EQ(v.size(), (size_t)1002);

    // Remove
    v.remove(0);
    EXPECT_EQ(v[0], 0);
    EXPECT_EQ(v.size(), (size_t)1001);

    // Clear
    v.clear();
    EXPECT_EQ(v.size(), (size_t)0);
    EXPECT_TRUE(v.isEmpty());

    // Deep Copy
    mstd::vector<int> v2;
    v2.push_back(10);
    mstd::vector<int> v3 = v2; // Copy constructor
    v3[0] = 20;
    EXPECT_EQ(v2[0], 10);
    EXPECT_EQ(v3[0], 20);

    v2 = v3; // Assignment operator
    v2[0] = 30;
    EXPECT_EQ(v3[0], 20);
    EXPECT_EQ(v2[0], 30);
}

void test_stack_queue() {
    std::cout << "[Running stack and queue tests...]\n";
    mstd::stack<int> s;
    EXPECT_TRUE(s.isEmpty());
    s.push(1);
    s.push(2);
    EXPECT_EQ(s.front(), 2);
    s.pop();
    EXPECT_EQ(s.front(), 1);
    EXPECT_FALSE(s.isEmpty());
    s.pop();
    EXPECT_TRUE(s.isEmpty());

    mstd::queue<int> q;
    EXPECT_TRUE(q.isEmpty());
    q.push(10);
    q.push(20);
    EXPECT_EQ(q.front(), 10);
    q.pop();
    EXPECT_EQ(q.front(), 20);
    EXPECT_FALSE(q.isEmpty());
    q.pop();
    EXPECT_TRUE(q.isEmpty());
}

void test_matrix() {
    std::cout << "[Running matrix tests...]\n";
    Matrix A(2, 3);
    Matrix B(3, 2);

    // 2x3 matrix
    A(0, 0) = 1; A(0, 1) = 2; A(0, 2) = 3;
    A(1, 0) = 4; A(1, 1) = 5; A(1, 2) = 6;

    // 3x2 matrix
    B(0, 0) = 7; B(0, 1) = 8;
    B(1, 0) = 9; B(1, 1) = 1;
    B(2, 0) = 2; B(2, 1) = 3;

    Matrix C = A * B;
    EXPECT_EQ(C(0, 0), 31);
    EXPECT_EQ(C(0, 1), 19);
    EXPECT_EQ(C(1, 0), 85);
    EXPECT_EQ(C(1, 1), 55);

    Matrix D(2, 2);
    D(0, 0) = 1; D(0, 1) = 1; D(1, 0) = 1; D(1, 1) = 1;

    Matrix E = C + D;
    EXPECT_EQ(E(0, 0), 32);
    EXPECT_EQ(E(0, 1), 20);
    EXPECT_EQ(E(1, 0), 86);
    EXPECT_EQ(E(1, 1), 56);

    // Shape mismatch
    EXPECT_THROWS(A * A);
    EXPECT_THROWS(A + B);

    // Transpose
    Matrix F = A.T();
    EXPECT_EQ(F(0, 1), A(1, 0));
    EXPECT_EQ(F(2, 0), A(0, 2));
}

void test_algorithms() {
    std::cout << "[Running algorithm tests...]\n";
    
    // Binary Search
    mstd::vector<int> sorted_v;
    for (int i = 0; i < 100; i++) sorted_v.push_back(i * 2); // 0, 2, 4, ... 198
    EXPECT_EQ(mstd::binary_search(sorted_v, 50), 25);
    EXPECT_EQ(mstd::binary_search(sorted_v, 0), 0);
    EXPECT_EQ(mstd::binary_search(sorted_v, 198), 99);
    EXPECT_EQ(mstd::binary_search(sorted_v, 99), -1);

    // Insertion Sort
    mstd::vector<int> v_insert;
    v_insert.push_back(5); v_insert.push_back(1); v_insert.push_back(4); v_insert.push_back(2); v_insert.push_back(3);
    mstd::insertion_sort(v_insert);
    EXPECT_EQ(v_insert[0], 1);
    EXPECT_EQ(v_insert[4], 5);

    // Quick Sort Edge Cases: Random, Reverse, Duplicates, Single Element, Empty
    mstd::vector<int> v_quick;
    v_quick.push_back(9); v_quick.push_back(2); v_quick.push_back(7); v_quick.push_back(2); v_quick.push_back(9);
    mstd::quick_sort(v_quick, 0, v_quick.size() - 1);
    EXPECT_EQ(v_quick[0], 2);
    EXPECT_EQ(v_quick[1], 2);
    EXPECT_EQ(v_quick[4], 9);

    mstd::vector<int> v_empty;
    mstd::quick_sort(v_empty, 0, -1); // Should safely return

    mstd::vector<int> v_single;
    v_single.push_back(42);
    mstd::quick_sort(v_single, 0, 0);
    EXPECT_EQ(v_single[0], 42);
}

void test_move_semantics() {
    std::cout << "[Running move semantics tests...]\n";
    mstd::vector<int> v1;
    v1.push_back(42);
    int* original_ptr = &v1[0];

    // Move constructor
    mstd::vector<int> v2(std::move(v1));
    EXPECT_EQ(&v2[0], original_ptr); // The pointer must be exactly the same!
    EXPECT_EQ(v1.size(), (size_t)0);

    // Move assignment
    mstd::vector<int> v3;
    v3 = std::move(v2);
    EXPECT_EQ(&v3[0], original_ptr);
    EXPECT_EQ(v2.size(), (size_t)0);
}

int main() {
    std::cout << "Starting Test Suite for MySTL...\n\n";
    test_vector();
    test_move_semantics();
    test_stack_queue();
    test_matrix();
    test_algorithms();
    
    std::cout << "\n====================================\n";
    std::cout << "Tests Passed: " << tests_passed << "\n";
    std::cout << "Tests Failed: " << tests_failed << "\n";
    std::cout << "====================================\n";

    if (tests_failed > 0) return 1;
    return 0;
}
