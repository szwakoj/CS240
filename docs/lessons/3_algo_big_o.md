# Algorithms and Big O

Knowing that algorithms solve problems might be a common sense statement to make. However, what happens when we have two algorithms that appear to solve the same computational problem? Which do we choose? How do we compare them? 

These are all of the concerns answered by Big O Notation, the measure of how much time it takes for an algorithm to run, given the input size. Here, we will:

- Gain the intuition of Big O Notation
- See common patterns of growth
- Compare two algorithms
- and measure both time and space complexity

## Algorithms

To review briefly:

- Computational problems are formal definitions of problems that outline the intended input and the desired output
- Algorithms are solutions to computational problems that use a finite number of sequential steps to go from input to desired output
- Programs are implementations of algorithms 
- The most basic way to assess an algorithm is to measure how many of the possible inputs can be solved using it, if it solves all problem instances, it is said to be correct. It is incorrect if it does not solve for one or more instances of the problem space

Now that the background is laid, we need to consider other ways of assessing algorithms, especially in terms that relate to programs and the domain we are solving in, digital computers. When speaking about modern computers, there are two basic attributes that dictate how good a computer is viewed in the modern day:

- **Execution Speed:** How fast operations are being executed
- **Memory Size:** How much space do we have to store information

In the same light, we assess the programs we use in these terms too. If a program is too slow, or uses too much RAM, we do not like it and identify it as a problem. Computers have gotten so good that we assume that all algorithms/programs are correct, it is just a matter of speed and resources. 

> [!NOTE] Correctness Vs Other Metrics
> While correctness is probably the most important aspect of an algorithm, we will always be attempting to make algorithms completely correct by default. This shifts the focus to those two attributes above. In fact, in most formal definitions algorithms are assumed to be correct. This lead to the division between **deterministic algorithms**; algorithms that have completely predicable behavior, always producing the same, correct output for any given input. And **probabilistic algorithms**; algorithms that use randomness in their execution, which means their correctness, runtime, or memory usage may vary between runs even with identical inputs. We mainly focus on pure, correct, deterministic algorithms, but by the end of the semester we will see some probabilistic algorithms.

### Input Size

This this in mind, how do we measure the time an algorithm takes or how much memory it takes up? To begin to tackle this, we should identify that the size of the input matters a lot for both of these metrics.

**Input size** depends on the problem being solved. For the problems we covered before like search, finding a max, or sorting, the input size is the amount of items in the input array/list. Take the finding max example from before:

- Algorithm: Max Element
	- Inputs: An array $A$ of $n$ numbers $[ a_0 , a_1, ..., a_{n-1} ]$, where $n > 0$
	- Output: $a_m$ the maximum number in the sequence
	- Procedure:
		1. $max \gets A[0]$
		2. $\text{for } i \gets 0 \text{ to } n -1 \text{ do:}$
			1. $\text{if } A[i] > max \text{ then:}$
				1. $max \gets A[i]$
			2. $\text{end if}$
		3. $\text{end for}$
		4. $\text{return } max$

Here the input size is noted with $n$, as $n$ increases, the algorithm will need to run more times, since its for loop is bounded by $n-1$.  However, input size does not need to be connected to the number of elements in an array, it could be the size of the numbers coming in, take the following algorithm for two binary numbers being added: 

- Algorithm: Binary Addition 
	 -  Inputs: Two binary numbers $A$ and $B$ of $n$ bits each, $A = [a_{n-1}, a_{n-2}, ..., a_0]$ and $B = [b_{n-1}, b_{n-2}, ..., b_0]$ 
	 -  Output: Binary number $C$ representing $A + B$ 
	 - Procedure: 
		 1. $carry \gets 0$ 
		 2. $C \gets \text{empty array of size } n+1$ 
		 3. $\text{for } i \gets 0 \text{ to } n-1 \text{ do:}$ 
			 1. $sum \gets a_i + b_i + carry$ 
			 2. $C[i] \gets sum \mod 2$ 
			 3. $carry \gets \lfloor sum / 2 \rfloor$ 
		 4. $\text{end for}$ 
		 5. $C[n] \gets carry$ 
		 6. $\text{return } C$

Here we add two numbers always, but their sizes deem how long the algorithm runs. So its not always about lists or collections alone, but the size of the data being represented.

### Runtime of Algorithms

We keep talking about the amount of time it takes an algorithm to run or if an algorithm is slow or fast, how can we measure that? Is it just the time it takes for the program implementing an algorithm to run on some computer? Let's test this, say we have two programs that implement the same algorithm and are given the same input. Further imagine that we have Computer A and Computer B. If we run both programs on Computer A, they will take the same amount of time to run, lets say 5 microseconds. We then move one copy of the program to Computer B and then race the two computers running the same program on the same input as before. We get the following results: 
  
- **Results**
	- Program on Computer A = 5 microseconds
	- Program on Computer B = 10 microseconds

Without knowing about the specs of A or B, we can see that B probably is a worse computer. However, which number would we use as the runtime for our algorithm given the input? What would happen if we programmed them in a different language that sped up or slowed down the program?

These questions are the reason why the runtime of an algorithm is not usually measured using the physical time it takes for an algorithm to generate an output for a given input. It is completely dependent on the implementation of the algorithm and where it is being ran, which makes it not the best metric for these abstract, almost universal algorithms. 

To attend to this nature, the **run time (or running time)** of an algorithm on a particular input 

## Growth of Functions

### Recurrence 

## Big O Notation

