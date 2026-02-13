# Asymptotic Notation: Big O and Beyond

You've learned how to measure algorithm runtime by constructing T(n) functions and identifying dominant components. But writing out the full derivations every time is impractical. We need shorthand.

**Asymptotic notation** is the language computer scientists use to describe algorithm efficiency in a short way. It ignores the constants from before and focuses on the dominant components to explain an algorithms behavior and how it scales to larger inputs.

The three most important asymptotic notations are:

- **Big O (O)** - Upper bound (worst-case): "It will never be slower than this"
- **Big Omega (Ω)** - Lower bound (best-case): "It can't be faster than this"
- **Big Theta (Θ)** - Tight bound (average-case): "It grows exactly like this"

This lesson covers how to:

- Express algorithm runtime using Big O, Omega, and Theta notation
- Analyze both best-case and worst-case scenarios for the same algorithm
- Quickly compare algorithms by their complexity classes
- Find dominant components in code without exhaustive mathematical analysis
- Understand why a "slower-looking" O(n log n) algorithm often beats a "simple" O(n²) one

## Asymptotic Notation

From the [last lesson](./3_runtime.md) , we now see that:

- Algorithms take a certain number of discrete steps for a given problem instance
- Those steps take some amount of time when implemented on hardware
- The total number of steps is ultimately decided by the input size $n$
- We can estimate the runtime of an algorithm by constructing a $T(n)$ function in terms of its input size, $n$, and how many times each step is ran based on $n$. We then multiply each step by hypothetical constants, $c_i$, corresponding to algorithm step $i$.
- Some algorithms runtimes grow faster than others, and this is largely decided by the equations that use $n$, called the **dominant component** and it dictates an algorithms **rate of growth**

This **dominant component** and **rate of growth** is what really matters. In the "Growth of Functions" section, we saw that no matter what constant values a linear growth function has, it will always result in a lower rate of growth than a quadratic function. For this reason, we can ignore constants for the most part and measure an algorithms run time as the dominant component:

- Max Algorithm: 
	- $T(n)= (c_2 + c_3 + c_4)n + (c_1 + c_2 + c_7) \approx n$
- Find Duplicates Algorithm: 
	- $T(n) = \frac{(c_2+c_3)}{2}n^2 + \left(c_1 - \frac{c_2+c_3}{2}\right)n + (c_1 + c_8) \approx n^2$
- Both in terms of rate of growth of run time

This is called **asymptotic notation** and it refers to the discarding of lower order terms (lower rate of growth terms) and constants. We use it in reference to runtimes to calculate an algorithms **time complexity**, or how the algorithm's runtime increases as the input size grows under various conditions. 

Recall that, when we constructed $T(n)$, the runtime function of an algorithm, there was a mention of a **worst-case** and **best-case** runtime when calculating an indeterminant number of steps depending on the contents of the input rather than its size. 

Worst-case refers to the maximum number of steps an algorithm could take if the input was the hardest it could be to solve. For the Max Algorithm, if the input was sorted least-greatest, line 4 would get ran $n$ times, where as if the max value was in the beginning, line 4 would never be ran.  This latter situation is the **best-case scenario**, where every line takes the least number of steps possible. Another example of this would be the Sorting Problem, any sorting problem's best-case scenario is an input that is fully sorted. There is also **average-case** where an average input in size and difficulty is assumed or calculated and that is used to find the average running time of an algorithm.

Each one of these is useful for understanding and assessing algorithms. Especially when you consider the fact that dominant components may be different for worst, best, and average cases. This means we have three options to assess an algorithm, and, as a result, three types of **asymptotic notation**:

- $\Theta (g(n))$ - **"Big Theta" Notation**
- $\Omega (g(n))$ - **"Big Omega" Notation**
- $O(g(n))$ - **"Big O" Notation**

### Big Theta Notation

$\Theta (g(n))$ - **"Big Theta" Notation**

For a given function $g(n)$, we denote by $\Theta (g(n))$ the *set of functions*

$$\begin{gather}\Theta (g(n)) = \{f(n): \text{there exist positive constants } c_1, c_2, \text{and } n_0 \text{ such that}\\
0 \leq c_1 g(n) \leq f(n) \leq c_2g(n) \text{ for all } n \geq n_0 \}\end{gather}$$


- **This means the function grows at _exactly_ this $g(n)$** - it's sandwiched between the upper and lower bound of constants for all values of $n$ starting at some $n_0$ 
- We use Big Theta when we can describe the **average-case** or when the worst and best cases are the same of an algorithm
- Example: The Max Algorithm is  $\Theta (n)$ because it always does roughly $n$ comparisons regardless of the input

Big Theta is used to show an algorithms average-case or true runtime growth. If an algorithm's "average input" can be assumed or derived probabilistic analysis of the algorithm over many different inputs could be used to find its average-case. Most of the time, the average-case is found through experimentation or assumed through rough estimates. Otherwise we use Big Theta when the upper and lower limit of growth is the same.

---
### Big Omega Notation

$\Omega (g(n))$ - **"Big Omega" Notation**

For a given function $g(n)$, we denote by $\Omega (g(n))$ the *set of functions*
	
$$\begin{gather}\Omega (g(n)) = \{f(n): \text{there exist positive constants } c \text{ and } n_0 \text{ such that}\\
0 \leq c g(n) \leq f(n) \text{ for all } n \geq n_0 \}\end{gather}$$

- **This means the function grows at least at a rate of $g(n)$**, but it can be higher than this lower bound
- We use Big Omega when we can describe the **best-case** of an algorithm and know that the runtime function cannot grow slower than $g(n)$ 

Big Omega notation is the **asymptotic lower bound** and describes the best-case running time of an algorithm. What ever function of growth $g(n)$ has, it represents the runtime growth of an algorithm as the ideal input grows. It represented the fastest an algorithm can go, given an input that results in the fewest steps where there are varying numbers of them. 

---
### **Big O Notation**

$O(g(n))$ - **"Big O" Notation**

For a given function $g(n)$, we denote by $O (g(n))$ the *set of functions*

$$\begin{gather}O (g(n)) = \{f(n): \text{there exist positive constants } c \text{ and } n_0 \text{ such that}\\
0  \leq f(n) \leq c g(n) \text{ for all } n \geq n_0 \}\end{gather}$$

- **This means the function grows at most at a rate of $g(n)$**, but it can be lower than this upper bound
- We use Big O when we want to describe the **worst-case** of an algorithm and know that the runtime function will be at worst growing at rate $g(n)$
- We are usually going to talk about this one since the worst-case is usually the most important to work around in critical places

Big O Notation is the most used notation as it is used to describe the worst-case running time growth. This represents the **asymptotic upper bound** and defines the upper limit of growth in the runtime of an algorithm. It assumes inputs that cause the maximum number of steps and represents the worst possible performance of the algorithm as input grows. As such, it is the most useful of the three, since we often need to plan around the worst case scenario in safety critical environments. 

---
## Time Complexity

These various notations allow us to describe the behavior of an algorithm's runtime as the size of the input grows, this is known as the **time complexity** of the algorithm, and we use the three methods above to describe the general growth of the runtime function $T(n)$ under different conditions. We will, for the most part, focus on using asymptotic notation to describe how runtime grows, however we can use it to describe the growth of any function. The other resource we will want to describe using this method is the amount of memory an algorithm requires. This **space complexity**, will be highlighted another day, but know that we can use this notation for other things.

To show the full break down of an algorithm, read through [this lab](../labs/1_insertion_breakdown.md) that shows the process of estimating a runtime function, discarding constants, and extracting dominant components to generate the various time complexity metrics for Insertion Sort.

## "O" My Gosh... So "Complex"...

This may have been a bit jarring with the math and the notation if you are not used to it. While these ideas were sprung from years of complex mathematical theory, we do not need to focus on it in this class. This is merely an introduction to algorithmic analysis and to familiarize oneself with the various ways we would assess an algorithm, complex as a task as it may seem.

One of the consequences of going down the path of mathematical theory is a loss of practical use. To ensure our perspective remains properly oriented, it would be best to review these various ideas and connect them to things we can use in our coding.

### Quick Algorithm Assessment

Because computer science has matured as much as it has, many times when we approach a problem there will already be a suite of solutions available to choose from, each with their complexity listed out beforehand. One such problem that will reoccur in this course is the Sorting Problem. We will cover the Sorting Problem and all of these algorithms in depth another day, but let's put our newly found knowledge to use. 

| **Algorithm**  | **Best Case**     | **Average Case**  | **Worst Case** | **Space Complexit**y |
| -------------- | ----------------- | ----------------- | -------------- | -------------------- |
| Bubble Sort    | $\Omega(n)$       | $\Theta(n²)$      | $O(n²)$        | $\Theta(1)$          |
| Selection Sort | $\Omega(n²)$      | $\Theta(n²)$      | $O(n²)$        | $\Theta(1)$          |
| Insertion Sort | $\Omega(n)$       | $\Theta(n²)$      | $O(n²)$        | $\Theta(1)$          |
| Merge Sort     | $\Omega(n log n)$ | $\Theta(n log n)$ | $O(n log n)$   | $O(n)$               |

To aid in this quick assessment, it will help to bring in the graph from the Runtime Lesson:

![](../img/graph.png){width="650"; .center}

Looking at this graph and the table above, it makes the comparison of algorithms much easier. See if you come up with the same following conclusions based on the graph:

- **On average AND in the worst-case**, Merge Sort will beat the others as $n$ grows to be very large
- In the **best-case**, Insertion and Bubble are the best, showing they work best on almost sorted lists. Contrary to this Selection Sort remains quadratic, even with mostly sorted sequences.
- Even though Merge is the fastest computationally, it requires a linear growth of memory space, something that all the other sorts only need 1 of

For quick assessments of algorithms bring up their graphs and compare their time-complexities visually. For most problems you should:

1. Look for the worst-case time complexities (Big O)
2. Compare them by graphing
3. Pick the one that grows the slowest as it moves to the right

### Finding Dominant Components

The full breakdowns of finding $T(n)$ and then stripping away the constants and lower order growth factors can be tedious and time consuming if it has not been done for you, or if you are the one creating the algorithm. When analyzing an algorithm's time complexity, you don't need to count every single operation. Instead, look for the **dominant component**, the part that grows the fastest as input size increases. Here are some quick patterns to recognize:

- **Single loop through n items?** ->$O(n)$
- **Nested loops through n items?** -> $O(n²)$
- **Dividing problem in half repeatedly?** -> $O(log n)$
- **Loop that does log n iterations, each doing n work?** -> $O(n log n)$
- **No loops, just a few operations?** -> $O(1)$
#### Example 1: Linear Search

- **Algorithm**: Linear Search
    - **Inputs**: An array $A$ of $n$ numbers $[a_0, a_1, ..., a_{n-1}]$, and a target value $target$
    - **Output**: Index of $target$ in $A$, or $-1$ if not found
    - **Procedure**:
        1. $\text{for } i \gets 0 \text{ to } n-1 \text{ do:}$
            1. $\text{if } A[i] = target \text{ then:}$
                1. $\text{return } i$
            2. $\text{end if}$
        2. $\text{end for}$
        3. $\text{return } -1$

**Dominant Component**: The single loop that potentially visits all $n$ elements once.  
**Time Complexity**: $O(n)$

#### Example 2: Check for Duplicates (Naive)

- **Algorithm**: Has Duplicates
    - **Inputs**: An array $A$ of $n$ numbers $[a_0, a_1, ..., a_{n-1}]$
    - **Output**: $true$ if any duplicates exist, $false$ otherwise
    - **Procedure**:
        1. $\text{for } i \gets 0 \text{ to } n-1 \text{ do:}$
            1. $\text{for } j \gets i+1 \text{ to } n-1 \text{ do:}$
                1. $\text{if } A[i] = A[j] \text{ then:}$
                    1. $\text{return } true$
                2. $\text{end if}$
            2. $\text{end for}$
        2. $\text{end for}$
        3. $\text{return } false$

**Dominant Component**: The nested loops where the outer loop runs $n$ times and the inner loop runs up to $n$ times for each iteration.  
**Time Complexity**: $O(n²)$





