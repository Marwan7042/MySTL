#ifndef M_FORWARAD_LIST_H
#define M_FORWARAD_LIST_H

#include <stdexcept>


namespace mstd {
    template <typename T>
    struct s_node {
        T data;
        s_node *next;
        s_node(T data, s_node *next = nullptr) : data(data), next(next) {}
    };
    
    template <typename T>
    class forward_list {
    private:
        s_node<T> *head;
        s_node<T> *tail;
        size_t _size;
        
        
        
    public:
        class iterator {
        private:
            s_node<T> *curr;
        public:
            iterator(s_node<T> *start_node) : curr(start_node) {}
            T& operator*() { return curr->data; }
            iterator& operator++(){ curr = curr->next; return *this; }
            bool operator!=(const iterator& other) const { return this->curr != other.curr; }
        };
        
        iterator begin() { return iterator(head); }
        iterator end() {return iterator(nullptr); }
        
        forward_list() : head(nullptr), tail(nullptr), _size(0) {}
        
        forward_list(const forward_list& other) : head(nullptr), tail(nullptr), _size(0) {
            s_node<T> *tmp = other.head;
            while (tmp){
                push_back(tmp->data);
                tmp = tmp->next;
            }
        }
        
        forward_list(forward_list&& other) noexcept {
            _size = other._size;
            head = other.head;
            tail = other.tail;
            
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
        }
        
        ~forward_list() {
            clear();
        }
        
        forward_list& operator=(const forward_list& other) {
            if (this == &other) return *this;
            
            clear();
            s_node<T> *tmp = other.head;
            while (tmp){
                push_back(tmp->data);
                tmp = tmp->next;
            }
            return *this;
        }
        
        forward_list& operator=(forward_list&& other) noexcept {
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
            s_node<T> *new_node = new s_node(data, head);
            
            if (!head) tail = new_node;
            head = new_node;
            
            _size++;
        }
        
        
        void push_back(const T& data) {
            s_node<T> *new_node = new s_node(data);
            
            if (!head) {
                head = new_node;
                tail = head;
                _size++;
                return;
            }
            
            tail->next = new_node;
            tail = new_node;
            
            _size++;
        }
        
        void pop_front() {
            if (!head) return;
            
            s_node<T> *tmp = head;
            head = head->next;
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
            
            s_node<T> *tmp = head;
            while(tmp->next != tail) tmp = tmp->next;
            
            delete tail;
            tmp->next = nullptr;
            tail = tmp;
            _size--;
        }
        
        void insert(size_t index, const T& data){
            if (index > _size) throw std::out_of_range("Index out of range.");
            
            if (index == 0) {
                push_front(data); 
                return;    
            } 
            if (index == _size) {  
                push_back(data);  
                return;    
            } 
            
            s_node<T> *new_node = new s_node<T>(data);
            
            s_node<T> *tmp = head;
            for (size_t i = 0; i < index-1; i++)
            tmp = tmp->next;
        
        new_node->next = tmp->next;
        tmp->next = new_node;
        
        _size++;
        }
    
        void remove(size_t index){
            if (index >= _size) throw std::out_of_range("Index out of range."); 
            
            if (index == 0) {
                pop_front(); 
                return;    
            } 
            if (index == _size - 1) { 
                pop_back();  
                return;    
            } 
            
            s_node<T> *tmp = head;
            for (size_t i = 0; i < index-1; i++)
            tmp = tmp->next;
        
        s_node<T> *removed = tmp->next;
        tmp->next = removed->next;
        delete removed;
        
        _size--;
        }

        void clear() {
            _size = 0;
            while (head) {
                s_node<T> *tmp = head;
                head = head->next;
                delete tmp;
            }
            tail = nullptr;
        }
        size_t getSize() const {return _size;}
        bool isEmpty() const {return head == nullptr;}
        T& front() {return head->data;}
        T& back() {return tail->data;}
    };
}

#endif