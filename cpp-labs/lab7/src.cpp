#include <cstddef>


template<typename Type>
class Queue {
    Type *data; size_t st, en, cp;

    Queue(): data(nullptr), st(0), en(0), cp(0) { }
    Queue(size_t capacity): data(new Type[capacity]), st(0), en(0), cp(capacity) { } 

    void push()
};


namespace lab7 {
    void runLab7(void) {
    }
}
