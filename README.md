# Small String Optimization 

## Overview
This project analyzes Small String Optimization (SSO) in C++'s std::string. It measures memory usage and allocation/deallocation performance for short and long strings, demonstrating how SSO avoids heap allocation for small strings to improve efficiency. The program dynamically infers the SSO threshold and provides insights into std::string behavior across standard library implementations.

## Build & Run
```bash
# Clone the repository
git clone https://github.com/AniDashyan/small_string_optimization.git

# Navigate to the repository
cd small_string_optimization

# Build the project
cmake -S . -B build
cmake --build build --config Release

# Run the executable
./build/sso
```

## Example Output
```bash
Memory Usage:
sizeof(std::string): 32 bytes
Short string ('hello'):
  Length: 5, Capacity: 15
Long string (30 chars):
  Length: 30, Capacity: 30

Performance Analysis
Short string: 25.62 ns
Long string:  63.58 ns
Length:  5, Capacity: 15, Likely SSO: Yes
Length: 10, Capacity: 15, Likely SSO: Yes
Length: 15, Capacity: 15, Likely SSO: Yes
Length: 20, Capacity: 20, Likely SSO: No
Length: 25, Capacity: 25, Likely SSO: No
Length: 30, Capacity: 30, Likely SSO: No
```

## Explanation
Small String Optimization (SSO)
SSO is a technique used by std::string to optimize small strings by storing them in a fixed-size buffer within the stack allocated string object itself, avoiding heap allocation. For strings exceeding this buffer size, std::string allocates memory on the heap. This reduces memory overhead and improves performance for common string lengths (e.g., up to ~15–23 bytes, depending on the standard library implementation).
