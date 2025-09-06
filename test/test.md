# Writing Unit Tests for MN Operators

This document explains the structure and steps to follow when writing unit tests for operators in the **MATHNEON** library.

---

## Test File Structure

Each test program should follow this structure:

### 1. Include headers
```c
#include <stdio.h>
#include <stdlib.h>
#include "../includes/MN_dtype.h"
#include "../includes/MN_macro.h"
#include "../includes/MN_math.h"
```
### 2. Allocate memory

* Allocate arrays for:
* Flat types (float, int)
* Vector types (vec2, vec3, vec4) for both float and int
* Allocate three copies: src, dst, ref.

### 3. Initialize constants and input values

* Define scalar and vector constants
* Fill the source arrays with predictable values.

### 4. Compute reference output (C implementation)

* Call the _c functions (e.g., mn_subc_float_c, mn_subc_vec3f_c) to generate the reference output.

### 5. Compute NEON output

* Call the _neon functions with the same inputs.

### 6. Validation

* Compare the dst results against the ref results element by element.
* Print an error message and exit if mismatched.
* If all pass, print a success message.

### 7. Cleanup

* Free all allocated memory.
