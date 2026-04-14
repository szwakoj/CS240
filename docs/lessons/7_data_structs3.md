# Data Structures: Linear Structures II 

Continuing after the previous lesson on classifying algorithms into linear and non-linear characteristics, we will cover the main linear structures outside of arrays and the dynamic counterpart. Stacks and queues are special cases of arrays, while linked lists are a different solution to having a dynamically resizable linear collection.

  In this lesson, we will cover:
  
- Stacks and Queues
- Linked Lists
- Doubly Linked Lists

## Stacks and Queues

**Stacks** and **queues** are linear data structures that force where add/remove operations happen in order to give immediate access to data and force certain ordering by the operations. They are similar enough that it makes sense to introduce them together and complementary in their implementation when side by side.

![](../img/stack_queue_light.png#only-light)
![](../img/stack_queue_dark.png#only-dark)
### Stacks

Stacks are special arrays where all append/push and remove/pop operations occur at the end of the array, always adding or removing at the last entered item. Another way to think about it is as **last in first out (LIFO)**, since the last item in a long list of pushes would be the first to be popped. It works like a stack of books where if you want to access the book on the bottom, you must take 
off the top of each book first.

The code implementation boils down to an array that keeps track of the last element that has functions that pop/push for you with that restriction. Here is the C code with the basic operations for a static `int` stack:

**Main Structure**

```C
typedef struct {
	int elements[MAX_STACK];
	int current_node;
} Stack;
```

**Creation**

```c
void stack_init(Stack* s)
{
	s->current_node = -1;
}
```

 **Push**

```c
void stack_push(Stack* s, int element)
{
	if (s->current_node == MAX_STACK - 1){
		printf("Max Stack Reached! Element not added ...\n");
		return;
	}
	s->current_node++;
	s->elements[s->current_node] = element;
}
```

 **Pop**

```c
int stack_pop(Stack* s)
{
	if (s->current_node == -1){
		printf("Nothing to pop!\n");
		return 0;
	}
	
	int value = s->elements[s->current_node];
	
	s->current_node--;
	
	return value;
}
```

**Peek/Top** (just look at top without popping)

```c
int stack_peek(Stack* s)
{
	if (s->current_node == -1){
		printf("Nothing to peek at!\n");
		return 0;
	}
	
	int value = s->elements[s->current_node];
	
	return value;
}
```

**Check If Empty** (without directly accessing stack internals)

```c
bool stack_is_empty(Stack* s)
{
	return (s->current_node == -1);
}
```

Note: This implementation uses a statically sized array, however, if you notice, this is extremely similar to how we implemented the dynamic array, just with less capabilities. With this in mind, you could easily create a dynamic stack.

All operations work in O(1) which makes this nice for when you know you do not need to look up for specific elements or indexes but are using a specialized algorithm for the task at hand.

These are good for when you need reverse ordering or to track a state as you go deeper into a process, times like:

- **Reversing Things**
	- For example, reversing a string. Starting at the beginning of the string, push the elements on a stack until reaching the NULL terminator. Go back to the beginning of the string, pop each element into the new string starting at index 0 until nothing is left in the string. The string will now be reversed.
- **Undo/Redo**
	- In a software, record every action in a stack, when user wants to undo an action, pop the action off the undo stack and push it onto a redo stack. If one wants to redo something, pop the redo stack onto the undo stack. 
- **Function Call Management**
	- When a function is called all local variables' addresses are loaded onto a stack as the function is ran. Afterwards, the stack of pointers is popped off in reverse order and freed from memory without issue. This is especially important in recursive functions that call many copies of itself each with its own scoped of variables that need to be freed in reverse order to ensure nothing breaks.

### Queues

**Queues** act much like their name implies, they are an ordered structure that removes items in the order they were added. This makes the first element the one to be removed every time with additions always occurring at the tail. The best way to think about it is as a line at a fast food place, we think of the person at the front as first (0 index) and they are removed from the line first, with the second person becoming first in their place. This is usually summarized in, **first in first out (FIFO)**. 

In the implementation of queues, it is once again based on arrays, however where one may think that it will require reordering in order to attend to the constantly changing index 0 element. Where you would assume you need constant reordering for each dequeue, we can use a similar trick to the one we used in stacks, just keeping an index on the current node of the stack. Instead of that, we will keep two indexes, a tail and a head, one for the current location to enqueue and one for dequeuing. We additionally make it a **circular buffer** array internally by wrapping indexes around as if the ends of the array are connected. We do this by using modulo to wrap indexes over the max back to the beginning:

```c
tail = (tail + 1) % MAX_QUEUE;
```

This creates a system that looks like this:

![](../img/circular_queue.gif)

**Main Structure**

```c
typedef struct {
	int elements[MAX_QUEUE];
	size_t head; // Current dequeue location
	size_t tail; // Current enqueue location
	size_t size; // To guard against overflowing
} Queue;
```

**Creation**

```c
void queue_init(Queue* q)
{
	q->head = 0;
	q->tail = 0;
	q->size = 0;
}
```

**Enqueue**

```c
void queue_enqueue(Queue* q, int element)
{
	if (q->size == MAX_QUEUE){
		printf("Max Queue Reached! Element not added ...\n");
		return;
	}
	q->elements[q->tail] = element;
	q->tail = (q->tail + 1) % MAX_QUEUE;
	q->size++;
}
```

**Dequeue**

```c
int queue_dequeue(Queue* q)
{
	if (q->size == 0){
		printf("Nothing to dequeue!\n");
		return 0;
	}
	int value = q->elements[q->head];
	q->head = (q->head + 1) % MAX_QUEUE;
	q->size--;
	return value;
}
```

**Peek/Front** (just look at front without dequeuing)

```c
int queue_peek(Queue* q)
{
	if (q->size == 0){
		printf("Nothing to peek at!\n");
		return 0;
	}
	return q->elements[q->head];
}
```

**Check If Empty**

```c
bool queue_is_empty(Queue* q)
{
	return (q->size == 0);
}
```

Note: The `size` field is what lets us distinguish between a full and empty queue, both states would otherwise look identical since `head == tail` in both cases. This is cleaner than the alternative of leaving one slot permanently empty.

Like stacks, all operations run in O(1), making queues efficient for situations where you need strict ordering of processing. These are good for when you need to process things in the order they arrived, times like:

- **Task Scheduling**
    - Operating systems use queues to manage which processes get CPU time, ensuring tasks are handled in the order they are received rather than arbitrarily.
- **Breadth-First Search**
    - When traversing a graph or tree level by level, a queue tracks which nodes to visit next, ensuring you fully explore one level before moving to the next.
- **Buffering**
    - Any time data is produced faster than it can be consumed, like keyboard input, network packets, or print jobs, a queue holds the incoming data in order until it can be processed.

Queues have additional extensions beyond this simple implementation. Some of the well known ones are:

- **Priority Queue**
	- Instead of strict FIFO ordering, each element is given a priority and the highest priority element is always dequeued first regardless of insertion order. Commonly implemented with a heap rather than a plain array.
- **Deque (Double-Ended Queue)** 
	- Allows enqueue and dequeue from both ends, making it a generalization of both stacks and queues at once. Useful when you need flexibility in which end you process from.

Both stacks and queues are fundamental data structures that are used at the core of a lot of software. They are related in operation and implementation with both being essentially arrays, just with specific algorithms for interaction. They both also enforce ordering on the elements queues in order of addition and stacks in reverse order.
## Linked Lists

**Linked lists** are a classic data structure that takes a different approach to dynamic, sequential data structures than we have seen thus far. In its approach, elements are not stored physically next to each other in memory, rather their sequential ordering and method of discovery are store via pointers to the "next" element in the list. Because all connections are via pointer variables and not inherent and assumed physical ordering, there never needs to be a copying operation for recording or resizing the list like arrays. It also means that reordering via swaps, reversing, or sorting all can happen without the elements themselves moving in memory. The only drawback is that vanilla linked lists do not allow getting an element at a certain index's content without traversing the list until it arrives there since the locations of each element are only known by the element before it.

![](../img/linked_list_light.png#only-light)
![](../img/linked_list_dark.png#only-dark)

This implementation of linked lists will use a `char*` to point to a string elsewhere in memory. This will also be a data struct that we separate into two different structs. This will keep organization better and separate functionality when we add additional features on top of the linked list.

**Structures**

```C
//This line is needed in order to use ListNode inside of ListNode
typedef struct ListNode ListNode;
typedef struct ListNode {
	char* content;
	ListNode* next; // Pointer to next node
} ListNode;

typedef struct {
	ListNode* HEAD;
	size_t size;
} LinkedList;
```


**Creation**

We should create two separate creation functions. This time we will make the node creation dynamically allocate a new node instead of allocating it outside of the function and then using an init function.

```C
ListNode* lnode_create(char* content)
{
	ListNode* new_node = malloc(sizeof(ListNode));
	new_node->content = content;
	new_node->next = NULL;
	return new_node;
}

LinkedList* list_create()
{
	LinkedList* new_list = malloc(sizeof(LinkedList));
	new_list->HEAD = NULL;
	new_list->size = 0;
	return new_list;
}
```

**Adding Elements**

```C
// Adding to the begining
void list_prepend(LinkedList* l, char* content)
{
	ListNode* new_node = lnode_create(content);
	new_node->next = l->HEAD;
	l->HEAD = new_node;
	l->size++;
}
// Adding to end
void list_append(LinkedList* l, char* content)
{
	ListNode* cur_node = l->HEAD;
	// If there isnt anything yet, just make a new one
	if (cur_node == NULL) {
		l->HEAD = lnode_create(content);
		l->size++;
		return;
	}
	// Traverse until reaching the tail
	while (cur_node->next != NULL){
		cur_node = cur_node->next;
	}
	// Add node at tail
	cur_node->next = lnode_create(content);
	l->size++;
}
// Adding at specific index
void list_insert(LinkedList* l, char* content, size_t index)
{
	if (index > l->size){
		printf("Error: index %d does not exist in list!\n", index);
		return;
	}
	
	// If they want to insert at the begining just prepend
	if (index == 0) {
		list_prepend(l, content);
		return;
	}
	
	size_t cur_index = 0;
	ListNode* cur_node = l->HEAD;
	
	if (cur_node == NULL) {
		l->HEAD = lnode_create(content);
		l->size++;
		return;
	}
	
	// Traverse until invalid next or reaching the place before the index
	while (cur_node->next != NULL && cur_index < index-1){
		cur_node = cur_node->next;
		cur_index++;
	}
	
	// "Rewire" the pointer connections to insert the node
	ListNode* new_node = lnode_create(content);
	new_node->next = cur_node->next;
	cur_node->next = new_node;
	l->size++;
}
```

**Removing Elements**

```C

void list_pop_front(LinkedList* l)
{
	if (l->size == 0) {
		printf("Error: Cannot pop an empty list!\n");
		return;
	}
	
	// Make the HEAD the next element, effectivly removing it from disovery
	ListNode* cur_node = l->HEAD;
	l->HEAD = cur_node->next;
	free(cur_node);
	l->size--;
}

void list_pop(LinkedList* l)
{
	if (l->size == 0) {
		printf("Error: Cannot pop an empty list!\n");
		return;
	} else if (l->size == 1) {
		list_pop_front(l);
		return;
	}
	
	ListNode* cur_node = l->HEAD;
	size_t cur_index = 0;
	
	while (cur_index < l->size - 1){
		cur_node = cur_node->next;
		cur_index++;
	}
	// Clean up memory and have the last node "forget" that it has a next
	free(cur_node->next);
	cur_node->next = NULL;
	l->size--;
}

void list_remove(LinkedList* l, size_t index)
{
	if (l->size == 0) {
		printf("Error: Cannot remove on an empty list!\n");
		return;
	}
	
	if (index >= l->size){
		printf("Error: index %d does not exist in list!\n", index);
		return;
	}
	
	// Pop if it is the front or back
	if (index == 0) {
		list_pop_front(l);
		return;
	} else if (index == l->size-1) {
		list_pop(l);
		return;
	}
	
	ListNode* cur_node = l->HEAD;
	size_t cur_index = 0;
	
	while (cur_node->next != NULL && cur_index < index-1){
		cur_node = cur_node->next;
		cur_index++;
	}
	
	ListNode* remove_node = cur_node->next;
	cur_node->next = remove_node->next;
	free(remove_node);
	l->size--;
}
```

**Element Access**

All access in the list is done by searching including accessing by index, so searching for indexes is a lot like searching for content. 

```C
char* list_get_by_index(LinkedList* l, size_t index)
{
	if (index >= l->size) {
		printf("Error: index %d does not exist in list!\n", index);
		return NULL;
	}
	
	if (index == 0) {
		return l->HEAD->content;
	}
	
	ListNode* cur_node = l->HEAD;
	size_t cur_index = 0;
	
	while (cur_node->next != NULL && cur_index < index){
		cur_node = cur_node->next;
		cur_index++;
	}
	
	return cur_node->content;
}

int list_get_by_value(LinkedList* l, char* value)
{
	if (l->size == 0) {
		printf("Error: Cannot search an empty list!\n");
		return -1;
	}
	
	ListNode* cur_node = l->HEAD;
	size_t cur_index = 0;
	
	while (cur_node != NULL && cur_index < l->size){
		// Match found
		if (!strcmp(cur_node->content, value)){
			return cur_index;
		}
		cur_node = cur_node->next;
		cur_index++;
	}
	
	return -1;
}
```

### Complexity and Summary

Linked lists trade the random access speed of arrays for flexibility in structural manipulation. Here is how the core operations break down:

|Operation|Time Complexity|Notes|
|---|---|---|
|Prepend|O(1)|HEAD pointer update only|
|Append|O(n)|Must traverse to the tail|
|Insert at index|O(n)|Traverse to index - 1|
|Remove front|O(1)|HEAD pointer update only|
|Remove back / at index|O(n)|Must traverse to find the node|
|Access by index|O(n)|No random access; must walk the list|
|Search by value|O(n)|Linear scan|

The O(1) prepend and front removal are the standout advantages. If your use case involves frequent additions and removals at the head, such as implementing a stack or a history buffer, a linked list is a natural fit and avoids the shifting cost you would pay with a plain array.

Where linked lists fall short is random access. Unlike arrays, there is no way to jump to index `i` directly; you must walk from HEAD every time, which is why search and index-based operations are all O(n). There is also a memory overhead cost since every node carries an extra pointer alongside its data.

Linked lists are well suited for:

- **Implementing stacks and queues**: prepend and pop-front are both O(1), making them efficient backing structures without a fixed size limit.
- **Maintaining an ordered collection with frequent insertions/deletions**: once you have a pointer to the right node, inserting or removing is just a pointer rewire with no shifting involved.
- **Building more complex structures**: linked lists are the foundation of adjacency lists in graphs, hash table chaining, and LRU caches.

---

## Doubly Linked Lists

A **doubly linked list** extends the singly linked list by giving each node a second pointer, `prev`, pointing back to the node before it, in addition to the existing `next` pointer. The list itself also typically holds a `TAIL` pointer alongside `HEAD`.

```c
typedef struct DListNode DListNode;
typedef struct DListNode {
    char* content;
    DListNode* next;
    DListNode* prev; // Points to the preceding node
} DListNode;

typedef struct {
    DListNode* HEAD;
    DListNode* TAIL;
    size_t size;
} DoublyLinkedList;
```

The structural difference is small, but it unlocks meaningful capability improvements:

- **Backward traversal**: you can walk the list in either direction, which makes operations like reverse iteration or finding a node from the tail straightforward.
- **O(1) append and tail removal**:  with a `TAIL` pointer and a `prev` link, you no longer need to traverse the entire list to reach the end. Appending and removing the last node both become constant time operations.
- **Easier node removal given a pointer**: in a singly linked list, removing a node requires a reference to the _previous_ node so you can rewire its `next`. With `prev` built in, any node can remove itself with no traversal needed.

The tradeoff is that every insertion and removal now needs to maintain _two_ pointers instead of one. The logic is the same as in a singly linked list, you are just doing the rewiring twice, for both `next` and `prev`, but it is easy to miss one side and corrupt the list. The memory cost per node also increases by one pointer.

Here is a comparison of the two structures at a glance:

|                      | Singly Linked List  | Doubly Linked List      |
| -------------------- | ------------------- | ----------------------- |
| Node pointers        | `next` only         | `next` and `prev`       |
| Append               | O(n)                | O(1) with TAIL pointer  |
| Remove tail          | O(n)                | O(1) with TAIL pointer  |
| Remove given pointer | O(n)  need previous | O(1) `prev` is built in |
| Traversal directions | Forward only        | Forward and backward    |
| Memory per node      | 1 extra pointer     | 2 extra pointers        |

Doubly linked lists are the structure behind browser history (back and forward), the undo/redo system in most editors, and the standard library's `std::list` in C++. Any time you need O(1) operations at _both_ ends of a list, or need to traverse in both directions, a doubly linked list is the right tool.

---

## Summary

Stacks, queues, and linked lists are three foundational linear structures, each with a distinct contract for how you interact with it:

- A **stack** enforces LIFO ordering. You can only touch the top, which makes it ideal for tracking state in reverse, ie function calls, undo history, expression parsing.
- A **queue** enforces FIFO ordering. Items are processed in the order they arrive, making it the right structure for scheduling, buffering, and level-order traversal.
- A **linked list** gives up random access in exchange for O(1) structural manipulation at the head and flexible resizing without any copying. A doubly linked list extends this to O(1) operations at both ends and adds the ability to traverse backward.

Arrays remain the better choice when random access, cache locality, or a simple indexed structure is what you need. These three structures are best understood not as replacements for arrays, but as tools for situations where the ordering of operations or the pattern of insertions and deletions is the dominant concern.