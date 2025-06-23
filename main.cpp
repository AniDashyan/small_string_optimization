#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>

using namespace std;

double get_time(const std::string& str, size_t iterations) {
    auto start = std::chrono::steady_clock::now();
    
    for (size_t i = 0; i < iterations; ++i) {
        std::string s = str; // Allocation/Deallocation
    }
    
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return static_cast<double>(duration) / iterations; 
}

size_t find_sso_limit() {
    size_t max_len = 30;
    size_t sso_capacity = 0;
    bool found = false;
    
    for (size_t len = 0; len <= max_len; ++len) {
        std::string s(len, 'a');
        size_t cap = s.capacity();
        
        if (len == 0) {
            sso_capacity = cap; // Initial capacity for empty std::string
        } else if (!found && cap > sso_capacity) {
            // Likely switched to heap
            found = true;
            return len - 1; // Previous length was SSO
        } else if (!found && len == max_len) {
            // No change in capacity
            return len;
        }
    }
    return sso_capacity;
}

int main() {
    std::string short_str = "hello";         
    std::string long_str(30, 'a');            

    const size_t iterations = 1'000'000;

    size_t sso_limit = find_sso_limit();

    cout << "Memory Usage:\n";
    cout << "sizeof(std::string): " << sizeof(std::string) << " bytes\n";
    cout << "Short string ('" << short_str << "'):\n";
    cout << "  Length: " << short_str.length() << ", Capacity: " << short_str.capacity() << "\n";
    cout << "Long string (30 chars):\n";
    cout << "  Length: " << long_str.length() << ", Capacity: " << long_str.capacity() << "\n";

    cout << "\nPerformance Analysis\n";
    cout << fixed << setprecision(2);
    cout << "Short string: " << get_time(short_str, iterations) << " ns\n";
    cout << "Long string:  " << get_time(long_str, iterations) << " ns\n";

    // Testing different string lengths
    for (size_t len = 5; len <= 30; len += 5) {
        std::string s(len, 'a');
        bool likely_sso = len <= sso_limit;
        cout << "Length: " << setw(2) << len << ", Capacity: " << setw(2) << s.capacity()
             << ", Likely SSO: " << (likely_sso ? "Yes" : "No") << "\n";
    }

    return 0;
}