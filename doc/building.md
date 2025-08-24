# Building MATHNEON

MATHNEON is a lightweight math library using ARM NEON intrinsics.  

---

## 📦 Requirements

- **CMake** ≥ 3.10
- **C compiler** (Tested with MSVC on Windows)
- **ARM NEON support**
  - On Windows ARM64 → use MSVC ARM64 toolchain
---

## 🔨 Build Instructions

### 1. Clone the repository
```
git clone https://github.com/yourusername/MATHNEON.git
cd MATHNEON
```
### 2. Configure and build with CMake
```
cmake -B build -S .
cmake --build build --config Release
```
This will generate:
Static library → build/Release/MATHNEON.lib (Windows) 
Unit tests → build/Release/test_<mathlib> (or .exe on Windows)

### 3. Testing
After building, run tests:
```
cd build
ctest --output-on-failure -C Release
```

