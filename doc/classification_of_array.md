# Understanding 1D, 2D, 3D, and 4D Arrays

This guide explains arrays in simple terms with examples.

---

## 📌 1D Array (One-dimensional)
- Think of it as a **list of boxes in a single row**.
- Each box stores one value.

Example:
```
int arr[5] = {10, 20, 30, 40, 50};
```
Visual:
```
[10] [20] [30] [40] [50]
```

---

📌 2D Array (Two-dimensional)

- Think of it as a table with rows and columns.
- Each row is like a 1D array.

Example:
```
int arr[3][4] = {
  {1, 2, 3, 4},
  {5, 6, 7, 8},
  {9, 10, 11, 12}
};
```
Visual (3 rows × 4 columns):
```
Row 1 → [ 1   2   3   4 ]
Row 2 → [ 5   6   7   8 ]
Row 3 → [ 9  10  11  12 ]
```

---
📌3D Array (Three-dimensional)

- Think of it as a stack of 2D tables.
- Each "layer" is a 2D array.

Example:
```
int arr[2][3][3] = {
  { {1,2,3}, {4,5,6}, {7,8,9} },
  { {10,11,12}, {13,14,15}, {16,17,18} }
};
```

Visual:
```
Layer 1:
[ 1   2   3 ]
[ 4   5   6 ]
[ 7   8   9 ]

Layer 2:
[ 10  11  12 ]
[ 13  14  15 ]
[ 16  17  18 ]
```
---
📌4D Array (Four-dimensional)

- A 4D array is a multidimensional array with four dimensions. It can be used to represent data that requires four indices to access.
- Like: multiple stacks of tables grouped together.
- Best usecase: A video (Frames × Height × Width × Color channels).

Example:
```
int arr[2][2][2][2] = {
  {
    { {1,2}, {3,4} },
    { {5,6}, {7,8} }
  },
  {
    { {9,10}, {11,12} },
    { {13,14}, {15,16} }
  }
};
```

