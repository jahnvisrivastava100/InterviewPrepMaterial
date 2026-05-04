````md id="spiral-matrix-final-notes"
# Spiral Matrix Traversal — Complete Notes

# Problem Statement

Given a 2D matrix, return all elements in spiral order.

Example:

Input:

```text id="sp1"
1 2 3
4 5 6
7 8 9
````

Output:

```text id="sp2"
[1,2,3,6,9,8,7,4,5]
```

---

# Approach Explanation Step-by-Step

## Step 1 → Define Boundaries

We maintain 4 boundaries:

```cpp id="sp3"
int up = 0;
int down = matrix.size() - 1;

int left = 0;
int right = matrix[0].size() - 1;
```

These boundaries represent the remaining unvisited area.

---

## Step 2 → Define Direction Variable

```cpp id="sp4"
int d = 0;
```

This variable controls traversal direction.

| d | Direction    |
| - | ------------ |
| 0 | Left → Right |
| 1 | Top → Bottom |
| 2 | Right → Left |
| 3 | Bottom → Top |

---

## Step 3 → Traverse While Boundaries Are Valid

```cpp id="sp5"
while(up <= down && left <= right)
```

Loop continues until all layers are traversed.

---

## Step 4 → Traverse Left to Right

```cpp id="sp6"
for(int i = left; i <= right; i++){
    res.push_back(matrix[up][i]);
}
up++;
```

After traversing top row:

* top row is fully visited
* move boundary downward

---

## Step 5 → Traverse Top to Bottom

```cpp id="sp7"
for(int i = up; i <= down; i++){
    res.push_back(matrix[i][right]);
}
right--;
```

After traversing right column:

* right column is fully visited
* shrink right boundary

---

## Step 6 → Traverse Right to Left

```cpp id="sp8"
for(int i = right; i >= left; i--){
    res.push_back(matrix[down][i]);
}
down--;
```

After traversing bottom row:

* bottom row consumed
* move boundary upward

---

## Step 7 → Traverse Bottom to Top

```cpp id="sp9"
for(int i = down; i >= up; i--){
    res.push_back(matrix[i][left]);
}
left++;
```

After traversing left column:

* left column consumed
* shift boundary rightward

---

## Step 8 → Rotate Direction

```cpp id="sp10"
d = (d + 1) % 4;
```

Cycles direction:

```text id="sp11"
0 → 1 → 2 → 3 → 0
```

---

# Complete Code

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {

        int up = 0;
        int down = matrix.size() - 1;

        int left = 0;
        int right = matrix[0].size() - 1;

        vector<int> res;

        int d = 0;

        while(up <= down && left <= right){

            if(d == 0){
                for(int i = left; i <= right; i++){
                    res.push_back(matrix[up][i]);
                }
                up++;
            }

            if(d == 1){
                for(int i = up; i <= down; i++){
                    res.push_back(matrix[i][right]);
                }
                right--;
            }

            if(d == 2){
                for(int i = right; i >= left; i--){
                    res.push_back(matrix[down][i]);
                }
                down--;
            }

            if(d == 3){
                for(int i = down; i >= up; i--){
                    res.push_back(matrix[i][left]);
                }
                left++;
            }

            d = (d + 1) % 4;
        }

        return res;
    }
};
```

---

# Thought Process Behind This Approach

The main observation is:

```text id="sp12"
Spiral traversal always moves layer by layer.
```

Each layer has:

1. top row
2. right column
3. bottom row
4. left column

After completing one layer:

```text id="sp13"
boundaries shrink inward
```

Instead of tracking visited cells separately, we reduce the matrix area dynamically.

This makes the solution:

* cleaner
* memory efficient
* easier to debug

---

# Complexity Analysis

## Time Complexity

## O(m × n)

Where:

* `m` = number of rows
* `n` = number of columns

Reason:

```text id="sp14"
Every element is visited exactly once.
```

---

## Space Complexity

## O(1)

Ignoring output array.

Extra space used:

* boundaries
* direction variable
* loop variables

No additional matrix used.

---

# Tricks Used In This Problem

---

## Trick 1 → Boundary Shrinking

Instead of marking visited cells:

```text id="sp15"
up++
down--
left++
right--
```

Shrinks the active matrix region.

This avoids:

* revisiting
* extra memory usage

---

## Trick 2 → Direction Cycling

```cpp id="sp16"
d = (d + 1) % 4;
```

Very common interview trick.

Helps rotate among:

```text id="sp17"
right
down
left
up
```

without multiple nested loops.

---

## Trick 3 → Layer-by-Layer Traversal

Think of matrix as concentric rectangles.

Example:

```text id="sp18"
Outer layer
Inner layer
Inner-inner layer
```

This mental model simplifies spiral problems.

---

# Interview Questions Asked Frequently

---

## Q1. Why do we use boundaries?

### Answer

Boundaries help define the current unvisited region.

After traversing one side:

```text id="sp19"
that side becomes invalid
```

so we shrink the corresponding boundary.

---

## Q2. Why modulo 4?

### Answer

There are exactly 4 traversal directions.

Modulo creates cyclic movement.

```cpp id="sp20"
d = (d + 1) % 4;
```

Example:

```text id="sp21"
0 → 1 → 2 → 3 → 0
```

---

## Q3. Why not use visited matrix?

### Answer

Visited matrix requires:

```text id="sp22"
O(m*n)
```

extra memory.

Boundary approach solves it using:

```text id="sp23"
O(1)
```

extra space.

---

## Q4. Why is loop condition:

```cpp id="sp24"
up <= down && left <= right
```

### Answer

Traversal should continue only while rows and columns remain valid.

Once boundaries cross:

```text id="sp25"
all cells are already visited
```

---

## Q5. What if matrix has one row?

### Answer

Only left-to-right traversal executes.

Algorithm still works safely.

---

## Q6. What if matrix has one column?

### Answer

Mainly top-to-bottom traversal executes.

No special handling required.

---

## Q7. Can this problem be solved recursively?

### Answer

Yes.

Each recursive call processes:

```text id="sp26"
outer layer
```

then recursively processes inner submatrix.

But iterative approach is simpler and preferred in interviews.

---

## Q8. How do you identify spiral traversal problems?

### Answer

Look for keywords like:

* circular movement
* layer traversal
* outer boundary
* inward movement

These usually indicate:

```text id="sp27"
top
bottom
left
right
```

boundary approach.

---

# Data Structures Used

---

## 1. Vector

```cpp id="sp28"
vector<int> res;
```

Used to store final spiral order traversal.

---

## 2. 2D Vector (Matrix)

```cpp id="sp29"
vector<vector<int>>& matrix
```

Represents grid structure.

Access format:

```cpp id="sp30"
matrix[row][col]
```

---

# Questions on Data Structures Used

---

## Q1. Why use vector instead of array?

### Answer

Vector provides:

* dynamic sizing
* easy insertion
* STL support

Arrays require fixed size.

---

## Q2. How is matrix stored internally?

### Answer

A 2D vector is internally:

```text id="sp31"
vector of vectors
```

Each row itself is a vector.

---

## Q3. Time complexity of vector push_back?

### Answer

Average:

```text id="sp32"
O(1)
```

Worst case during resizing:

```text id="sp33"
O(n)
```

---

## Q4. Why matrix indexing is O(1)?

### Answer

Vectors support direct indexing.

```cpp id="sp34"
matrix[i][j]
```

is constant-time access.

---

# Real World Applications

---

## 1. Image Processing

Spiral traversal can be used in:

* image scanning
* pixel layer processing
* boundary extraction

---

## 2. Robotics Path Traversal

Robots cleaning or scanning rectangular regions may move in spiral paths.

Example:

```text id="sp35"
vacuum cleaning robots
```

---

## 3. Game Development

Used in:

* map exploration
* spiral spawning systems
* area reveal animations

---

## 4. Matrix-Based Simulations

Useful in:

* heat map simulations
* layer processing
* scientific computations

---

## 5. Printer/Scanner Hardware Logic

Some hardware devices process data layer-by-layer internally.

---

# Final Summary

Core idea:

```text id="sp36"
Use four shrinking boundaries
+
Traverse in four cyclic directions
+
Reduce the active matrix after every traversal
```

This gives:

* efficient traversal
* O(m*n) time
* O(1) extra space
* clean interview-friendly logic

```
```
