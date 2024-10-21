#include <cstdio>
#include <cstring>
#include <iomanip>
#include <lab7.hpp>
#include <iostream>

namespace lab7 {
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
