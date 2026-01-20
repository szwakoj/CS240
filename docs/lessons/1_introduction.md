# Introduction 

This course is concerned with the study of data structures and algorithms in computer science. This lesson serves as an introduction to some of the core concepts that we will be building on over the course of this semester. Here we cover:
- Computational Problems
- Algorithms Basics
- Introduce Data Structures
## Algorithms

What are algorithms? Algorithms have been at the core of your computer science journey since its beginning, however before understanding them more deeply, we must first know why they exist in the first place.

### Problems
Even in your most rudimentary programs, you can understand them as solutions to some problem, or at least attempts at them. These problems can be as simple as to sort a list, find a max, or calculate an average, or as complex as retrieving the correct webpage given a search, training artificial intelligence systems efficiently, or landing a drone. All of the previous can be formalized into computational problems; problems that specify constraints on an input-output relationship.

 One such problem we will be tackling is the **sorting problem**, usually defined as:
- **Plain English**
	- Take in a sequence of amount of numbers and produce a sequence of the same numbers in order of least to greatest
- **Formal Definition**
	- Input: An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$
	- Output: A permutation (reordering) $[ a^{\prime}_1 , a^{\prime}_2, ..., a^{\prime}_n ]$ of the input sequence such that $a^{\prime}_1 \leq a^{\prime}_2 \leq ... \leq a^{\prime}_n$

Sorting is a very important operation in computer science, many problems require or are more easily solved if a sequence is ordered. It would be a good idea to absorb the definition of the sorting problem as we will be programming it and solutions to it soon.

By formalizing the problem into a mathematical representation, we now have a general way of understanding the problem regardless of how we implement a check for it. The formal definition also gives a means of defining what a valid input is, or if something is an **instance** of the problem

A single **instance** of a problem is a single valid input that satisfies the constraints of the problem's intended inputs. Each instance is an example of a possible problem from the formal definition. For our previous problem:
- Instance of Sorting Problem
	- $\langle 70, 55, 86, 12, 72, 20, 31, 3 \rangle$
- Intended Output
	-  $\langle 3, 12, 20, 31, 55, 70, 72, 86\rangle$

### Algorithms as Solutions
How do we produce that intended output? Algorithms.
Algorithms are solutions to computational problems. They take in a possible instance of the problem and are expected to produce a valid output. The process of each algorithm is different but boils down into taking in an input, transforming it, and producing an expected output. The transformation is done using a discrete number of ordered computational steps.

In previous courses, you may have been introduced to algorithms as a set of steps that accomplish a certain task. Or you may have used algorithms as backbones for the logic of your code, using them as a means of aiding in the problem solving process. Whether you realized it or not, algorithms are what define programs. All programs are implementations of some algorithm. For example, take a look a the following algorithm for finding the max in a collection of numbers:
- Algorithm: Max Element
	- Inputs: An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$
	- Output: $a_m$ the maximum number in the sequence
	- Procedure:
		1. $max \gets A[0]$
		2. $\text{for } i \gets 0 \text{ to } n -1 \text{ do:}$
			1. $\text{if } A[i] > max \text{ then:}$
				1. $max \gets A[i]$
			2. $\text{end if}$
		3. $\text{end for}$
		4. $\text{return } max$
This algorithm could be written in any programming language:
```python
# Python Max Element
def max_element(A):
	cur_max = A[0] 
	
	for i in range(len(A)):
		if A[i] > cur_max:
			cur_max = A[i]
	
	return cur_max
```
```C
// C Max Element
int max_element(int n, int A[n])
{
	int cur_max = A[0];
	
	for(int i = 0; i < n; i++) {
		if (A[i] > cur_max) {
			cur_max = A[i];
		}
	}
	
	return cur_max;
}
```

In the pseudo code above, you may notice that the algorithm is defined along with the problem it is meant to solve, showing their relationship.
### Assessing Algorithms

Say we have the following problem:
- **Plain English**
	- Linear Search: Find the index of a certain value in an array, return -1 if it does not exist
- **Formal Definition**
	- Input: 
		- An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$
		- Target number $t$
	- Output:  The smallest index $\text{i where } A[i]=t, or −1$ if no such index exists

How would we assess two different algorithms that reportedly solve it?

One way would be to check its correctness, or whether or not the algorithm can solve every instance of a problem. Algorithms that halt with the correct output for every input instance are said to be **correct** and **solves** the given computational problem. That word "halt" refers the requirement that a correct algorithms must terminate in finite time. A correct algorithm cannot sometimes give a correct answer on a given instance, and sometimes run infinitely as a possibility, it must stop.

Algorithms can be **incorrect** and solve only a subset of the possible instances of a computational problem. In these cases, we can assess what percentage of cases the algorithm solves for. While it may seem nonsensical and undesirable to have an algorithm that doesn't always work, there are times it can be beneficial, we will take a look at those at a later date. For the short-term, we will mostly be looking at algorithms that **solve** certain computational problems completely and are correct. 

Let's compare the correctness of two algorithms:
- Algorithm: 404 Not Found
	- Input: 
		- An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$
		- Target number $t$
	- Output: -1
	- Procedure:
		- $\text{return } -1$

- Algorithm: Linear Search
	- Input: 
		- An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$
		- Target number $t$
	- Output:  The smallest index $\text{i where } A[i]=t, or −1$ if no such index exists
	- Procedure:
		1. $\text{for } i \gets 0 \text{ to } n-1 \text{ do:}$
			1. $\text{if } A[i] = t \text{ then:}$
				1. $\text{return } i$
			2. $\text{end if}$
		2. $\text{end for}$
		3. $\text{return } -1$

Obviously, "404 Not Found" is an incomplete algorithm, it always assumes that the target number is not in the input array. For Linear Search, however, we can be pretty sure that it will work for all instances of the problem. There are ways to test this, and we will take a look at those at a later date.

Another way to assess an algorithm, is by how fast it runs. While it may not be true 100% of the time, in instances where the target number is not within the input array, "404 Not Found" will be faster than "Linear Search". 

No mater what input array given, "404 Not Found" will produce an output in a single computational step. If that computational step took 1 second, no matter the size of $n$, or the size of the input array, "404 Not Found" will always take 1 second to complete. "Linear Search" on the other hand requires many more computational steps to complete. Mainly, it loops through each element of the array until the end in the event of the target not existing. At each iteration of the loop there is a comparison operation, if we take the 1 second time estimate from before then we get a time of $n$ seconds if the target doesn't exist. 

While this is a simple example, this process can be done on any algorithm and estimate its so called time complexity, a future topic.
## Data Structures

Each of the previous examples works on some form of data. Mostly **arrays**, or ordered numbers in a set size of contiguous memory. This will be covered more in [C Review](docs/lessons/2_reviewing_c.md) and later in the data structures lessons, but it means that all data is stored physically next to each other. This creates some limitations with working with it as a medium of data in an algorithm. For example, to remove an element, all elements to the right of it must be shifted down by one in order to fill the empty space left by the removed element. This can be computationally expensive if you are removing and adding elements very quickly to different parts of the array during the run of an algorithm. In other cases, the way you represent the data can make solving problems faster.

The way you represent data for a given problem is called the **data structure**. **Data structures** are methods of storing and organizing data in some medium that allows for easy access and modification. Choosing the correct data structure has the possibility of trivializing the design of algorithms and the capability to make them for efficient.

We will cover many data structures in the course this semester. Some highlights will be:
- Arrays and Dynamic Arrays
- Linked Lists
- Stacks and Queues
- Trees
- Hash tables
- Graphs
Each one will become a well acquainted tool that you will use to deconstruct and solve problems effectively. In the short term we will be looking at algorithms first, for now, use this section as a means of introducing the idea and begin thinking about how the form of data can lend to problem solving.


