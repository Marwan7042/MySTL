#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <string>
#include <stdexcept>
#include <functional>
#include "vector.h"
#include "forward_list.h"
#include "pair.h"

namespace mstd {
    template <typename K, typename V>
    class unordered_map{
    private:
        mstd::vector<mstd::forward_list<mstd::pair<K, V>>> table;
        size_t _size;
        size_t _capacity;

        size_t hash(const K& key) const {
            // Let the STL figure out the math for hashing.
            size_t hash_value = std::hash<K>{}(key);
            return hash_value % _capacity; 
        }

    public:
        unordered_map(size_t cap = 16) : _capacity(cap), _size(0), table(cap) {}
        ~unordered_map() {}
        
        V& operator[](const K& key) {
            size_t index = hash(key);
            mstd::forward_list<mstd::pair<K, V>>& bucket = table[index];

            for (auto it = bucket.begin(); it != bucket.end(); ++it){
                if ((*it).first == key) return (*it).second;
            }

            V blank_value = V();
            bucket.push_front(mstd::pair<K, V>(key, blank_value));
            _size++;

            return bucket.front().second;
        }

        void insert(const K& key, const V& value) {
            size_t index = hash(key);
            mstd::forward_list<mstd::pair<K, V>>& bucket = table[index];

            for (auto it = bucket.begin(); it != bucket.end(); ++it) {
                if ((*it).first == key) {
                    (*it).second = value;
                    return;
                }
            }
            mstd::pair<K, V> data(key, value);
            bucket.push_front(data);

            _size++;
        }

        bool contains(const K& key) {
            size_t index = hash(key);
            mstd::forward_list<mstd::pair<K, V>>& bucket = table[index];

            for (auto it = bucket.begin(); it != bucket.end(); ++it){
                if ((*it).first == key) return true;
            }
            return false;
        }

        void remove(const K& key) {                                                                                                                                              
            size_t index = hash(key);                                                                                                                                            
            mstd::forward_list<mstd::pair<K, V>>& bucket = table[index];                                                                                                         
                                                                                                                                                                                    
            size_t list_index = 0;
            for (auto it = bucket.begin(); it != bucket.end(); ++it) {                                                                                                           
                if ((*it).first == key) {
                    bucket.remove(list_index); // Use your list's built-in remove!
                    _size--;                   // Decrease the total Hash Map size
                    return;
                }
            list_index++;
            }
        }

        void clear() {
            for (auto& bucket : table) {
                bucket.clear();
            }
            table.clear();
            _size = 0;
        }
        size_t size() { return _size; }
        bool isEmpty() { return !_size; }
    };
}
    
#endif