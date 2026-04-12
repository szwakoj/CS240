#  Unit 2 Test Review Questions

## Due: 4/19/26

## Description

This HW will serve as a review of the material thus far and have questions to prepare you for the upcoming exam. "Unit 2: Data Structures" was centered on introducing the formal study of data organization, the properties that distinguish different structures, and the tradeoffs each structure makes in terms of time and space. These topics will be the primary focus along with the material online it is associated with:

- Primitives vs Data Structures, Homogeneous vs Heterogeneous, Records
    - [Data Structures: Primitives and Composite Types](../lessons/5_data_structs1.md)
- Linear vs Non-Linear, Arrays, Strings, Static vs Dynamic Memory, Dynamic Arrays
    - [Data Structures: Linear Structures I](../lessons/6_data_structs2.md)
- Stacks, Queues, Linked Lists, Doubly Linked Lists
    - [Data Structures: Linear Structures II](../lessons/7_data_structs3.md)

The test will have True/False, Multiple Choice, Short Answer, Fill-in-the-Blank, and Complexity Analysis type questions. They will all be based on these short answer questions. Answer each to the best of your ability and use the material and in-class notes to fill in any gaps you find you have. This is meant to be a graded review - simply looking up answers without understanding will not prepare you for the exam. Try your best and ask questions during class time.

---

## Section 1: Primitives, Data Structures, and Records - /30 pts

**1. (4 pts) | ~3-4 sentences** What is the difference between a **primitive** and a **data structure**? Give two examples of each in C and explain what makes each category distinct.



**2. (4 pts) | ~3-4 sentences** What does it mean for a data structure to be **homogeneous**? What does it mean for it to be **heterogeneous**? Give one example of each and explain why the distinction matters.



**3. (4 pts) | ~3-4 sentences** What is a **record**? List its four fundamental traits and briefly describe each one.



**4. (4 pts) | ~2-3 sentences + example** What is a **fixed schema**? Why is this property important, and how does it manifest in C's `struct`?



**5. (4 pts) | ~3-4 sentences** What is the difference between a C `struct` and the theoretical concept of a record? When does a `struct` go beyond what a record defines?



**6. (4 pts) | ~3-4 sentences** Explain **shallow copying** in C. Why is it a problem when copying `struct`s that contain arrays or string fields, and what is the correct approach?



**7. (6 pts - 2 pts each)** Match each term to its correct definition by filling in the table:

|Term|Definition|
|---|---|
|Primitive||
|Record||
|Heterogeneous Data Structure||

**Definitions (use each once):**

- A composite structure with a fixed set of named fields, each of which may be a different type, all grouped under a single identity
- A basic data type provided directly by the target system, such as `int`, `char`, or `double`
- A data structure that can store elements of more than one type within a single instance

---

## Section 2: Linear Structures I - Arrays, Strings, and Dynamic Memory - /35 pts

**1. (4 pts) | ~3-4 sentences** What is the difference between a **linear** and a **non-linear** data structure? Give one example of each and describe what property of the data makes one a better fit than the other.



**2. (4 pts) | ~3-4 sentences** What are the three defining properties of an array? How does each property relate to the performance of array operations?



**3. (4 pts) | ~3-4 sentences** What is a **sentinel value**? How do strings in C use a sentinel value, and what practical advantage does this provide when passing strings as pointers?



**4. (6 pts - 1 pt each)** For the array operation below, fill in the time complexity and a one-sentence justification for each:

|Operation|Time Complexity|Justification|
|---|---|---|
|Access by index|||
|Append to end (space available)|||
|Insert at middle|||
|Delete from middle|||
|Search for a value|||
|Copy entire array|||



**5. (4 pts) | ~3-4 sentences** What is the difference between **stack memory** and **heap memory**? What are the tradeoffs of each, and which C functions are used to allocate and release heap memory?



**6. (4 pts) | ~3-4 sentences** What is a **memory leak**? When does it occur in C, and what is its effect on a running program?



**7. (4 pts) | ~3-4 sentences** What is a **dynamic array** and how does it solve the limitation of a static array? Describe the resize strategy covered in the lesson and explain why that specific strategy keeps the amortized cost of append at O(1).



**8. (5 pts)** The table below shows the time complexity for operations on a **static array** versus a **dynamic array**. Fill in the missing entries and answer the question that follows.

|Operation|Static Array|Dynamic Array|
|---|---|---|
|Access by index|O(1)||
|Append (with room)|O(1)||
|Append (resize needed)|N/A||
|Append (amortized)|N/A||
|Insert / Delete middle|O(n)||
|Search for value|O(n)||

**a. (1 pt)** What is the key structural difference between a static array and a dynamic array in terms of where their memory lives?


---
## Section 3: Linear Structures II - Stacks, Queues, and Linked Lists - /35 pts

**1. (4 pts) | ~3-4 sentences** What is a **stack**? Describe its ordering property, name its two primary operations, and give one real-world use case where a stack is the natural choice.



**2. (4 pts) | ~3-4 sentences** What is a **queue**? Describe how it differs from a stack in terms of ordering, name its two primary operations, and give one real-world use case where a queue is the natural choice.



**3. (4 pts) | ~3-4 sentences** A queue is often implemented internally as a **circular buffer**. What problem does this solve, and how does the modulo operator enable it? What role does the `size` field play in this implementation?



**4. (6 pts - 2 pts each)** Fill in the table comparing stacks and queues:

|Property|Stack|Queue|
|---|---|---|
|Ordering principle|||
|Add operation name|||
|Remove operation name|||
|Time complexity of add|||
|Time complexity of remove|||
|Example use case|||



**5. (4 pts) | ~3-4 sentences** What is a **linked list** and how does it differ from an array in terms of how elements are stored in memory? What operation does this structural difference make faster, and what operation does it make slower?



**6. (4 pts) | ~2-3 sentences + example** What does it mean to "rewire" pointers when inserting or removing a node in a linked list? Describe the steps required to insert a new node between two existing nodes.



**7. (4 pts) | ~3-4 sentences** What is a **doubly linked list**? What two capabilities does it add over a singly linked list, and what are the costs of those additions?



**8. (5 pts)** The table below compares singly and doubly linked lists. Fill in the missing entries:

|Operation|Singly Linked List|Doubly Linked List|
|---|---|---|
|Prepend|O(1)||
|Append|O(n)||
|Remove front|O(1)||
|Remove back|O(n)||
|Remove given a pointer to the node|O(n)||
|Traversal direction|Forward only||
|Memory per node|1 extra pointer||

**a. (1 pt)** What field must be added to the list struct itself (not just the node) to achieve O(1) append in a doubly linked list?



**9. (4 pts)** The table below summarizes the time complexity of linked list operations. A few entries have been left blank. Fill them in and answer the follow-up question.

|Operation|Time Complexity|Notes|
|---|---|---|
|Prepend|O(1)|HEAD pointer update only|
|Append||Must traverse to the tail|
|Insert at index|O(n)|Traverse to index - 1|
|Remove front||HEAD pointer update only|
|Remove back / at index|O(n)|Must traverse to find the node|
|Access by index|O(n)||
|Search by value||Linear scan|

**a. (1 pt)** Arrays have O(1) access by index while linked lists do not. In one sentence, explain the structural reason for this difference.

---

## Section 4: Synthesis and Comparison - / 10 pts

**1. (4 pts) | ~3-4 sentences** You are designing a system that receives a stream of incoming tasks and must process them in the order they arrive, but also occasionally needs to cancel the most recently added task before it is processed. Which single data structure would you choose to handle both requirements, or would you use a combination? Justify your answer.



**2. (3 pts) | ~3-4 sentences** A classmate argues that a dynamic array is always better than a linked list because it supports O(1) amortized append and O(1) random access, while a linked list's append is O(n). Give one concrete scenario where a linked list would still be the better choice and explain why.



**3. (3 pts)** For each scenario below, identify the most appropriate data structure from those covered in this unit and give a one-sentence justification:

| Scenario                                                                     | Best Structure | Justification |
| ---------------------------------------------------------------------------- | -------------- | ------------- |
| A browser's back/forward history                                             |                |               |
| A print spooler that processes jobs in arrival order                         |                |               |
| A music playlist where songs are stored with title, artist, year, and rating |                |               |


## Point Summary

| Section                                             | Points   |
| --------------------------------------------------- | -------- |
| Section 1: Primitives, Data Structures, and Records | /30      |
| Section 2: Linear Structures I                      | /35      |
| Section 3: Linear Structures II                     | /35      |
| Section 4: Synthesis and Comparison                 | /10      |
| **Total**                                           | **/110** |