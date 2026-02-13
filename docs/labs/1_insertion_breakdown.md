# Lab 1: Insertion Sort Algorithm Time Complexity

Insertion sort is a simple sorting algorithm that builds the final sorted array one item at a time. It works similarly to how you might sort playing cards in your hands - you pick up cards one at a time and insert them into their correct position among the cards you've already sorted.

Here is the algorithm with the time costs and number of times each line runs:

- **Algorithm: Insertion Sort**
    - **Input:** An array $A$ of $n$ numbers $[a_0, a_1, ..., a_{n-1}]$
    - **Output:** The array $A$ sorted in non-decreasing order
    - **Procedure:**

| No. | Step                                                               | $c_i$ | Number of Times           |
| --- | ------------------------------------------------------------------ | ----- | ------------------------- |
| 1   | $\text{for } i \gets 1 \text{ to } n-1 \text{ do:}$                | $c_1$ | $n$                       |
| 2   | &emsp;$key \gets A[i]$                                             | $c_2$ | $n-1$                     |
| 3   | &emsp;$j \gets i - 1$                                              | $c_3$ | $n-1$                     |
| 4   | &emsp;$\text{while } j \geq 0 \text{ and } A[j] > key \text{ do:}$ | $c_4$ | $\sum_{i=1}^{n-1}t_i$     |
| 5   | &emsp;&emsp;$A[j+1] \gets A[j]$                                    | $c_5$ | $\sum_{i=1}^{n-1}(t_i-1)$ |
| 6   | &emsp;&emsp;$j \gets j - 1$                                        | $c_6$ | $\sum_{i=1}^{n-1}(t_i-1)$ |
| 7   | &emsp;$\text{end while}$                                           | 0     | -                         |
| 8   | &emsp;$A[j+1] \gets key$                                           | $c_8$ | $n-1$                     |
| 9   | $\text{end for}$                                                   | 0     | -                         |

Here, $t_i$ denotes the number of times the while loop test in line 4 is executed for a particular value of $i$. Notice that:

- The outer loop runs from $i=1$ to $n-1$, so it executes $n-1$ times
- For each iteration $i$, the while loop condition is checked $t_i$ times
- The body of the while loop (lines 5-6) executes $t_i - 1$ times (one less than the condition check, since the final check fails and exits the loop)

The value of $t_i$ varies based on the input configuration, giving us different cases to analyze.

## Best Case Analysis

The **best case** occurs when the array is already sorted in non-decreasing order. In this scenario:

- For each iteration $i$, when we compare $key$ (which is $A[i]$) with $A[j]$ (which is $A[i-1]$)
- Since the array is already sorted, $A[i-1] \leq A[i]$, so the condition $A[j] > key$ is immediately false
- The while loop condition is checked exactly once ($t_i = 1$) and the body never executes ($t_i - 1 = 0$)

Therefore, in the best case:

$$T(n) = c_1(n) + c_2(n-1) + c_3(n-1) + c_4(n-1) + c_5(0) + c_6(0) + c_8(n-1)$$

Simplifying:

$$T(n) = c_1n + c_2(n-1) + c_3(n-1) + c_4(n-1) + c_8(n-1)$$

$$T(n) = c_1n + (c_2 + c_3 + c_4 + c_8)(n-1)$$

$$T(n) = c_1n + (c_2 + c_3 + c_4 + c_8)n - (c_2 + c_3 + c_4 + c_8)$$

$$T(n) = (c_1 + c_2 + c_3 + c_4 + c_8)n - (c_2 + c_3 + c_4 + c_8)$$

If we let $a = c_1 + c_2 + c_3 + c_4 + c_8$ and $b = c_2 + c_3 + c_4 + c_8$:

$$T(n) = an - b$$

This is a **linear function** of $n$. The best-case time complexity of insertion sort is therefore:

$$\Omega(n)$$

This means insertion sort runs in at least linear time - it cannot be faster than checking each element at least once.

## Worst Case Analysis

The **worst case** occurs when the array is sorted in reverse order (strictly decreasing). In this scenario:

- For each iteration $i$, the element $A[i]$ must be compared with all elements before it
- Each comparison shows that $A[j] > key$, so we keep moving backwards
- The while loop continues until $j < 0$
- For position $i$, we make $i+1$ comparisons (checking positions $i-1, i-2, ..., 1, 0$, and then checking if $j \geq 0$ fails)
- The body executes $i$ times

Therefore: $t_i = i + 1$ for each $i$ from $1$ to $n-1$

Computing the sums:

$$\sum_{i=1}^{n-1}t_i = \sum_{i=1}^{n-1}(i+1) = \sum_{i=1}^{n-1}i + \sum_{i=1}^{n-1}1 = \frac{(n-1)n}{2} + (n-1) = \frac{n^2 + n - 2}{2}$$

$$\sum_{i=1}^{n-1}(t_i-1) = \sum_{i=1}^{n-1}i = \frac{(n-1)n}{2}$$

Now we can calculate the worst-case runtime:

$$T(n) = c_1(n) + c_2(n-1) + c_3(n-1) + c_4\left(\frac{n^2+n-2}{2}\right) + c_5\left(\frac{n(n-1)}{2}\right) + c_6\left(\frac{n(n-1)}{2}\right) + c_8(n-1)$$

Simplifying by expanding and collecting terms:

$$T(n) = c_1n + c_2(n-1) + c_3(n-1) + \frac{c_4n^2 + c_4n - 2c_4}{2} + \frac{c_5n^2 - c_5n}{2} + \frac{c_6n^2 - c_6n}{2} + c_8(n-1)$$

$$T(n) = \frac{c_4 + c_5 + c_6}{2}n^2 + \left(c_1 + c_2 + c_3 + \frac{c_4 - c_5 - c_6}{2} + c_8\right)n - (c_2 + c_3 + c_4 + c_8)$$

If we let $a = \frac{c_4 + c_5 + c_6}{2}$, $b = c_1 + c_2 + c_3 + \frac{c_4 - c_5 - c_6}{2} + c_8$, and $c = c_2 + c_3 + c_4 + c_8$:

$$T(n) = an^2 + bn - c$$

This is a **quadratic function** of $n$. The worst-case time complexity of insertion sort is therefore:

$$O(n^2)$$

## Summary

Insertion sort has:

- **Best case:** $\Omega(n)$ - linear time when the array is already sorted
- **Worst case:** $O(n^2)$ - quadratic time when the array is reverse sorted
- **Average case:** $\Theta(n^2)$ - for random inputs, on average the while loop executes about half the maximum times, which still results in quadratic growth

This analysis shows why insertion sort is efficient for small or nearly-sorted datasets (where it approaches linear time) but becomes slow for large, randomly ordered datasets (where it exhibits quadratic behavior). For small values of $n$ (typically $n < 50$), insertion sort can actually be faster than more advanced algorithms due to its low constant factors and simple operations, but as $n$ grows large, the quadratic growth dominates and makes it impractical compared to algorithms like merge sort or quicksort which have $O(n \log n)$ worst-case or average-case complexity.
