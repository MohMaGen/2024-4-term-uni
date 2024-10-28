#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <exception>
#include <functional>
#include <iostream>
#include <lab7.hpp>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/un.h>
#include <sys/socket.h>

namespace lab8 {
    /*
     * @brief Class for optional value
     *
     * Idea taken from Haskell Maybe monad and std::optional from c++.
     */
    template<typename Type>
    struct Maybe {
        enum { Just=0, Nothing } variant;
        union { Type just; bool _; };

        /*
         * Default constructor creates nothing variant.
         */
        Maybe<Type>(): variant(Nothing), _(false) {}

        /*
         * Create new Just container.
         */
        Maybe<Type>(Type value): variant(Just), just(value) {}


        /*
         * Check if contains value.
         *
         * @return bool if contains value.
         */
        constexpr bool hasSome() const noexcept { return variant != Nothing; }
        explicit operator bool() { return hasSome(); }

        /*
         * Get value or trhow std::out_of_range if irs empty.
         */
        const Type& operator*() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        /*
         * Get value or trhow std::out_of_range if irs empty.
         */
        Type& operator*() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return just;
        }

        /*
         * Get value or trhow std::out_of_range if irs empty.
         */
        const Type* operator->() const {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }

        /*
         * Get value or trhow std::out_of_range if irs empty.
         */
        Type* operator->() {
            if (variant == Nothing) throw std::out_of_range("Attempt ot get Nothing!!!");
            return &just;
        }
    };


	/*
     * Class describing Customer without default constructor.
     *
     * Customers can be three types: Junior Middle or Senior.
     * (Stupid joke Middle must be Adult, but...)
     *
     * Customers has time_to_serve -- time needed by window to satisfy
     * needs of customer.
     */
    class Customer {
        public:
            /*
             * Type of Customer
             */
            enum CustomerType { Junior=0, Middle, Senior } type;

            /*
             * Time needed by window to satisfy
             * needs of customer.
             */
            size_t time_to_serve;

            Customer() = delete;

            /*
             * Create new customer of random type. Also can return empty Maybe which means
             * no customer generated this time.
             *
             * @return Maybe<Customer> optional customer.
             */
            static Maybe<Customer> Generate() {
                double chance = (double)std::rand() / (double)RAND_MAX;

                if (chance < 0.05) return { Customer{ Junior, (size_t)std::rand()%5+5 } };
                if (chance < 0.45) return { Customer{ Middle, (size_t)std::rand()%3+2 } };
                if (chance < 0.75) return { Customer{ Senior, (size_t)std::rand()%2+7 } };

                return { };
            }

            /*
             * Construct customer.
             *
             * @type -- type of the customer.
             * @time_to_serve -- time needed by window to serve customer.
             */
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

    std::ostream& operator<<(std::ostream& os, Maybe<Customer> customer) {
        return customer ? os << "Just `" << *customer << "`" : os << "Nothing";
    }

    /*
     * Class describing window that can serve customer.
     *
     * It's contains customer and serving time.
     *
     * Window can be update and ticked.
     */
    class Window {
        Maybe<Customer> _customer;
        size_t _serving_time = 0;
        public:
            /*
             * Apply 1 min delta time to counters.
             */
            void tick(void) {
                if (!_customer) return;
                _serving_time++;
            }

            /*
             * Update window.
             *
             * @return 1 if customer have served this update or 0.
             */
            int update() {
                if (!_customer) return 0;

                if (_serving_time >= _customer->time_to_serve) {
                    _customer = { };
                    _serving_time = 0;
                    return 1;
                }

                return 0;
            }

            /*
             * Return customer.
             *
             * @return ref to the customer.
             */
            const Maybe<Customer>& getCustomer(void) const noexcept {
                return _customer;
            } 

            /*
             * Check if contains customer.
             *
             * @return if contains customer.
             */
            bool hasCustomer(void) const noexcept {
                return _customer.hasSome();
            }

            /*
             * Update customer and serving time.
             *
             * @param customer -- new cusomer value.
             */
            void setCustomer(Customer customer) noexcept {
                _customer = {  customer };
                _serving_time = 0;
            }


        friend std::ostream& operator<<(std::ostream& os, const Window &window);
    };
    std::ostream& operator<<(std::ostream& os, const Window &window) {
        os << "Window `" << window._serving_time << "min` " << window._customer;

        return os;
    }

    /*
     * Class describing Institution that contains all windows and queues.
     */
    class Institution {
        lab7::Queue<Customer> _e_queue { 10 }, _l_queue { 10 };
        std::vector<Window> _windows { 3 }; 

        // Current time in mins from start of the shift.
        size_t _inst_time = 0;

        // Time to create new customers.
        size_t _time_to_next_cutomer_wave = 0;

        // Count of customers that have been served.
        size_t _served_customers = 0;

        // Count of all customers entered to institution.
        size_t _customers_count  = 0;

		/*
         * Generate three or less customers.
         */
        void _new_customers() {
            std::cout << "  - New customers:";

            for (size_t i = 0; i < 3; i++) {
                auto customer = Customer::Generate();
                if (!customer.hasSome()) continue;

                _customers_count++;

                double chance = (double)std::rand() / (double)RAND_MAX;

                switch (customer->type) {
                case Customer::Junior: {
                    std::cout << " Junior";

                    if (chance <= 0.2)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Middle: {
                    std::cout << " Middle";

                    if (chance <= 0.7)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                case Customer::Senior: {
                    std::cout << " Senior";

                    if (chance <= 0.05)
                        _e_queue.push(*customer); 
                    else 
                        _l_queue.push(*customer);
                } break;
                default:
                    std::cout << "BI";
                }
            }
            std::cout << std::endl;
        }

        /*
         * Update tick. (Update all components)
         */
        void _update() {
            std::cout << "UPDATE:" << std::endl;

            if (_inst_time >= 540) {
                std::cout << "  - shift ends..." << std::endl;
                return;
            }

            if (_time_to_next_cutomer_wave == 0) {
                _new_customers();
                _time_to_next_cutomer_wave = 5;
            }

            for (auto &window: _windows) {
                _served_customers += window.update();
                if (window.hasCustomer()) continue;

                if (_inst_time < 180 || _inst_time > 240) { 
                    if (_e_queue.len() > 0) {
                        window.setCustomer(_e_queue.shift());  
                    } else if (_l_queue.len() > 0) {
                        window.setCustomer(_l_queue.shift());  
                    }
				}
            }
        }

        /*
         * Display main information of the institution.
         */
        void _display() {
            std::cout << "DISPLAY:" << std::endl;
            std::cout << "  - E queue:";
            for (auto customer : _e_queue) {
                std::cout << " " << customer;
            }
            std::cout << std::endl;

            std::cout << "  - Live queue:";
            for (auto customer : _l_queue) {
                std::cout << " " << customer;
            }
            std::cout << std::endl;

            std::cout << "  - Windows:" << std::endl;;
            for (auto window: _windows) {
                std::cout << "   - " << window << std::endl;
            }
            std::cout << std::endl;
        }

        public:
            Institution(size_t windows_count): _windows(windows_count)  { 
                _update();
                _display();
            } 

            /*
             * Get vector of windows.
             *
             * @return ref to the windows.
             */
            const std::vector<Window>& getWindows(void) const noexcept {
                return _windows;
            }

            /*
             * Get live queue.
             *
             * @return ref to the live queue.
             */
            const lab7::Queue<Customer>&  getLiveQueue(void) const noexcept {
                return _l_queue;
            } 

            /*
             * Get e queue.
             *
             * @return ref to the e queue.
             */
            const lab7::Queue<Customer>& getEQueue(void) const noexcept {
                return _e_queue;
            } 

            /*
             * Stats of the shift.
             */
            struct Stats {
                // count of customers.
                size_t customers_count;

                // count of served customers.
                size_t served_customers;
            };

            /*
             * Return stats of this shift.
             * 
             * @return Stats of the shift.
             */
            Stats getStats(void) const noexcept {
                return Stats { _customers_count, _served_customers };
            }

            /*
             * Tick
             */
            void tick() {
                _update();

                _display();

                _time_to_next_cutomer_wave--;
                _inst_time++;
                for (auto& window: _windows) window.tick();
            }
    };

    /*
     * Create socket path by pid of server process.
     */
    std::string getSocketPath(size_t pid) {
        return "/tmp/cpp_labs-lab8-" + std::to_string(pid);
    }

    /*
     * Message variant 
     */
    enum class MessageVariant: char {
        GET_E_QUEUE=0,
        GET_L_QUEUE,
        GET_WINDOWS,
        GET_STATS,
        TICK,
        CLOSE,
    };

    /*
     * Response variant.
     */
    enum class ResponseVariant: char {
        OK=0,
        WINDOWS,
        CUSTOMERS,
        STATS,

        ERR=-1,
    };

    /*
     * Server Connection.
     * 
     */
    class Connection {
        Institution &institution;
        std::mutex &institutioin_mutex;
        int data_socket;
        bool should_close = false;

        public:
            Connection() = delete;

            /*
             * Create connection.
             * 
             * @param institution -- ref to the institution.
             * @param institutioin_mutex -- ref to the mutex of institutioin.
             * @param data_socket -- socket to read and write to the client.
             */
            Connection(Institution& institution, std::mutex &institutioin_mutex, int data_socket):
                institution(institution), institutioin_mutex(institutioin_mutex), data_socket(data_socket) {}

            /*
             * Serve tick message.
             *
             * @param buffer.
             */
            void tick_msg(char *buffer) {
                std::cout << "Request for tick:" << std::endl;

                {
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    institution.tick();
                }

                buffer[0] = (char)ResponseVariant::OK;

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");

                std::cout << "  : ok" << std::endl;
            }

            /*
             * Serve get live queue message.
             *
             * @param buffer.
             */
            void get_l_queue_msg(char *buffer) {
                const auto live_queue = [&]{
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    buffer[0] = (char)ResponseVariant::OK;
                    return institution.getLiveQueue();
                }();

                std::cout << "Request for live queue:" << std::endl;
                if (live_queue.len() > 0xFF)
                    throw std::runtime_error("Live Queue len too huge.");

                buffer[0] = (char)ResponseVariant::CUSTOMERS;

                buffer[1] = (unsigned char)live_queue.len();
                std::cout << "  : size is `" << live_queue.len() << "`." << std::endl;

                size_t idx = 2;
                for (auto customer : live_queue) {
                    std::cout << "  : customer `" << customer << "`." << std::endl;

                    std::memcpy(buffer+idx, &customer, sizeof(customer));
                    idx += sizeof(customer);
                }

                if (write(data_socket, buffer, idx) == -1)
                    throw std::runtime_error("Failed to write data socket.");
            }

            /*
             * Serve get e queue message.
             *
             * @param buffer.
             */
            void get_e_queue_msg(char *buffer) {
                const auto e_queue = [&]{
                    std::lock_guard<std::mutex> guard(institutioin_mutex); 
                    buffer[0] = (char)ResponseVariant::OK;
                    return institution.getEQueue();
                }();
                std::cout << "Request for e queue:" << std::endl;

                if (e_queue.len() > 0xFF)
                    throw std::runtime_error("E Queue len too huge.");

                buffer[0] = (char)ResponseVariant::CUSTOMERS;

                buffer[1] = (unsigned char)e_queue.len();
                std::cout << "  : size is `" << e_queue.len() << "`." << std::endl;

                size_t idx = 2;
                for (auto customer : e_queue) {
                    std::cout << "  : customer `" << customer << "`." << std::endl;

                    std::memcpy(buffer+idx, &customer, sizeof(customer));
                    idx += sizeof(customer);
                }

                if (write(data_socket, buffer, idx) == -1)
                    throw std::runtime_error("Failed to write data socket.");
            }

            /*
             * Serve get windows message.
             *
             * @param buffer.
             */
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

            /*
             * Serve get stats message.
             *
             * @param buffer.
             */
            void get_stats_msg(char *buffer) {
                std::cout << "Request for stats:" << std::endl;
                auto stats = [&] {
                    std::lock_guard<std::mutex> guard (institutioin_mutex);
                    return institution.getStats();
                }();

                buffer[0] = (char)ResponseVariant::STATS;
                *(Institution::Stats*)(buffer + 1) = stats;

                if (write(data_socket, buffer, sizeof(Institution::Stats) + 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");
            }

            /*
             * Serve close message.
             *
             * @param buffer.
             */
            void close_msg(char *buffer) {
                std::cout << "Request for end:" << std::endl;
                buffer[0] = (char)ResponseVariant::OK;

                if (write(data_socket, buffer, 1) == -1)
                    throw std::runtime_error("Failed to write data socket.");

                should_close = true;

                std::cout << "  : ok" << std::endl;
            }


            /*
             * Operator () to call main loop of connection.
             */
            void operator()() {
                char buffer[0x100];

                std::function<void (void)> jmp_table[] = {
                    [&buffer, this](){ this->get_e_queue_msg(buffer); },
                    [&buffer, this](){ this->get_l_queue_msg(buffer); },
                    [&buffer, this](){ this->get_windows_msg(buffer); },
                    [&buffer, this](){ this->get_stats_msg(buffer); },
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


    /*
     * Server logic.
     */
    void server(void) {
        std::srand(std::time(nullptr));
        Institution institution { 2 };
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

    /*
     * Class of client connection.
     */
    class ClientConnection {
        char *_data;
        int _data_socket;

        static constexpr char _HELP_MSG[] = "\n"
            " - help                -- prints this message.\n"
            " - close/c             -- close connection.\n"
            " - simulate/s <time>   -- simulate work of institution.\n"
            " - tick/t              -- tick.\n"
            " - windows/w           -- prints all windows.\n"
            " - e_queue/e           -- prints e queue.\n"
            " - l_queue/l           -- prints live queue.\n";

        /*
         * Read to the _data from server and check
         * if respoinse variant equal to must_be.
         * 
         * @param must_be -- value that must be.
         */
        bool _read_response(ResponseVariant must_be) {
            if (int len = read(_data_socket, _data, 0x100); len > 0) {
                auto response_variant =  ResponseVariant(_data[0]);

                if (response_variant == ResponseVariant::ERR) {
                    std::cout << "Response an error message" << std::endl;
                    return false;
                } 

                if (response_variant != must_be) {
                    std::cout << "Get wront response message!" << std::endl;
                    return false;
                }
            } else {
                std::cout << "Failed to read from the server!" << std::endl;
                return false;
            }
            return true;
        }

        /*
         * Write message to the server.
         *
         * @data -- variant of the message to write.
         */
        bool _write_message(MessageVariant data) {
            _data[0] = (char)data;

            if (write(_data_socket, _data, 1) < 0) {
                std::cout << "Failed to write to the server!" << std::endl;
                return false;
            } 

            return true;
        }

        /*
         * Complete tick command.
         */
        bool _do_tick() {
            if (!_write_message(MessageVariant::TICK)) return false; 
            if (!_read_response(ResponseVariant::OK))  return false;

            std::cout << "Tick succsessfully!!" << std::endl;

            return false;
        }

        /*
         * Parse payload of response.
         *
         * @generic_param Type type of the paylaod element.
         * @return vector of resulting elements.
         */
        template<typename Type>
        std::vector<Type> _parse_array() {
            std::vector<Type> data { };
            size_t array_len = (size_t)_data[1];

            data.reserve(array_len); 

            size_t offset = 2;
            for (size_t i = 0; i < array_len; i++) {
                Type *elem = (Type*)(_data + offset);
                data.push_back(*elem);
                offset += sizeof(Type);
            }

            return std::move(data);
        }

        /*
         * Complete windows command.
         */
        bool _do_windows() {
            if (!_write_message(MessageVariant::GET_WINDOWS)) return false; 
            if (!_read_response(ResponseVariant::WINDOWS))    return false;

			auto windows = _parse_array<Window>();

            std::cout << "Windows count: `" << windows.size() << "`." << std::endl;
            for (auto window: windows) {
                std::cout << " <=> window: " << window << std::endl;
            }

            return false;
        }

        /*
         * Complete e queue command.
         */
        bool _do_e_queue() {
            if (!_write_message(MessageVariant::GET_E_QUEUE)) return false; 
            if (!_read_response(ResponseVariant::CUSTOMERS))  return false;

            auto customers = _parse_array<Customer>();

            std::cout << "E queue count: `" << customers.size() << "`." << std::endl;
            for (auto customer: customers) {
                std::cout << " <=> customer: " << customer << std::endl;
            }

            return false;
        }

        /*
         * Complete live queue command.
         */
        bool _do_l_queue() {
            if (!_write_message(MessageVariant::GET_L_QUEUE)) return false; 
            if (!_read_response(ResponseVariant::CUSTOMERS))  return false;

            auto customers = _parse_array<Customer>();

            std::cout << "L queue count: `" << customers.size() << "`." << std::endl;
            for (auto customer: customers) {
                std::cout << " <=> customer: " << customer << std::endl;
            }

            return false;
        }

        /*
         * Calculate amount of mins in string line.
         *
         * string must conatains whitespace sparated values of
         * format `<uint>(min|m|mins|h|hour|hours)`.
         * 
         * @return resulting sum of value.
         */
        size_t _calc_mins(const std::string& str) {
            size_t res = 0;

            std::string word { };
            std::string line = str + " ";

            for (char c : line) {
                if (c == ' ') {
                    char *offset;
                    size_t v = std::strtoul(word.c_str(), &offset, 10); 
                    if (offset == word.c_str()) {
                        v = 0;
                    } else {

                        if (std::strcmp(offset, "min") == 0 || std::strcmp(offset, "m") == 0
                                || std::strcmp(offset, "mins") == 0) v *= 1;

                        else if (std::strcmp(offset, "hour") == 0 || std::strcmp(offset, "h") == 0
                                || std::strcmp(offset, "hours") == 0) v *= 60;

                        else v = 0;
                    }

                    word = std::string { };
                    res += v;
                }
                word.push_back(c); 
            }

            return res;
        }

        /*
         * Complete simulate command.
         */
        bool _do_simulate() {
            std::string line ( 0x100, '\0' );
            std::cin.getline(line.data(), 0x100);

            size_t time = _calc_mins(line); 
            std::cout << "Will simulate " << time << "min." << std::endl;

            size_t i = 0;
            while (i < time) {
                if (!_write_message(MessageVariant::TICK)) continue;
                if (!_read_response(ResponseVariant::OK))  continue;
                i++;
            }

            if (!_write_message(MessageVariant::GET_WINDOWS)) return false; 
            if (!_read_response(ResponseVariant::WINDOWS))    return false;

            auto windows = _parse_array<Window>();

            if (!_write_message(MessageVariant::GET_E_QUEUE)) return false; 
            if (!_read_response(ResponseVariant::CUSTOMERS))  return false;

            auto e_queue = _parse_array<Customer>();

            if (!_write_message(MessageVariant::GET_L_QUEUE)) return false; 
            if (!_read_response(ResponseVariant::CUSTOMERS))  return false;

            auto l_queue = _parse_array<Customer>();

            std::cout << "L queue count: `" << l_queue.size() << "`." << std::endl;
            for (auto customer: l_queue) {
                std::cout << " <=> customer: " << customer << std::endl;
            }

            std::cout << "E queue count: `" << e_queue.size() << "`." << std::endl;
            for (auto customer: e_queue) {
                std::cout << " <=> customer: " << customer << std::endl;
            }

            std::cout << "Windows count: `" << windows.size() << "`." << std::endl;
            for (auto window: windows) {
                std::cout << " <=> window: " << window << std::endl;
            }

            if (!_write_message(MessageVariant::GET_STATS)) return false; 
            if (!_read_response(ResponseVariant::STATS))  return false;

            Institution::Stats *stats = (Institution::Stats *)(_data + 1);
            std::cout << "Stats:" << std::endl;
            std::cout << "  - customer count " << stats->customers_count << std::endl;
            std::cout << "  - served customers " << stats->served_customers << std::endl;
            std::cout << std::endl;

            return false;
        }

        public:
            /*
             * Create clinet connection.
             *
             * @param data_socket - socket of server connection.
             */
            ClientConnection(int data_socket): _data(new char[0x1000]), _data_socket(data_socket) {}

            /*
             * Comlete command from string.
             * 
             * @param command to complete.
             */
            bool do_command(const std::string& cmd) {
                if (cmd == "help") {
                    std::cout << _HELP_MSG << std::endl;
                    return false;
                }
                if (cmd == "c" || cmd == "close") {
                    std::cout << "closing..." << std::endl;
                    return true;
                } 
                if (cmd == "tick" || cmd == "t") {
                    return _do_tick();
                }
                if (cmd == "w" || cmd == "windows") {
                    return _do_windows();
                }
                if (cmd == "e" || cmd == "e_queue") {
                    return _do_e_queue();
                }
                if (cmd == "l" || cmd == "l_queue") {
                    return _do_l_queue();
                }
                if (cmd == "s" || cmd == "simulate") {
                    _do_simulate();
                }
                return false;
            }
    };

    /*
     * Do client logic.
     */
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

            ClientConnection connection { data_socket };

            while (true) {
                std::string cmd { };
                std::cout << "lab8 client> ";
                std::cin >> cmd;

                connection.do_command(cmd); 
            }

            data[0] = (char)MessageVariant::CLOSE;
            write(data_socket, data, 1);
            break;
        }
    }


    /*
     * Start lab.
     */
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
