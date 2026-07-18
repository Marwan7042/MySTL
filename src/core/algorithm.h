#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "vector.h"

namespace mstd {
    template <typename T>                                                                                                                                                        
    void swap(T& a, T& b) {                                                                                                                                                      
        T temp = a;                                                                                                                                                              
        a = b;                                                                                                                                                                   
        b = temp;                                                                                                                                                                
    }      

    template <typename T>
    int binary_search(const mstd::vector<T>& v, const T& target) {
        int low = 0, high = v.size() - 1;

        while (low <= high) {
            long long mid = low + (high - low) / 2;
            if (v[mid] == target) return mid;
            else if (v[mid] < target) low = mid + 1;
            else high = mid - 1;
        }
        return -1;
    }

    template <typename T>
    void insertion_sort(mstd::vector<T>& v) {
        for (int i = 0; i < v.size(); i++) {
            T key = v[i];
            int j = i - 1;
            while (j >= 0 && v[j] > key){
                v[j+1] = v[j];
                j--;
            }
            v[j+1] = key;
        }
    }   

    template <typename T>
    int partition(mstd::vector<T>& v, int low, int high) {
        T pivot = v[high];
        int i = low - 1;

        for (int j = low; j < high; j++){
            if (v[j] < pivot) { 
                i++;
                swap(v[i], v[j]);
            } 
        }
        i++;
        swap(v[i], v[high]);

        return i;
    }

    template <typename T>
    void quick_sort(mstd::vector<T>& v, int low, int high) {
        if (high <= low) return;
        int pivot = partition(v, low, high);
        quick_sort(v, low, pivot-1);
        quick_sort(v, pivot+1, high);
    }
}

#endif