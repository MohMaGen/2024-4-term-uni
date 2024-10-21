#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>

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

struct Str {
    char *data;
    size_t len;

    Str(const char* s): data(new char[std::strlen(s)]), len(std::strlen(s)) {
        std::strcpy(data, s); 
    }
    Str(Str& s) {
        data = new char[s.len];
        len = s.len;

        std::memcpy(data, s.data, s.len * sizeof(char));
    }

    Str& operator=(Str& s) {
        data = new char[s.len];
        len = s.len;

        std::memcpy(data, s.data, s.len * sizeof(char));
        return *this;
    }

    Str& operator=(Str&& s) {
        data = s.data;
        len = s.len;
        s.data = nullptr;
        s.len = 0;
        return *this;
    }

    Str(Str&& s) {
        data = s.data;
        len = s.len;
        s.data = nullptr;
        s.len = 0;
    }
    ~Str() {
        delete[] data;
        len = 0;
    }
};

std::ostream& operator<<(std::ostream& os, const Str& str) {
    for (char *el = str.data; el < str.data + str.len; el++) os.put(*el); 
    return os;
}


namespace lab7 {
    void runLab7(void) {
        Queue<Str> data { 10 }; 

        data.push({ "str1" }); 
        data.push({ "str2" }); 
        data.push({ "str3" }); 
        data.push({ "str4" }); 
        data.push({ "str5" }); 


        for (auto el : data) {
            std::cout << "- `" <<  el.data << "`." << std::endl;
        }

        auto el = data.shift();
        printf("remove `%.*s`.\n", (int)el.len, el.data);
        for (auto el : data) {
            std::cout << "- `" <<  el.data << "`." << std::endl;
        }

        while (true) {
            std::cout << "enter\n" <<
                         "    - push <str>\n" <<
                         "    - shift <str>\n" <<
                         "    - empty\n" <<
                         "    - len\n" <<
                         std::endl;

            std::string cmd { 0 };
            std::cout << "lab7> ";
            std::cin >> cmd;

            if (cmd == "push") {
                std::string buf { 0 };
                std::cin >> buf;
                data.push(buf.c_str()); 

            } else if (cmd == "shift") {
                auto elem = data.shift();
                std::cout << "Shifted elem: `" << elem << "`." << std::endl;

            } else if (cmd == "empty") {
                if (data.empty()) 
                    std::cout << "Queue is empty." << std::endl;
                else 
                    std::cout << "Queue isnot empty." << std::endl;

            } else if (cmd == "len") {
                std::cout << "Len of queue is: " << data.len() << std::endl;

            } else {
                std::cout << "Invalid command: " << std::quoted(cmd) << std::endl;
            }

            for (auto el : data) {
                std::cout << "- `" <<  el.data << "`." << std::endl;
            }
        }
    }
}
