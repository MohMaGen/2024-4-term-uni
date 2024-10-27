#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <functional>
#include <iostream>
#include <lab7.hpp>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

namespace lab8 {
    template<typename Type>
    struct Maybe {
        enum { Just=0, Nothing } variant;
        union { Type just; bool _; };

        Maybe(): variant(Nothing), _(false) {}
        Maybe(Type value): variant(Just), just(value) {}

        constexpr bool hasSome() const noexcept { return variant != Nothing; }
        explicit operator bool() { return hasSome(); }

        const Type& operator*() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        Type& operator*() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        const Type* operator->() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }

        Type* operator->() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }
    };


    class Customer {
        public:
            enum CustomerType { Junior=0, Middle, Senior } type;
            size_t time_to_serve;

            Customer() = delete;
            static Maybe<Customer> Generate() {
                double chance = (double)std::rand() / (double)RAND_MAX;

                if (chance < 0.05) return { Customer{ Junior, (size_t)std::rand()%5+5 } };
                if (chance < 0.45) return { Customer{ Middle, (size_t)std::rand()%3+2 } };
                if (chance < 0.75) return { Customer{ Senior, (size_t)std::rand()%2+7 } };

                return { };
            }
            Customer(CustomerType type, size_t time_to_serve): type{ type }, time_to_serve(time_to_serve) {}
    };

    std::ostream& operator<<(std::ostream& os, Customer customer) {
        switch (customer.type) {
        case Customer::Junior: os << "Junior"; break;
        case Customer::Middle: os << "Middle"; break;
        case Customer::Senior: os << "Senior"; break;
        }

        return os << " " << customer.time_to_serve << "min";
    }

    class Window {
        Maybe<Customer> _customer;
        size_t serving_time = 0;
        public:
            void tick(void) {
                if (!_customer) return;

                serving_time++;
                if (serving_time >= _customer->time_to_serve) {
                    _customer = { };
                    serving_time = 0;
                }
            }

            const Maybe<Customer>& getCustomer(void) const noexcept {
                return _customer;
            } 

            bool hasCustomer(void) const noexcept {
                return _customer.hasSome();
            }
        friend std::ostream& operator<<(std::ostream& os, const Window &window);
    };
    std::ostream& operator<<(std::ostream& os, const Window &window) {
        os << "Window `" << window.serving_time << "` ";

        if (window._customer.hasSome()) {
            os << "customer: `" << *window._customer << "`";
        } else {
            os << "no customer";
        }

        return os;
    }

    class Institution {
        lab7::Queue<Customer> _e_queue { 10 }, _l_queue { 10 };
        std::vector<Window> _windows { 3 }; 

        size_t _inst_time = 0;
        size_t _time_to_next_cutomer_wave = 0;

        void _new_customers() {
            for (size_t i = 0; i < 3; i++) {
                auto customer = Customer::Generate();
                if (!customer) continue;


                double chance = (double)std::rand() / (double)RAND_MAX;

                switch (customer->type) {
                case Customer::Junior: {
                    if (chance <= 0.2)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Middle: {
                    if (chance <= 0.7)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Senior: {
                    if (chance <= 0.05)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                }
            }

        }

        void _update() {
            if (_time_to_next_cutomer_wave == 0) {
                _new_customers();
                _time_to_next_cutomer_wave = 5;
            }
        }


        void _display() {
            std::cout << "E queue:";
            for (auto customer : _e_queue) {
                std::cout << " " << customer;
            }
            std::cout << std::endl;

            std::cout << "Live queue:";
            for (auto customer : _l_queue) {
                std::cout << " " << customer;
            }
            std::cout << std::endl;
        }


        public:
            Institution() { }
            Institution(size_t windows_count): _windows(windows_count)  { } 

            const std::vector<Window>& getWindows(void) const noexcept {
                return _windows;
            }

            const lab7::Queue<Customer> getLiveQueue(void) const noexcept {
                return _l_queue;
            } 

            const lab7::Queue<Customer> getEQueue(void) const noexcept {
                return _e_queue;
            } 

            void tick() {
                _update();

                _display();

                _time_to_next_cutomer_wave--;
                _inst_time++;
            }
    };

    std::string getSocketPath(size_t pid) {
        return "/tmp/cpp_labs-lab8-" + std::to_string(pid);
    }

    enum class MessageVariant: char {
        GET_E_QUEUE=0,
        GET_L_QUEUE,
        GET_WINDOWS,
        TICK,
        CLOSE,
    };

    enum class ResponseVariant: char {
        OK=0,
        WINDOWS,
        CUSTOMERS,

        ERR=-1,
    };

    class Connection {
        Institution &institution;
        std::mutex &institutioin_mutex;
        int data_socket;
        bool should_close = false;

        public:
            Connection(Institution& institution, std::mutex &institutioin_mutex, int data_socket):
                institution(institution), institutioin_mutex(institutioin_mutex), data_socket(data_socket) {}

            void tick_msg(char *buffer) {
                std::cout << "Request for tick:" << std::endl;

                std::lock_guard<std::mutex> guard(institutioin_mutex); 
                institution.tick();

                buffer[0] = (char)ResponseVariant::OK;

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");

                std::cout << "  : ok" << std::endl;
            }

            void get_l_queue_msg(char *buffer) {
                const auto live_queue = [&]{
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    buffer[0] = (char)ResponseVariant::OK;
                    return institution.getWindows();
                }();

                buffer[0] = (char)ResponseVariant::CUSTOMERS;

                buffer[1] = (unsigned char)live_queue.size();

                size_t idx = 2;
                for (auto customer : live_queue) {
                    std::memcpy(buffer+idx, &customer, sizeof(customer));
                    idx += sizeof(customer);
                }

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");
            }

            void get_e_queue_msg(char *buffer) {
                const auto e_queue = [&]{
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    buffer[0] = (char)ResponseVariant::OK;
                    return institution.getWindows();
                }();

                buffer[0] = (char)ResponseVariant::CUSTOMERS;

                buffer[1] = (unsigned char)e_queue.size();

                size_t idx = 2;
                for (auto customer : e_queue) {
                    std::memcpy(buffer+idx, &customer, sizeof(customer));
                    idx += sizeof(customer);
                }

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");
            }

            void get_windows_msg(char *buffer) {
                const auto &windows = [&]{
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    return institution.getWindows();
                }();
                std::cout << "Request for windows:" << std::endl;

                if (windows.size() > 0xFF)
                    throw std::runtime_error("Windows size too huge.");

                std::cout << "  : size: `" << windows.size() << "'" << std::endl;

                buffer[0] = (char)ResponseVariant::WINDOWS;

                buffer[1] = (unsigned char)windows.size();

                size_t idx = 2;
                for (const auto window: windows) {
                    std::cout << "  : window '" << window << "'" << std::endl;

                    std::memcpy(buffer+idx, &window, sizeof(window));
                    idx += sizeof(window);
                }

                if (write(data_socket, buffer, idx) == -1)
                    throw std::runtime_error("Failed to write data socket.");

            }

            void close_msg(char *buffer) {
                std::cout << "Request for end:" << std::endl;
                buffer[0] = (char)ResponseVariant::OK;

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");

                should_close = true;

                std::cout << "  : ok" << std::endl;
            }

            void operator()() {
                char buffer[0x100];

                std::function<void (void)> jmp_table[] = {
                    [&buffer, this](){ this->get_e_queue_msg(buffer); },
                    [&buffer, this](){ this->get_l_queue_msg(buffer); },
                    [&buffer, this](){ this->get_windows_msg(buffer); },
                    [&buffer, this](){ this->tick_msg(buffer); },
                    [&buffer, this](){ this->close_msg(buffer); },
                };

                while (!should_close) {
                    try {
                        long ret = read(data_socket, buffer, sizeof(buffer));
                        if (ret == -1) throw std::runtime_error("Failed read from data socket.");
                        if (ret == 0) throw std::runtime_error("Empty message.");

                        char msg = buffer[0];
                        if (msg < 0 || msg > (char)MessageVariant::CLOSE)
                            throw std::runtime_error("Invalid command.");

                        jmp_table[(size_t)msg]();

                    } catch (std::exception& e) {
                        std::cout << "Connection Failed: `" << e.what() << "`." << std::endl;
                        break;
                    }
                }
                close(data_socket);
            }

    };


    void server(void) {
        Institution institution { 3 };
        std::mutex institutioin_mutex;

        size_t pid = getpid();
        std::cout << "Server PID: `" << pid << "`.\n";

        int connection_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
        if (connection_socket == -1) throw std::runtime_error("Failed to create socket"); 

        struct sockaddr_un name;
        std::memset(&name, 0, sizeof(name));
        name.sun_family = AF_UNIX;
        std::strcpy(name.sun_path, getSocketPath(pid).c_str());


        if (bind(connection_socket, (struct sockaddr*)&name, sizeof(name)) < 0) {
            throw std::runtime_error("Failed to bind connection socket.");
        }
        listen(connection_socket, 0);

        std::vector<std::thread> threads;
        while (true) {
            if (int data_socket = accept(connection_socket, NULL, NULL); data_socket > 0)
                threads.push_back(std::thread(Connection(institution, institutioin_mutex, data_socket)));
        }

        for (auto &thread : threads) {
            thread.join();
        }

        close(connection_socket);
        unlink(getSocketPath(pid).c_str()); 

    }

    void client(void) {
        while (true) {
            size_t pid = 0;
            std::cout << "Enter server's PID: ";
            std::cin >> pid;
            std::cout << "Server socket at: `" << getSocketPath(pid) << "`\n"; 

            struct sockaddr_un server_addr;
            std::memset(&server_addr, 0, sizeof(server_addr));
            server_addr.sun_family = AF_UNIX;
            std::strcpy(server_addr.sun_path, getSocketPath(pid).c_str());

            int data_socket = socket(AF_UNIX, SOCK_SEQPACKET, 0);
            if (connect(data_socket, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
                std::cout << "Failed to connect to the server." << std::endl;
              	continue;
            }

            char data[0x100] = { '\0' };

            const char HELP_MSG[] = "\n"
                " - help        -- prints this message.\n"
                " - close/c		-- close connection.\n"
                " - tick/t		-- tick.\n"
                " - windows/w   -- prints all windows.\n"
                " - e_queue/e   -- prints e queue.\n"
                " - l_queue/l   -- prints live queue.\n";

            std::cout << HELP_MSG << std::endl;;
            while (true) {
                std::string cmd { };
                std::cout << "lab8 client> ";
                std::cin >> cmd;

                if (cmd == "help") {
                    std::cout << HELP_MSG << std::endl;

                } else if (cmd == "c" || cmd == "close") {
                    std::cout << "closing..." << std::endl;
                    break;

                }  else if (cmd == "tick" || cmd == "t") {
                    data[0] = (char)MessageVariant::TICK;

                    if (write(data_socket, data, 1) < 0) {
                        std::cout << "Failed to write to the server!" << std::endl;
                        continue;
                    } 
                    if (int len = read(data_socket, data, 0x100); len > 0) {
                        auto response_variant =  ResponseVariant(data[0]);

                        if (response_variant == ResponseVariant::ERR) {
                            std::cout << "Response an error message" << std::endl;
                            continue;
                        } 

                        if (response_variant != ResponseVariant::OK) {
                            std::cout << "Get wront response message!" << std::endl;
                            continue;
                        }

                        if (response_variant == ResponseVariant::OK) {
                            std::cout << "No problems" << std::endl;
                        }
                    }

                } else if (cmd == "w" || cmd == "windows") {
                    data[0] = (char)MessageVariant::GET_WINDOWS;

                    if (write(data_socket, data, 1) < 0) {
                        std::cout << "Failed to write to the server!" << std::endl;
                        continue;
                    } 

                    if (int len = read(data_socket, data, 0x100); len > 0) {
                        std::cout << "Bytes: ";
                        for (size_t i = 0; i < len; i++) {
                            printf("%.2X ", data[i]); 
                        }
                        std::cout << std::endl;

                        auto response_variant =  ResponseVariant(data[0]);

                        if (response_variant == ResponseVariant::ERR) {
                            std::cout << "Response an error message" << std::endl;
                            continue;
                        } 
                        if (response_variant != ResponseVariant::WINDOWS) {
                            std::cout << "Get wront response message!" << std::endl;
                            continue;
                        }

                        size_t windows_size = (size_t)data[1];
                        std::cout << "Windows count: `" << windows_size << "`." << std::endl;
                        size_t offset = 2;
                        for (size_t i = 0; i < windows_size; i++) {
                            Window *window = (Window*)(data + offset);
                            std::cout << " <=> window: " << *window  << std::endl;
                        }

                    } else {
                        std::cout << "Failed to read from the server!" << std::endl;
                    }
                } else if (cmd == "e" || cmd == "e_queue") {
                    data[0] = (char)MessageVariant::GET_E_QUEUE;

                    if (write(data_socket, data, 1) < 0) {
                        std::cout << "Failed to write to the server!" << std::endl;
                        continue;
                    } 

                    if (int len = read(data_socket, data, 0x100); len > 0) {
                        std::cout << "Bytes: ";
                        for (size_t i = 0; i < len; i++) {
                            printf("%.2X ", data[i]); 
                        }
                        std::cout << std::endl;

                        auto response_variant =  ResponseVariant(data[0]);

                        if (response_variant == ResponseVariant::ERR) {
                            std::cout << "Response an error message" << std::endl;
                            continue;
                        } 
                        if (response_variant != ResponseVariant::CUSTOMERS) {
                            std::cout << "Get wront response message!" << std::endl;
                            continue;
                        }

                        size_t customers_count = (size_t)data[1];
                        std::cout << "customers count: `" << customers_count << "`." << std::endl;
                        size_t offset = 2;

                        for (size_t i = 0; i < customers_count; i++) {
                            Customer *customer = (Customer*)(data + offset);
                            std::cout << " <=> customer: " << *customer  << std::endl;
                        }

                    } else {
                        std::cout << "Failed to read from the server!" << std::endl;
                    }
                } else if (cmd == "l" || cmd == "l_queue") {
                    data[0] = (char)MessageVariant::GET_L_QUEUE;

                    if (write(data_socket, data, 1) < 0) {
                        std::cout << "Failed to write to the server!" << std::endl;
                        continue;
                    } 

                    if (int len = read(data_socket, data, 0x100); len > 0) {
                        std::cout << "Bytes: ";
                        for (size_t i = 0; i < len; i++) {
                            printf("%.2X ", data[i]); 
                        }
                        std::cout << std::endl;

                        auto response_variant =  ResponseVariant(data[0]);

                        if (response_variant == ResponseVariant::ERR) {
                            std::cout << "Response an error message" << std::endl;
                            continue;
                        } 
                        if (response_variant != ResponseVariant::CUSTOMERS) {
                            std::cout << "Get wront response message!" << std::endl;
                            continue;
                        }

                        size_t customers_count = (size_t)data[1];
                        std::cout << "customers count: `" << customers_count << "`." << std::endl;
                        size_t offset = 2;

                        for (size_t i = 0; i < customers_count; i++) {
                            Customer *customer = (Customer*)(data + offset);
                            std::cout << " <=> customer: " << *customer  << std::endl;
                        }

                    } else {
                        std::cout << "Failed to read from the server!" << std::endl;
                    }
                }
            }

            data[0] = (char)MessageVariant::CLOSE;
            write(data_socket, data, 1);
            break;
        }
    }


    void runLab8(void) {
        std::string run_type { };
        std::cin >> run_type;

        try {
            if (run_type == "server" || run_type == "s" || run_type == "serve")
                server();
            else
                client();

        } catch (std::exception& e) {
            std::cerr << "Failed with: `" << e.what() << "`." << std::endl;
        }
    }
}
