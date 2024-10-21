#ifndef lab7_hpp_INCLUDED
#define lab7_hpp_INCLUDED

#include <algorithm>
#include <cstddef>
#include <cstdlib>
namespace lab7 {
    void runLab7(void);

    template<typename Type>
    class Queue {
        Type *_data; size_t _start, _end, _capacity;

        public:
            Queue(): _data(nullptr), _start(0), _end(0), _capacity(0) { }
            Queue(size_t capacity): _data((Type*)std::malloc(sizeof(Type) * capacity)), _start(0), _end(0), _capacity(capacity) { }

            ~Queue() { delete _data; }

            /*
             * Push vector to the queue.
             */
            void push(Type value) {
                if (_end >= _capacity) {
                    ++_capacity *= 2;
                    _data = (Type*)std::realloc(_data, sizeof(Type) * _capacity);
               }
                _data[_end++] = std::move(value); 
            }

    		/*
             * Delete front elemnt of queue.
             */
            void pop(void) {
                if (_end == _start) return;
                _start++;
            }

            /*
             * Return front element and pop queue. (Elem moved no copy).
             */
            Type shift(void) {
                Type el = front();
                pop();
                return std::move(el);
            }

            /*
             * Return len of the queue.
             */
            size_t len(void) {
                return _end - _start;
            }

            Type front(void) {
                return _data[_start];
            }

            bool empty(void) {
                return len() == 0;
            }

            struct Iterator
            {
                using iterator_category = std::forward_iterator_tag;
                using difference_type   = std::ptrdiff_t;
                using value_type        = Type;
                using pointer           = Type*;
                using reference         = Type&;


                Iterator(pointer ptr) : _ptr(ptr) { }

                reference operator*() const { return *_ptr; }
                pointer operator->() { return _ptr; }

                Iterator& operator++() { _ptr++; return *this; }  

                Iterator operator++(int) { Iterator tp = *this; ++(*this); return tp; }

                friend bool operator== (const Iterator& a, const Iterator& b) { return a._ptr == b._ptr; };
                friend bool operator!= (const Iterator& a, const Iterator& b) { return a._ptr != b._ptr; };

                private:
                    pointer _ptr;

            };
            Iterator begin(void) { return Iterator(_data + _start); }
            Iterator end(void) { return Iterator(_data + _end); }
    };
}

#endif // lab7_hpp_INCLUDED
