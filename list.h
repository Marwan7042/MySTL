#ifndef M_LIST_H
#define M_LIST_H

#include <stdexcept>


namespace mstd {
    template <typename T>
    struct node {
        T data;
        node *next;
        node *prev;
        node(T data, node *next=nullptr, node *prev=nullptr) : data(data), next(next), prev(prev) {}
    };
    
    template <typename T>
    class list {
    private:
        node<T> *head;
        node<T> *tail;
        size_t _size;

        
        public:
        list() : head(nullptr), tail(nullptr), _size(0) {}
        
        list(const list& other) : head(nullptr), tail(nullptr), _size(0) {
            node<T> *tmp = other.head;
            while (tmp){
                push_back(tmp->data);
                tmp = tmp->next;
            }
        }
        
        list(list&& other) noexcept{
            _size = other._size;
            head = other.head;
            tail = other.tail;

            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }

        ~list() {
            _size = 0;
            while (head){
                node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
        }
        
        list& operator=(const list& other){
            if (this == &other) return *this;
            
            clear();
            node<T> *tmp = other.head;
            while (tmp){
                push_back(tmp->data);
                tmp = tmp->next;
            }
            return *this;
        }

        list& operator=(list&& other) noexcept {
            if (this == &other) return *this;
            
            clear();
            _size = other._size;
            head = other.head;
            tail = other.tail;
            
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
            
            return *this;
        }
        
        void push_front(const T& data) {
            node<T> *new_node = new node(data, head);
            
            if (!head) tail = new_node;
            else head->prev = new_node;
            
            head = new_node;
            _size++;
        }
        
        
        void push_back(const T& data) {
            node<T> *new_node = new node(data);
            
            if (!head) {
                head = new_node;
                tail = head;
                _size++;
                return;
            }
            
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
            
            _size++;
        }

        void pop_front() {
            if (!head) return;
            
            node<T> *tmp = head;
            
            head = head->next;
            if (head) head->prev = nullptr;
            
            delete tmp;
            
            _size--;
            
            if (!head) tail = nullptr;
        }
        
        void pop_back() {
            if (!head) return;
            if (_size == 1) {
                pop_front();
                return;
            }
            
            node<T> *tmp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            
            delete tmp;
            _size--;
        }
        
        void insert(size_t index, const T& data){
            if (index > _size) throw std::out_of_range("Index out of range.");
            
            if (index == 0) {
                push_front(data); 
                return;    
            } 
            if (index == size) {  
                push_back(data);  
                return;    
            } 
            
            node<T> *new_node = new node<T>(data);
            
            node<T> *tmp = head;
            for (size_t i = 0; i < index-1; i++)
                tmp = tmp->next;

            new_node->next = tmp->next;
            new_node->prev = tmp;
            tmp->next->prev = new_node;
            tmp->next = new_node;
            
            _size++;
        }
        
        void remove(size_t index){
            if (index >= _size) throw std::out_of_range("Index out of range."); 
            
            if (index == 0) {
                pop_front(); 
                return;    
            } 
            if (index == size - 1) { 
                pop_back();  
                return;    
            } 
            
            node<T> *tmp = head;
            for (size_t i = 0; i < index-1; i++)
            tmp = tmp->next;
        
        node<T> *removed = tmp->next;
        tmp->next = removed->next;
        tmp->next->prev = tmp;
        delete removed;
        
        _size--;
    }
    
    void clear() {
        _size = 0;
        while (head) {
            node<T> *tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
    }
    
    size_t size() const {return _size;}
    bool isEmpty() const {return head == nullptr;}
    T& front() {return head->data;}
    T& back() {return tail->data;}
    };
}

#endif