#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iterator>

template<typename Type>
class Queue {
    Type *_data; size_t _st, _en, _cp;

    public:
        Queue(): _data(nullptr), _st(0), _en(0), _cp(0) { }
        Queue(size_t capacity): _data((Type*)std::malloc(sizeof(Type) * capacity)), _st(0), _en(0), _cp(capacity) { } 
        ~Queue() { delete _data; }

        void push(Type value) {
            if (_en >= _cp) {
                ++_cp *= 2;
                Type *data = (Type*)std::malloc(sizeof(Type) * _cp);
                for (size_t i = _st; i < _en; i++) data[i - _st] = _data[i];
                delete _data;
                _data = data;
            }
            _data[_en++] = value; 
        }

        void pop(void) {
            if (_en == _st) return;
            _st++;
        }

        size_t len(void) {
            return _en - _st;
        }

        Type front(void) {
            return _data[_st];
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
        Iterator begin(void) { return Iterator(_data + _st); }
        Iterator end(void) { return Iterator(_data + _en); }
};


namespace lab7 {
    void runLab7(void) {
        struct str {
            char *data;
            size_t len;

            str(const char* s): data(new char[std::strlen(s)]), len(std::strlen(s)) {
                std::strcpy(data, s); 
            }
        };
        Queue<str> data { 10 }; 

        data.push({ "str1" }); 
        data.push({ "str2" }); 
        data.push({ "str3" }); 
        data.push({ "str4" }); 
        data.push({ "str5" }); 

        for (auto el : data) {
            printf("- `%.*s`.\n", (int)el.len, el.data);
        }

        printf("remove `%.*s`.\n", (int)data.front().len, data.front().data);
        data.pop();
        for (auto el : data) {
            printf("- `%.*s`\n", (int)el.len, el.data);
        }
    }
}
