# MachineEpsilon

This project analyzes the numerical precision of different floating-point implementations (32-bit, 64-bit, and 128-bit) when computing the arcsine function. It compares the results against reference implementations and visualizes the absolute and relative errors.

## 📊 Key Features
- Implementation of 128-bit floating-point arithmetic using double-double technique
- Taylor series approximation of arcsin function
- Precision comparison between:
  - `float` (32-bit)
  - `double` (64-bit)
  - `real128` (128-bit custom implementation)
- Error analysis:
  - Absolute error
  - Relative error
  - Difference between precisions
- Visualization using matplotlib-cpp

## 📦 Dependencies
- C++20 compatible compiler
- CMake (≥ 3.10)
- Python (for matplotlib-cpp)
- matplotlib-cpp (included)

## 🛠️ Build and Run
```bash
# Clone the repository
git clone https://github.com/Berletm/MachineEpsilon
cd MachineEpsilon

# Configure and build
mkdir build && cd build
cmake ..
make

# Run the program
./MachineEpsilon