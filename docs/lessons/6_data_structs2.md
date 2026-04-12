# Data Structures: Linear Structures I

After learning about the basics of data structures as opposed to primitives, we now will cover another distinction between data structures, linear vs non-linear. This is a distinction between how data is stored, either sequentially or hierarchically/in a network. We then relate this concept to known structures in C by default and extensions on them for more flexible programming. 

In this lesson we will cover:

- Linear vs Non-Linear Data Structures
- Arrays and Strings Formally
- Static and Dynamic Memory
- Dynamic Arrays

##  Linear vs Non-Linear Data Structures

Data structures are defined not just by what they store, but by how they organize it. Every data structure has a set of properties that describe its shape, its rules, and the guarantees it makes to the programmer. In the previous lesson we saw our first two: **homogeneity**, whether a structure holds one type or many, and **schema**, whether the structure's layout is fixed or flexible. These properties determined everything about how records behave and what operations make sense on them. As we encounter more structures, we will keep building this vocabulary. The next property we introduce cuts across nearly every structure you will work with: whether the data is organized **linearly** or **non-linearly**.

If one requires a homogenous data structure that stores many of the same type, there are two ways of organizing that data; either sequentially or without a successive ordering. To demonstrate this idea, think about how you would store friends on a social media platform. Each profile has some number of characteristics and are friends with other profiles. If we wanted to store the friends of a single person it makes sense to store them in a structure that allows for them to be ordered, like by how long someone knows them, number of interactions, or by popularity. So an array of profiles would make sense to display a user's friends to them:

```C
typedef struct Profile {
	char name[32];
	char user_name[32];
	char bio[256];
	// struct and pointer needed to make list of its own type
	struct Profile* friends[256]; 
} Profile;

// Social network as an array of people
Profile social_network[2048];
```

That works for a single user's display page, but what if we wanted to store the entire social network and keep track of who is friends with who? If we relied on this and wanted to see whether two people are connected, or find the shortest path between two users through mutual friends, we would have to search every profile's friends array, and every one of their friends' arrays, branching outward in every direction with no structure to guide us. The data has a natural shape, a web of connections, and an array is the wrong container for that shape.

This is how we distinguish between **linear** and **non-linear** data structures. Linear data structures are organized to be accessed and thought of as sequential collections of similar data. This means that there is an ordering to the elements and they are organized in a manner the reflects this. **Non-linear** data structures are ones that organize their elements without a strictly sequential ordering rather with one that reflects the relationships that the elements have. Linear structures have a notions of first, last, next, previous, but non-linear structures do not. There is no inherent ordering and all elements can only be viewed in relation to one another. In non-linear instead of first or last, we have root and leaves. Instead of next or previous, we have parent and children.

![](../img/lin_ds_light.png#only-light)
![](../img/lin_ds_dark.png#only-dark)

We will first cover the linear data structures as they are fundamental in understanding modern computer systems and will be the main means that computers interface with data for the foreseeable future. Non-linear structures are used everywhere currently and are integral for being an efficient programmer, however they were developed after the linear structures and in response to their short comings. Some basics of each are in the image above but to reiterate:

- **Linear Data Structures**
	- Arrays/Strings
	- Linked Lists
	- Stacks
	- Queues
- **Non-Linear Data Structures**
	- Trees
	- Graphs
	- Hash Tables

This lesson we will review the basic static arrays and strings that you have been using in C and then show how they can be extended and made dynamic.


## Arrays and Strings

**Arrays** are defined to be sequential collections of the same typed data stored in contiguous  memory. This means arrays:

- are ordered - **Linear**
- must contain elements of the same type - **Homogenous**
- store elements physically in order - **Consecutive Memory**
![](../img/arrays_1_light.png#only-light)
![](../img/arrays_1_dark.png#only-dark)

Array contents are accessed via the index the element is in. The idea is that since we always know where the data is we can access it immediately if we know where the first element is. This is similar to how we can easily add and remove elements at the end of the array, so called append and pop operations so long as there is enough space reserved. This however leads to the fact that we cannot know where a certain value is at any given moment. In order to see where a particular value is inside of an array, or to check for its existence, one must check element by element. This is because we can always know *where* each element is specially, just not *what* each element is currently. Another complication arises if we want to insert or delete somewhere in the middle of the array. Since the array is ordered and physically next to each other we must shift elements to account for the reordering.

![](../img/arrays_2_light.png#only-light)
![](../img/arrays_2_dark.png#only-dark)
This reordering is something that must be accounted for for all linear types if they allow for insertions and deletions. 

## Arrays in C

**Creation, Access, In-Place Mutation**
```c
int numbers[5] = {10, 20, 30, 40, 50};

// Access elements by index (zero-indexed)
int first = numbers[0];  // 10
numbers[2] = 35;         // Modify third element
```

**Append/Pop or Insertion/Deletion at Tail**

```C
int numbers[10] = {10, 20, 30, 40, 50}; // Larger than needed
int size = 5; // Store current size somewhere else

// Append
numbers[size] = 60;
size++;

// Pop
size--; // Just "forget" that there was an element at the end
```

**Insertion/Deletion in Middle**

```c
// Assuming array is big enough
void insert(size_t size, int array[], int value, size_t index)
{
	for(int i = size - 1; i > (int)index; i--){
		array[i+1] = array[i];
	}
	array[index] = value;
}

void delete(size_t size, int array[], size_t index)
{
	for(int i = index; i < (int)size - 1; i++){
		array[i] = array[i+1];
	} 
}
```

**Search**

```C
int find(size_t size, int array[], int value)
{
	for (int i = 0; i <  size; i++) {
		if (array[i] == value){
			return i;
		}
	}
	// Not found return indication
	return -1;
}
```

**Copying**

```C
void copy(size_t size, int dest[], int src[])
{
	for (int i = 0; i <  size; i++) {
		dest[i] = src[i];
	}
}
```

Almost all operations on arrays are bounded by the input size of the array linearly, making them the standard to beat for other structures:

Array Operation Time Complexity

| Operation              | Time Complexity |
|------------------------|-----------------|
| Access by index        | O(1)            |
| Append / Pop           | O(1)            |
| Insert / Delete middle | O(n)            |
| Search for value       | O(n)            |
| Copy                   | O(n)            |

### Strings

Strings are an extension of arrays and an example of a **sentinel** data structure. **Sentinel** data structures are a family of data structures that define a **sentinel value** that defines the end of an instance of the structure. For strings in C and generally, that value is the null terminator, `'\0'`.

```c
char str[] = "Hello";
// Actually stored as: {'H', 'e', 'l', 'l', 'o', '\0'}
// str[5] == '\0'

char str2[] = "Hello World!";
// Change the space into a \0 to make it end early
str2[5] = '\0';
printf("%s\n", str2); // Prints "Hello"
// The original memory is still there, just need to push the pointer forward
printf("%s\n", str2 + 6); // Prints "World!"
// str2 is now effectively storing two strings, "Hello" and "World!"
```

The reason this is useful is that if you are storing many strings in memory, each with a different length, you can store many strings in many different places in varying sizes and always know how to stop reading in memory before going out of bounds. This allows for pointers to be passed around as if they are the character arrays themselves without worrying about bleeding over into other memory locations.  

```C
void print_string(char* s)
{
    while(*s != '\0'){
        printf("%c", *s);
        s++;
    }
}

char greeting[] = "Hello";
char name[] = "Alice";

print_string(greeting); // Stops at its own '\0', never touches name
print_string(name);

char names[] = "Johnny\0Joan\0Jenifer\Jamiroquai\0Jim\0";
char* current_name = names;    // Start current name pointing to "John"
char* name_by_index[5];        // Array to store name locations as they are found
	
for(int i = 0; i < 5; i++){
	// Print char from current location until \0
	print_string(current_name);
	// Stores the pointer to all valid names in the bigger string
	// This can be used to now reference name indexes rather than searching
	// for \0
	name_by_index[i] = current_name;
	
	
	// Push forward the pointer until it is at the \0
	
	while (*current_name != '\0')
		current_name++;
	// Push one more to be at first char of next name
	current_name++;
}
// Can now use name_by_index[i] to print names
for(int i = 0; i < 5; i++){
	print_string(name_by_index[i]);
}
```


## Static VS Dynamic Memory

While strings help with some of the problems with arrays by being able to treat them as pointers, the main issue with arrays in C is that they have a set size in memory. For all of the above examples, we had to work within a set bounds.

In a computer, everything must be stored within a set sized contiguous block of memory as the computer does not have infinite memory. Information is stored in these blocks of memory and referenced through their addresses (pointers in C). If all data must be stored ultimately within these blocks, all the active addresses must be kept somewhere so we can reference them and not lose them. We also need to make sure we remove old memory so we do not run out of memory early keeping a bunch of unused data around. As such, operating system memory managers that our programs run on top of try to keep our data controlled as much as they can. C however, gives a lot of freedom with managing your own memory.

The first way that the compiler and OS manage the memory of our programs is by estimating how much our program needs based on the source code. This is why the compiler wants arrays to be a set size and then respected afterwards. By keeping things a known set size it makes the memory footprint of the program easy to predict, track, and clean up. This static memory footprint is the minimum amount of memory your program needs to run and is a count of the number of bytes your variables and arrays take up. This memory is called the stack and represents guaranteed safe memory for the runtime of your program. When we set an array's max size to something large to account for an unknown amount of data, we are reserving memory on the stack that we know will be available for that array. Stack memory is also fast to access since its location and element sizes are known, as well as being pre-loaded in fast access memory. The one drawback to the stack is that it is static - it cannot be grown or shrunk during the run of the program.

To account for this, computers allow for new memory locations to be reserved during the runtime of your program in a different place than the stack memory. Such dynamic memory at runtime is known as the heap, and it is controlled in C by functions like `malloc()` and `free()`. The heap is a place that the compiler/OS allows your program to grow into manually without it managing the data. This means that it is manually managed by the programmer and they must properly manage it and clean up afterwards. The added freedom also comes at the cost of speed since the compiler could not account for operations on dynamic memory ahead of time and needs to look up locations at runtime.

```c
// Allocate an array of 10 ints on the heap at runtime
int* numbers = malloc(10 * sizeof(int));

numbers[0] = 42; // Used exactly like a stack array

free(numbers);   // Must be freed manually or memory is leaked
```

If `free()` is not called on heap memory when it is no longer needed, that memory remains reserved for the duration of the program even though nothing is using it. This is called a **memory leak** and is one of the most common bugs in C programs.

**Note**: **Stack overflow**, where a program runs out of stack memory, is possible and most commonly occurs with deep recursion, where a function calls itself many times and each call adds to the stack. More on this when we cover recursion.


## Dynamic Arrays

Static arrays are fast and simple but require knowing the size of your data ahead of time. In practice this is often not possible, you may not know how many elements you need until the program is running. The solution is a **dynamic array**, an array allocated on the heap that can be resized at runtime as needed.

It is similar to creating large-fixed sized arrays and keeping track of the used size, but being able to resize the array as you grow. It begins with allocating an initial block of heap memory, as it is used track the current size and the total capacity separately, and when the array fills up, allocate a larger block, copy the contents over, and free the old one.

```c
typedef struct {
    int* data;       // Pointer to heap-allocated array
    size_t size;     // Number of elements currently stored
    size_t capacity; // Total number of elements that can be stored
} DynamicArray;
```

This is a record wrapping a heap pointer, the first time in this lesson that a data structure is built from both a `struct` and heap memory together.

**Creation:**

```c
DynamicArray create(size_t initial_capacity)
{
    DynamicArray da;
    da.data = malloc(initial_capacity * sizeof(int));
    da.size = 0;
    da.capacity = initial_capacity;
    return da;
}
```

**Append:**

When appending, we first check if there is room. If not, we resize before inserting. The standard strategy is to double the capacity, this keeps the average cost of an append low:

```c
void append(DynamicArray* da, int value)
{
    if(da->size == da->capacity){
        da->capacity *= 2;
        da->data = realloc(da->data, da->capacity * sizeof(int));
    }
    da->data[da->size] = value;
    da->size++;
}
```

`realloc()` is a heap function that attempts to resize an existing allocation. If it can grow the block in place it will, otherwise it allocates a new block, copies the contents, and frees the old one for you.

**Access and Modification:**

```c
int get(DynamicArray* da, size_t index)
{
    return da->data[index];
}

void set(DynamicArray* da, size_t index, int value)
{
    da->data[index] = value;
}
```

These are identical in cost to static array access - still O(1) - because the underlying storage is still a contiguous block.

**Deletion:**

```c
void delete(DynamicArray* da, size_t index)
{
    for(int i = index; i < (int)da->size - 1; i++){
        da->data[i] = da->data[i+1];
    }
    da->size--;
}
```

**Cleanup:**

Since the array lives on the heap, it must be freed when done:

```c
void destroy(DynamicArray* da)
{
    free(da->data);
    da->data = NULL;
    da->size = 0;
    da->capacity = 0;
}
```

Setting `data` to `NULL` after freeing is a defensive habit. Accessing a freed pointer is undefined behavior, but dereferencing `NULL` will crash immediately and visibly rather than silently corrupting memory.

**Complexity:**

|Operation|Time Complexity|
|---|---|
|Access by index|O(1)|
|Append (with room)|O(1)|
|Append (resize needed)|O(n)|
|Append (amortized)|O(1)|
|Insert / Delete middle|O(n)|
|Search for value|O(n)|

The amortized O(1) for append is worth understanding. Resizing is expensive but rare, by doubling capacity each time, the number of resizes grows logarithmically while the number of appends grows linearly. The cost of resizing averaged across all appends works out to a constant. This is why doubling specifically is the standard strategy rather than growing by a fixed amount.

