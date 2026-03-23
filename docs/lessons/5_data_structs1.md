
# Data Structures: Primitives and Composite Types

This lesson introduces the building blocks of data organization. We establish 
the difference between primitives and data structures, introduce the 
homogeneous/heterogeneous distinction, and cover the simplest heterogeneous 
structure: the record. Later lessons will build on this foundation to cover 
linear and non-linear data structures and their implementations.

In this lesson:

- Primitives vs Data Structures
- Homogeneous vs Heterogeneous Structures
- Records

## Data Structures

Before going into the common structures that you will be confronted within your coding, let's differentiate a little:

- **Primitives**: The basic data types that we have access to on the target system
	- `int`, `char`, `float` and `double`, and pointers in C
	- both `signed` and `unsigned`, and the additions in the standard like `int16_t` in `stdint.h`
- **Data Structures**: Collections of primitives **or other data structures** that organize information in a way that aids in the process of solving a problem
	- Arrays are one of the more fundamental data structures as it is a collection of a single type stored physically next to each other
	- Pointers can point to anything are are sometimes thought of as data structures as a result
		- In C++, there are different kinds of pointers and makes those implementations as distinct data structures
	- `struct`'s are C's make way of creating data structures

This creates a division and a conceptual framework to think about data structures; we are organizing grouped primitives in a way that makes certain operations easier.

By "easier" I mean any of the following:

- More efficient computationally
- More conservative on space, and/or
- Make programming simpler 

Data structures are meant to be tools for aiding in the processes of programming and algorithmic design. The way we organize data in memory and within a program can drastically help with certain types of problems being solved on a computer, especially when we consider the above ways data structures can make life better.

Algorithms work on either primitives or data structures as input. When designing data structures we often also design the algorithms intended to work on it. For example, since array elements are stored physically next to each other in memory it is extremely fast to access any variable given its first element's location:

```c
int array[] = {1, 2, 3};

// Remember these are the same
printf("%d\n", array[2]);
printf("%d\n", *(array+2));
```

Here, we are showing that array access is just pushing the pointer forward in memory. This means we do not need to look up the location of element 2, it is simply 2 integer spaces forward from the first. We can think about the "access algorithm" as follows:

- Algorithm: Array Element Access
    - Inputs: An array $A$ of $n$ elements $[a_0, a_1, \dots, a_{n-1}]$, a base address $\text{base}$, element size $s$, and index $i$ where $0 \leq i < n$
    - Output: $a_i$, the element at index $i$
    - Procedure:
        1. $\text{address} \gets \text{base} + (i \times s)$
        2. $\text{return } *\text{address}$

While this may seem common sense, other data structures that do not take from arrays basic structure may store values all over a computer, requiring the creation of specialized algorithms for things as simple as element access.

An array is the simplest example of a **homogeneous data structure** as they are collections of the same type of data one after another in memory. **Heterogenous data structures** are structures that contain different types of data under its organization scheme. The simplest version of this is called a **record**.
### Data Structure: Records

A **record** is a composite data structure consisting of a fixed set of named fields, where each field can be a different type, that are all contained under the same identity. Their fundamental traits are:

- **Fixed schema**: The types, names, and number of fields is fixed and cannot be changed after creation and are defined before a program is ran
- **Named access**: Each field is accessed via an internally unique name that associates labels with the specific data
	- This means that the locality of the data does not need to be next to each other in memory, implementations vary in this, C lays `struct` fields next to each other in memory, but a record does not define this
- **Heterogenous**: fields can be different types
- **Finite and bounded**: There is a known and fixed number of fields and therefore memory taken up by the structure 

A C `struct` is a low-level implementation of a record that allows one to store multiple data types under the same structure. A record is a theoretical concept that can be implemented using C `struct`'s, however `struct`'s can be used for more complex data types as well. Some programming languages create specific language features implementing theoretical structures directly and by name (Pascal, Haskell, and Elm).

Here is a `struct` record for a song in a music playlist in C:

```C
typedef struct {
	char title[64];
	char artist[64];
	int release_year;
	double rating;
} Song;
```

**Note**: `typedef` in C is the type definition keyword and is how we create new named data types. If  it is omitted, every time one uses the struct, it will require `struct Song` rather than just `Song`. For this lesson and in the future, it will be used and not explained to make code more concise. 

Here are the basic operations on the record:

**Creation**:

```C
// Uninitialized
Song s;
// Give data later
strcpy(s.title, "A Decade in Blue (Da Ba Dee)");
strcpy(s.artist, "Eiffel 65");
s.release_year = 1999
s.rating = 8.0;

// Initalized Variants
Song s = {"Title", "Artist", 2000, 8.4};

Song s = {
	.title = "Ultimate Showdown",
	.artist = "Lemon Demon",
	.release_year = 2006,
	.rating = 9.7
};
```

**Access/Modification:**

```C
Song s = {"Title", "Artist", 2000, 8.4};

printf("Song info: %s, %s, %d, %lf\n", s.title, s.artist, s.release_year, s.rating);

s.rating -= 0.4;

strcpy(s.title, "New Title");
```

**Copying (In C)**

C does arrays and strings by pointers and by nature all of C's copying behavior is done by value rather than by reference. This means this situation is common and why `strcpy()` exists:

```C
// INCORRECT WAY
char* str1 = "This is String 1";
char* str2 = "String 2 is over here";

str1 = str2;

printf("Str1 = %s\n", str1); // Prints "String 2 is over here"
printf("Str2 = %s\n", str2); // Prints "String 2 is over here"

// All good right? WRONG!

str1[7] = '1' // Changing the "2" to a "1" for str1

printf("Str1 = %s\n", str1); // Prints "String 1 is over here"
printf("Str2 = %s\n", str2); // Prints "String 1 is over here"

// CORRECT WAY
char str1[32] = "This is String 1";
char str2[32] = "String 2 is over here";

strcpy(str1, str2);
```

This is called **shallow copying** — copying the reference rather than the data it points to. This extents to `struct`'s meaning we need to copy array and string fields element by element using loops or `strcpy()` each time or through a function:

```C
// Stock struct, stores ticker and last week of prices
typedef struct {
	char ticker[6];
	double week_prices[7];
} Stock;
// Pointers so we can edit data in place
void stock_copy(Stock* dest, Stock* src)
{
	// Copy ticker by element
	strcpy(dest->ticker, src->ticker);
	// Copy prices by element
	for(int i = 0; i < 7; i++){
		dest->week_prices[i] = src->week_prices[i];
	}
}
```

**Note**: Those arrows, `->`, are dereference access operators. This are effectively dereferencing and then accessing the field you need. `dest->ticker` is equivalent to `(*dest).ticker`. More on this in the lab on structs, arrays and strings.

Records do not have other operations on them generally, other than maybe a print or output operation. This makes them a structure that is used by other data structures that allow for further collection of multiple records.  

Records on their own are not particularly powerful — their value comes from being the atom that larger structures are built from. A linked list is a chain of records. A queue is a managed collection of records. A hash table is an array of records. Understanding what a record is and how C represents it in memory is the foundation for everything that follows.

The next lesson introduces **linear data structures** — structures where elements have a defined sequential order. We will look at what makes a structure linear, contrast it with non-linear structures, and then dig into the most fundamental linear structure you will use: the array.