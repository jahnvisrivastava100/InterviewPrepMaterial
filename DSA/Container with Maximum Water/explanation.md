# Container With Maximum Water

## Problem Statement

Given an array `height` where each element represents the height of a vertical line drawn at index `i`, find two lines that together with the x-axis form a container that can store the maximum amount of water.

The amount of water stored depends on:

- Width between the two lines
- Minimum of the two heights

Formula:

area = min(height[i], height[j]) * (j - i)

---

## Approach

### Brute Force

Check every possible pair of lines and calculate the area.

- Time Complexity: `O(N²)`
- Space Complexity: `O(1)`

---

## Optimized Two Pointer Approach

### Intuition

The container area is determined by:

- Width between pointers
- Smaller height among the two lines

Even if one line is taller, water can only be stored up to the smaller height.

We start with:

- `i = 0`
- `j = n - 1`

This gives the maximum possible width initially.

At every step:

1. Calculate current area
2. Update maximum area
3. Move the pointer pointing to the smaller height

### Why move the smaller height?

Because the smaller height is the limiting factor.

Moving the taller height inward only decreases the width while the limiting height remains unchanged, so the area cannot improve.

Moving the smaller height gives a chance to find a taller line and potentially increase the area.

---

## Complexity Analysis

| Complexity Type | Value |
|---|---|
| Time Complexity | `O(N)` |
| Space Complexity | `O(1)` |

---

## Common Interview Questions Asked

| Question | Explanation |
|---|---|
| Why is the area calculated using the minimum height? | Water can only be stored up to the shorter wall because it spills from the smaller side. |
| Why do we move the smaller pointer? | The smaller height is the bottleneck. Moving the taller pointer cannot increase the area since width decreases and limiting height remains the same. |
| Why is this approach O(N)? | Each pointer moves only in one direction and visits each index at most once. |
| Why not move both pointers together? | Moving both pointers may skip potential optimal solutions unnecessarily. |
| Why do we start from both ends? | Starting from both ends gives the maximum possible width initially. |
| Can this be solved using brute force? | Yes, by checking every pair of lines, but it takes `O(N²)` time. |
| What happens if heights are equal? | We can move either pointer because both heights limit the area equally. |
| Is this a greedy approach? | Yes, because at every step we greedily discard the smaller height side. |
