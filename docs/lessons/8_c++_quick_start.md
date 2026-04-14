# C++ Quick Start

A component of this course is to learn the C++ programming language. C++ is an extension of C that adds new features to make the language feel modern and more powerful. This lesson will focus on the general trends of translating into C++ from C.

In this lesson, we will cover C++'s:
- C++ Generally
- Namespaces
- I/O
- Additional Primitive Types
- Dynamic Memory Functions
- Classes
- The Standard Template Library (STL)

## C++ Program Structure and Compilation

The following is an example of a "Hello World" program in both C and C++ along with their compile command:

C:

```c
// main.c
#include <stdio.h>

int main() 
{
	const char* hello = "Hello World!";
	
	printf("%s \n", hello);
	
	return 0;
}
```

Compiled using:

```bash
gcc main.c -o C_code_hello
```

C++:

```C++
// main.cpp
#include <iostream>
#include <string>

int main() 
{
	std::string hello = "Hello World!";
	
	std::cout << hello << std::endl;
	
	return 0;
}
```

Compiled using:

```bash
g++ main.cpp -o C_code_hello
```

As you can see there are some differences however they are minor. In fact, you can compile the C code using `g++` no problem. The striking similarities are because C++ is a super set of C, meaning that it is C added on to (hence the name being C incremented). 

As you can see, compilation is much the same just switching `gcc` -> `g++` when you run the command in the terminal.

You may also see a lot of `std::`'s around. This is C++'s standard **namespace** being added to standard language features.
## `using` Name Spaces

 A namespace is used to group identifiers of both variables and functions by the way they are used. This allows you to have multiple of the same identifiers for functions or variables in different namespaces, for example:

```C++
// main.cpp
#include <iostream>
#include <string>

namespace SpaceA {
	std::string hello = "Hello World from namespace SpaceA";
}
namespace SpaceB {
	std::string hello = "Hello Planet from namespace SpaceB";
}

int main() 
{

	
	std::cout << SpaceA::hello << std::endl;
	std::cout << SpaceB::hello << std::endl;
	
	return 0;
}
```

This is good for when you make BIG projects and might have multiple `draw()` functions or multiple `height` and  `width` variables. With a namespace you can `screen::draw()` or `sprite::width` instead of needing C's long variable names (`sprite_width` and `window_width`).

The `std` namespace is reserved for C++ Standard Template Library(STL) functions, classes, and variables (more on the STL later). It can be annoying to constantly need to write down `std::` before every standard function (since you end up using them a lot). To make it better, we have the `using` keyword. The `using` keyword is used to make aliases for identifiers so you can change the way you use certain variables or functions names. If we use `using namespace std;` this will automatically add `std::` to the beginning of the identifiers of your program if you don't explicitly put them:

```C++
// main.cpp
#include <iostream>
#include <string>

namespace SpaceA {
	std::string hello = "Hello World from namespace SpaceA";
}

namespace SpaceB {
	std::string hello = "Hello Planet from namespace SpaceB";
}

using namespace std;

int main() 
{
	
	cout << SpaceA::hello << endl;
	cout << SpaceB::hello << endl;
	
	return 0;
}
```

This is fine for simple programs, but you need to be careful "using" `using` it since it makes big changes to how your write code and if you use someone else's library you make mess up their namespaces. To be extra safe while typing less, you can do the following to use only the standard functions you need without `std::` and without overwriting an others you may be using:
```C++
// Instead of using namespace std;
using std::cout;
using std::endl;

// Can now use cout with out std::
```

## Input Output
In the previous examples, you may have noticed that outputing to the screen is MUCH different than what we are used to. Do not worry! It is not that bad, and actually makes things easier.

This sections will use a slightly different piece of code to work on:

```c++
#include <iostream>
#include <string>

int main() 
{
	// Start name off empty
	std::string name = "";
	// Temperature value to tell user later
	int temp = 70;
		
	// Prompt user to enter their name
	std::cout << "Welcome! Please enter your name" << std::endl << ">";
	// Input user's name into name var
	std::cin >> name;
	// or std::getline(std::cin, name);
	
	// Output a formatted string using their name
	std::cout << "Hello there, " << name << "! Thats a nice name!"<< std::endl;
	
	std::cout << "The temperature is currently: " << temp << "F!" << std::endl;
	
	return 0;
}
```

Example use:

```bash
$ g++ hello.cpp -o hello
$ ./hello
Welcome! Please enter your name
>John
Hello there, John! Thats a nice name!
The temperature is currently: 70F!
```

In C, we used `printf()` and format specifiers to output to the screen. This allowed us to give the function a string with special character codes inside to format the data types, like so:

```c
int temp = 70;
const char* name = "John";

printf("Hello %s! The temperature is %d\n", name, temp);
```

`scanf()` worked much the same way:

```C
int temp;

scanf("%d", &temp);
```

C++ on the other hand takes care of the formatting for you. You dictate the order and the rest is handled for you.

`std::cout` refers to **standard output stream** or just standard out, this is the standard place that output information is written to when sending out information. You used `stdout` every time you called `printf()`, it represents the pointer that we write memory to output to the console. In C++ we still need to write data to this location, but by just giving the data to the pointer. When `std::cout<<"my string" << std""endl` is used its as if we are sending the information "my string" to the output directly. The benefit of C++ is that there are NO FORMAT SPECIFIERS for basic I/O. All data is formatted automatically when we `<<` it into `std::cout`.

This is the same for `std::cin` except it is the **standard input stream**. It still does not need formats, it will read data in according to the type of the destination variable.

## Strings

You may also noticed that C++ has its own string type rather than `char` arrays. In C, strings were just arrays of characters with a null terminator at the end, which meant you had to manage their memory, use clunky functions like `strcpy` and `strcmp`, and be careful not to overflow your buffer. C++ gives you `std::string` which handles all of that for you.

```c
// C
char name[50] = "Alice";
char greeting[100];
strcpy(greeting, "Hello, ");
strcat(greeting, name);
printf("%s\n", greeting);
```

```c++
// C++
std::string name = "Alice";
std::string greeting = "Hello, " + name;
std::cout << greeting << std::endl;
```

Much cleaner. Here are the most useful things you can do with a string right out of the box:

```c++
std::string s = "Hello";

s.length();       // how many characters
s[0];             // access individual characters just like an array
s + " World";     // concatenation with +
s == "Hello";     // comparison with ==, no strcmp needed
s.substr(1, 3);   // grab a slice, starting at index 1, length 3 -> "ell"
s.find("ell");    // returns index of substring, or string::npos if not found
```

You can still use C-style `char` arrays in C++ and sometimes you will need to when interfacing with certain libraries. But for anything you write yourself in this course, always use `std::string`.

One thing to watch out for: `std::cin >>` stops reading at whitespace, so if you need to read a full line with spaces in it, use `std::getline()` instead:

```c++
std::string fullName;
std::getline(std::cin, fullName); // reads the whole line including spaces
```

## Additional Types: bool and References

### bool

C didn't have a native boolean type. You typically used `int` and relied on 0 being false and anything else being true, sometimes pulling in `stdbool.h` to get the `true` and `false` keywords. In C++, `bool` is a fully built-in type and needs no include:

```c++
bool found = false;
bool isEven = (x % 2 == 0);

if (found) {
    std::cout << "found it!" << std::endl;
}
```

Simple upgrade, nothing scary.

### References

This one is more important. A reference is an alias for an existing variable. You declare one using `&` after the type:

```c++
int x = 10;
int& ref = x; // ref is now another name for x

ref = 20;
std::cout << x << std::endl; // prints 20, x was changed through ref
```

Where this really matters is function parameters. In C, if you wanted a function to modify a variable you passed a pointer to it:

```c
// C
void increment(int* x) {
    (*x)++;
}

increment(&myVar);
```

In C++ you can use a reference instead and skip the pointer syntax entirely:

```c++
// C++
void increment(int& x) {
    x++;
}

increment(myVar); // no & needed at the call site
```

The end result is the same, `myVar` gets modified. But references are cleaner to read and write, and unlike pointers they cannot be null and cannot be reassigned to refer to something else after they are created. You will see them constantly in C++ code, especially when passing large objects into functions where you want to avoid copying the whole thing.

**Note:** References do not replace pointers entirely. You still need raw pointers for things like building linked lists and trees, which is most of what this course is about. Think of references as a cleaner tool for the cases where pointers were just being used as a workaround for pass-by-value.

## Dynamic Memory: `new` and `delete`

In C you used `malloc()` and `free()` to manage heap memory. C++ replaces these with the `new` and `delete` keywords. They do the same job but are built into the language itself rather than being library functions.

```c
// C
int* p = (int*)malloc(sizeof(int));
*p = 42;
free(p);
```

```c++
// C++
int* p = new int;
*p = 42;
delete p;
```

For arrays it works like this:

```c++
int* arr = new int[10];  // allocate array of 10 ints
arr[0] = 1;
delete[] arr;            // note the [] on delete, this is required for arrays
```

Using `delete` without `[]` on an array is undefined behavior, so do not forget the brackets.

The big practical difference from `malloc` is that `new` automatically calls constructors when you are allocating objects (more on that in the next section), which `malloc` does not. For this course you will be writing things like `new Node` constantly when building linked lists and trees, so this syntax will become second nature fast.

As with C, every `new` must have a matching `delete`. Forgetting to delete is a memory leak and those will absolutely show up if you run a memory checker on your assignments.

## Classes

This is where C++ starts to really separate itself from C. You already know structs. In C, a struct is just a container that holds data together under one name:

```c
// C
struct Node {
    int data;
    struct Node* next;
};
```

In C++, structs can also hold functions. But more importantly, C++ gives you **classes**, which are like structs with two extra superpowers: **access control** and **constructors/destructors**.

### Access Control

Class members are either `public` (anyone can access them) or `private` (only the class itself can access them). This lets you hide the internals of your data structure and only expose what the outside world actually needs to use.

```c++
class Stack {
private:
    int data[100]; // outsiders cannot touch this directly
    int top;

public:
    void push(int val);  // outsiders use these
    int pop();
    bool isEmpty();
};
```

The difference between a `class` and a `struct` in C++ is actually just this: struct members are public by default, class members are private by default. That is the only technical difference. In practice, people use structs for simple data containers (like a linked list node) and classes for anything with real logic and hidden internals.

### Constructors and Destructors

A **constructor** is a special function that runs automatically when you create an object. It has the same name as the class and no return type. You use it to initialize your data:

```c++
class Node {
public:
    int data;
    Node* next;

    Node(int val) {       // constructor
        data = val;
        next = nullptr;   // nullptr is C++'s version of NULL
    }
};
```

Now when you create a node you can do it in one line:

```c++
Node* n = new Node(42); // constructor runs automatically, data = 42, next = nullptr
```

A **destructor** runs automatically when an object is destroyed or deleted. It has the same name as the class with a `~` in front and no parameters. This is where you clean up any heap memory the object owns:

```c++
class LinkedList {
private:
    Node* head;

public:
    LinkedList() {        // constructor
        head = nullptr;
    }

    ~LinkedList() {       // destructor, runs when the list is deleted or goes out of scope
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};
```

Putting it all together, a small but complete example:

```c++
#include <iostream>

class Counter {
private:
    int count;

public:
    Counter() {           // constructor, start at 0
        count = 0;
    }

    void increment() {
        count++;
    }

    int getCount() {
        return count;
    }
};

int main() {
    Counter c;
    c.increment();
    c.increment();
    std::cout << c.getCount() << std::endl; // prints 2
    return 0;
}
```

Note that `c.count` would be a compile error here because `count` is private. The only way to interact with it from outside the class is through `increment()` and `getCount()`. This is exactly the kind of structure you will use to build your own data structures in this course.

## The Standard Template Library (STL)

The STL is a collection of ready-made data structures and algorithms that ship with C++. For this course you will be implementing most of these yourself so you actually understand what is happening under the hood. But once you have built a linked list by hand, it is worth knowing that C++ already has all of these waiting for you:

| Container             | What it is                                                 |
| --------------------- | ---------------------------------------------------------- |
| `std::vector`         | Dynamic array, resizes automatically                       |
| `std::stack`          | Stack with push/pop/top                                    |
| `std::queue`          | Queue with push/pop/front                                  |
| `std::priority_queue` | Heap-based priority queue                                  |
| `std::map`            | Sorted key-value store (Binary Search Tree under the hood) |
| `std::unordered_map`  | Hash map, faster average lookup                            |
| `std::set`            | Sorted collection of unique values                         |

They all live under `std::` and need their corresponding header, for example `#include <vector>` for vector. You will see these come up later in the course once we start talking about what they actually are internally.

---
## Quick Reference: C to C++ Cheat Sheet

| |C|C++|
|---|---|---|
|**Compile**|`gcc main.c -o out`|`g++ main.cpp -o out`|
|**Output**|`printf("val: %d\n", x)`|`std::cout << "val: " << x << std::endl`|
|**Input**|`scanf("%d", &x)`|`std::cin >> x`|
|**Strings**|`char str[50]` + strcpy/strcat|`std::string str` + `+` and `==`|
|**Boolean**|`int` or `stdbool.h`|`bool` built-in|
|**Pass by reference**|`void f(int* x)` + `f(&var)`|`void f(int& x)` + `f(var)`|
|**Heap allocate**|`malloc(sizeof(int))`|`new int`|
|**Heap free**|`free(ptr)`|`delete ptr` / `delete[] ptr`|
|**Null pointer**|`NULL`|`nullptr`|
|**Grouped data**|`struct` (data only)|`struct` or `class` (data + functions + access control)|
|**Auto-init object**|manual init function|constructor|
|**Auto-cleanup object**|manual cleanup function|destructor|
|**Avoid std:: prefix**|N/A|`using namespace std;`|