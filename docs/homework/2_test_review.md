# Unit 1 Test Review Questions

## Due: 3/13/26

### Description

This HW will serve as a review of the material thus far and have questions to prepare you for the upcoming exam. "Unit 1: Algorithms and Runtime Analysis" was centered on introducing the formal study of algorithms, how we measure their efficiency, and the mathematical tools we use to compare them. These topics will be the primary focus along with the material online it is associated with:

- Algorithms and Computational Problems
    - [Introduction](../lessons/1_introduction.md)
- Runtime Analysis
    - [Runtime Analysis Fundamentals](../lessons/3_runtime.md)
- Asymptotic Notation
    - [Asymptotic Notation](../lessons/4_big_o.md)
- Algorithm Breakdowns
	- [Insertion Lab](../labs/1_insertion_breakdown.md)

The test will have True/False, Multiple Choice, Short Answer, Fill-in-the-Blank, and Runtime Analysis type questions. They will all be based on these short answer questions. Answer each to the best of your ability and use the material and in-class notes to fill in any gaps you find you have. This is meant to be a graded review, simply looking up answers without understanding will not prepare you for the exam, try your best and ask questions during class time.

---

## Section 1: Algorithms and Computational Problems - /30 pts

**1. (4 pts) | ~3-4 sentences** What is a computational problem? What are the two parts of its formal definition and what does each specify?

---

**2. (4 pts) | ~3-4 sentences** What is an algorithm? How does it relate to a computational problem, and how does it relate to a program?

---

**3. (4 pts) | ~3-4 sentences** What does it mean for an algorithm to be **correct**? What is required beyond just producing the right output sometimes?

---

**4. (4 pts) | ~2-3 sentences + example** What is an **instance** of a problem? Give an example instance for the sorting problem.

---

**5. (4 pts) | ~3-4 sentences** What is the difference between a **deterministic** algorithm and a **probabilistic** algorithm? Which type do we primarily focus on in this course and why?

---

**6. (4 pts) | ~3-4 sentences** Consider two algorithms for the Linear Search problem: one that always returns -1 to indicate that the target is not in the sequence always, and one that actually searches the array. Are both of them correct? Explain what percentage of instances each one solves.

---

**7. (6 pts - 2 pts each)** Match each term to its correct definition by filling in the table:

|Term|Definition|
|---|---|
|Computational Problem||
|Algorithm||
|Instance||

**Definitions (use each once):**

- A single valid input that satisfies the constraints of a problem's intended inputs
- A formal specification of an input-output relationship with defined constraints
- A finite sequence of ordered steps that transforms a valid input into the correct output

---

## Section 2: Runtime Analysis - /35 pts

**1. (4 pts) | ~3-4 sentences** Why don't we measure the runtime of an algorithm by simply timing how long a program takes to run on a computer? What do we measure instead?

---

**2. (4 pts) | ~3-4 sentences** What is **input size**? Is it always the number of elements in an array? Give an example where it is not.

---

**3. (4 pts) | ~3-4 sentences** What is the **worst-case** runtime of an algorithm? What is the **best-case**? Why do we typically focus on the worst-case?

---

**4. (6 pts - 1 pt each)** For the algorithm below, fill in the number of times each
step executes for an input array of size $n$ in the **worst case**:

- **Algorithm: Count Inversions (Naive)**
    - **Input:** An array $A$ of $n$ numbers $[a_0, a_1, ..., a_{n-1}]$
    - **Output:** The number of pairs $(i, j)$ where $i < j$ but $A[i] > A[j]$
    - **Procedure:**

| No. | Step | $c_i$ | Number of Times |
|---|---|---|---|
| 1 | $count \gets 0$ | $c_1$ | |
| 2 | $\text{for } i \gets 0 \text{ to } n-1 \text{ do:}$ | $c_2$ | |
| 3 | $\quad \text{for } j \gets i+1 \text{ to } n-1 \text{ do:}$ | $c_3$ | |
| 4 | $\quad\quad \text{if } A[i] > A[j] \text{ then:}$ | $c_4$ | |
| 5 | $\quad\quad\quad count \gets count + 1$ | $c_5$ | |
| 6 | $\quad\quad \text{end if}$ | $0$ | |
| 7 | $\quad \text{end for}$ | $0$ | |
| 8 | $\text{end for}$ | $0$ | |
| 9 | $\text{return } count$ | $c_9$ | |

---

**5. (4 pts)** Using the step counts from Question 4 and constants $c_1$ through $c_5$, write out the full runtime function $T(n)$ for the Count Inversions (Naive) algorithm (worst-case). Then simplify it by extracting out the constants.

---

**6. (5 pts) | ~4-5 sentences** What is a **dominant component** of a runtime function? In the function $T(n) = 3n^2 + 50n + 200$, which is the dominant component and why? What happens to the other terms as $n$ grows very large?

---

**7. (4 pts)** Two algorithms solve the same problem. Algorithm A has a runtime of $T(n) = 100n + 500$ and Algorithm B has a runtime of $T(n) = 2n^2 + 3$. Which is faster for small inputs? Which is faster for large inputs? Show your work.

| |Algorithm A: $100n + 500$|Algorithm B: $2n^2 + 3$|
|---|---|---|
|$n = 5$|||
|$n = 1000$|||

---

**8. (4 pts) | ~2-3 sentences** List the main growth function types covered in class from slowest to fastest growth. Why does the dominant component determine the long-term behavior of a runtime function?

---

## Section 3: Asymptotic Notation - /35 pts

**1. (4 pts) | ~3-4 sentences** What is asymptotic notation? What two things does it discard from a full runtime function $T(n)$, and why is it okay to discard them?

---

**2. (6 pts - 2 pts each)** Fill in the table defining the three main asymptotic notations:

|Notation|Name|Describes|Bound Type|
|---|---|---|---|
|$O(g(n))$||||
|$\Omega(g(n))$||||
|$\Theta(g(n))$||||

---

**3. (4 pts) | ~2-3 sentences** When would you use Big Theta ($\Theta$) instead of Big O ($O$) to describe an algorithm's complexity? Give an example of an algorithm where the best and worst case growth are the same.

---

**4. (6 pts - 2 pts each)** Identify the time complexity (Big O) of each code snippet. Justify each answer in one sentence.

**a.**

```c
int sum = 0;
for (int i = 0; i < n; i++) {
    sum += arr[i];
}
```

**Complexity:** ____________ | **Justification:**

---

**b.**

```c
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        printf("%d %d\n", i, j);
    }
}
```

**Complexity:** ____________ | **Justification:**

---

**c.**

```c
int x = arr[0] + arr[n-1];
printf("%d\n", x);
```

**Complexity:** ____________ | **Justification:**

---

**5. (5 pts)** The table below shows common sorting algorithms and their complexities. Use it to answer the questions that follow.

|Algorithm|Best Case|Average Case|Worst Case|Space|
|---|---|---|---|---|
|Bubble Sort|$\Omega(n)$|$\Theta(n^2)$|$O(n^2)$|$\Theta(1)$|
|Selection Sort|$\Omega(n^2)$|$\Theta(n^2)$|$O(n^2)$|$\Theta(1)$|
|Insertion Sort|$\Omega(n)$|$\Theta(n^2)$|$O(n^2)$|$\Theta(1)$|
|Merge Sort|$\Omega(n \log n)$|$\Theta(n \log n)$|$O(n \log n)$|$O(n)$|

**a. (1 pt)** Which algorithm is best in the worst-case for large inputs?

**b. (1 pt)** Which algorithms perform best on a nearly-sorted list? Why?

**c. (1 pt)** What tradeoff does Merge Sort make compared to the other three?

**d. (2 pts) | ~2 sentences** Why does Selection Sort remain $\Omega(n^2)$ in the best case when Bubble Sort and Insertion Sort do not?

---

**6. (4 pts) | ~3-4 sentences** Without doing a full $T(n)$ breakdown, how can you quickly estimate the Big O time complexity of an algorithm by looking at its structure? Describe the patterns to look for and the complexity class each implies.

---

**7. (2 pts) | ~1-2 sentences** What is **space complexity**? What notation do we use to describe it, and what does it measure?

---

## Point Summary

|Section|Points|
|---|---|
|Section 1: Algorithms and Computational Problems|/30|
|Section 2: Runtime Analysis|/35|
|Section 3: Asymptotic Notation|/35|
|**Total**|**/100**|