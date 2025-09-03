# Project Layout

This document describes the structure of the project.

```text
.github/
└── workflows/
    └── build_and_test.yml       # CI workflow for building and testing
checks/                          # Validation and platform checks
└── neon_check.c                 # Checks NEON SIMD availability
doc/                             # Project documentation
├── building.md                  # Instructions to build the project
└── classification_of_array.md   # Notes on array classification
includes/                        # Public header files
├── MN_dtype.h                   # Data type definitions
├── MN_macro.h                   # Common macros
└── MN_math.h                    # Math-related declarations
src/                             # Source code implementation
├── Operators/
│   ├── Operator_neon.c          # NEON-optimized math operator
│   └── Operator_scalar.c        # Scalar implementation math operator
test/                            # Unit and validation tests
├── test_operator_neon.c         # Tests for NEON routines
└── test.md                      # Documentation for testing strategy

CHANGELOG.md                     # Record of changes
CMakeLists.txt                   # CMake build configuration
Goal.md                          # Project goals and roadmap
README.md                        # Overview and usage instructions
