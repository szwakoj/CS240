# C Review: Text Adventure Game
## Due Date: 2/20/26

## Description:
In this homework, you will construct a text adventure game in the style of classics like [Zork](https://en.wikipedia.org/wiki/Zork), [The Hobbit](https://en.wikipedia.org/wiki/The_Hobbit_(1982_video_game)), and [The Hitchhiker's Guide to the Galaxy](https://en.wikipedia.org/wiki/The_Hitchhiker%27s_Guide_to_the_Galaxy_(video_game)) but simplified to a manageable scope. You are to create a text adventure in the command-line using the C programming language and rooms that I provide in the form of text files. You will be implementing the data structures and algorithms to facilitate the gameplay and read in arbitrary room files.

If you are unfamiliar to the idea of a text-based adventure game, here are some defining features:

- A terminal interface for the user to enter action commands from a narrow subset
	- Commands like "look", "go {north|east|south|west}", and "grab {item}" are classic examples
- Text that prompts the user as to where they are in the game world
	- "You awake in your bed room in the South side of the room. To the North is the door to the rest of your house. To the West, your window. To the East, is your desk with something shiny on it"
- A method of keeping track of player actions
	- Usually an inventory of items that puzzles require for solving
- If you want a better idea, click [this link](https://www.web-adventures.org/cgi-bin/webfrotz?s=ZorkDungeon), to go to a web-based version of ZORK. Play for a little while to get the gist and experience video game history 

To make sure the scope doesn't go too wild for a first assignment the following restrictions and changes will be made to the program you produce **by the end** of the assignment:

- I will provide template rooms that you will fill in
- You will read in data into a Room data structure
- You will only need to implement movement and looking for the commands 
	- I.e. "go North", "go South" "look"
- After that you make it your own and add at least 2 more rooms

In order to accomplish this game, we are going to split the work into to main parts:

- Section 1: Setting Up
	- This part will focus on setting up the basic data structures, reading file data, and creating the user interface for a small version of the full game
	- You will start by parsing a room files that I provide to you, creating a struct to store that data, and navigating the basic rooms by implementing the movement command parser
- Section 2: Customize and reflect
	- Customize the existing rooms and add at least 2 more rooms
	- Answer some reflection questions
## Section 1: Setting Up (basic_game.c)

Click [here](../homework/HW1_Start.zip) , to download the starting point that I have created for you. It is also on Brightspace, under Content->Homework 1. Unzip it into the place you are completing Homework 1, Section 1. 

### Overview
In this section, you will build the foundation for your text adventure game. You'll work with the provided starter code that reads room information from files and displays it. Your job is to:

1. Define a Room struct to store room data
2. Build an array of rooms from the file data
3. Parse connections between rooms
4. Implement a game loop with basic movement commands

The starter code provides the following files:

- **`rooms.txt`**: Contains the number of rooms and a list of filenames for individual room files
- **`connections.txt`**: Contains information about which rooms connect to each other and in which direction
- **Individual room files** (e.g., `0_enter.txt`, `1_middle.txt`): Each contains a room name and description

Currently the starting code is showing how to read in the file data, your job is to store it in a data structure and make algorithms on top of it.
### Task 1: Define the Room Struct (10 points)

Create a `Room` struct that can store all necessary information about a room:

- Room name (string)
- Room description (string)
- Connections to other rooms in four directions: North, South, East, West
    - Hint: Use integers to store the room indices, with -1 indicating no connection in that direction
- A flag indicating if it is the exit, if you reach this room the games over
- Optional: A flag indicating if this room contains a key (for Section 2)
- Optional: A flag indicating if this room has a locked door (for Section 2)
### Task 2: Load Rooms into Memory (20 points)

Modify the provided code to:

1. Allocate an array of `Room` structs based on `num_rooms`
2. For each room file, read the name and description and store them in the corresponding struct
3. Initialize all direction connections to -1 (no connection)

**Hints**:

- You'll need to use `malloc()` to allocate the array
- Use `strcpy()` to copy strings into your struct fields
- Don't forget to allocate space for the strings inside each struct
### Task 3: Parse Room Connections (20 points)

Write code to read `connections.txt` and populate the connection information in your room array. The format of `connections.txt` is:

**First line**: Number of connections

**Subsequent lines**:

```
<room_index> <direction1> <direction2> <connected_room_index>
```

Where:

- `room_index` is the index of the room in your array (the "from" room)
- `direction1` is the direction FROM room_index (one of: `N`, `S`, `E`, `W`)
- `direction2` is the opposite direction FROM connected_room_index back to room_index
- `connected_room_index` is the index of the room it connects to (the "to" room)

**Example `connections.txt`:**

```
2
0 W E 1
1 N S 2
```
![Image showing the above geographically](../img/hw1.png)
This means:

- **Line 1**: There are 2 connections total
- **Line 2**: Room 0 connects **West** to room 1, and room 1 connects **East** back to room 0
- **Line 3**: Room 1 connects **North** to room 2, and room 2 connects **South** back to room 1

**Important Notes:**

- Each connection is bidirectional and defined on a single line
- The first direction is from the perspective of the first room
- The second direction is from the perspective of the second room
- You need to update BOTH rooms' connection arrays when parsing each line

**Example parsing logic:**

```c
void load_connections(Room* rooms, const char* filename) {
    FILE* conn_file = fopen(filename, "r");
    
    int num_connections;
    fscanf(conn_file, "%d", &num_connections);
    
    for(int i = 0; i < num_connections; i++) {
        int room1, room2;
        char dir1, dir2;
        
        fscanf(conn_file, "%d %c %c %d", &room1, &dir1, &dir2, &room2);
        
        // Set connection from room1 in direction dir1 to room2
        // Set connection from room2 in direction dir2 to room1
        // You'll need to convert 'N', 'S', 'E', 'W' to array indices
    }
    
    fclose(conn_file);
}
```


### Task 4: Implement Game Loop with Movement (30 points)

Create a game loop that:

1. Keeps track of the current room (start at room 0)
2. Displays the current room name and description
3. Shows available exits (which directions have connections)
4. Prompts the user for a command
5. Parses the command:
    - `look` - redisplays current room information
    - `go <direction>` - moves to the connected room in that direction (north/south/east/west)
    - `quit` - exits the game
    - Optional: Zork had a `hello` command that would spur a random greeting when called
6. Handles invalid commands gracefully with error messages

**Hints:**

- After everything is loaded, a loop needs to be entered that constantly will be asking for input and executing it, checking to see if quit or if the final room has been entered
- Use strcmp() to compare user strings to commands
		- Unfortunately, you cannot find a meaningful way out of an if-else for each statement (ie we cannot use `switch`)
### Task 5: Memory Management (10 points)

Ensure proper memory management (clean up after yourself):

- Free all dynamically allocated memory before the program exits
- Free memory for strings within each room struct
- Free the room array itself
### Section 1 Grading Rubric

- Task 1: Room struct definition (10 points)
- Task 2: Loading rooms from files (20 points)
- Task 3: Parsing connections (20 points)
- Task 4: Game loop and movement (30 points)
- Task 5: Memory management (10 points)
- Code style and comments (10 points)
- **Total: 100 points**

## Section 2: Customize and Reflect

### Overview

Now that you have a working game with the provided rooms, you'll make it your own by customizing the existing rooms and adding at least 2 new rooms of your own design. You'll also reflect on your experience working in C.

### Task 1: Customize Existing Rooms (20 points)

Modify the room description files I provided to create your own narrative:

- Change room names to fit your theme
- Rewrite room descriptions with your own creative text
- Change connections as you like

**Examples of themes:**

- SUNY Poly Campus Areas
- NYS Road Trip with Cities
- Classic Fantasy Adventure
- Cyberpunk


### Task 2: Add At Least 2 New Rooms (30 points)

Expand your game world by:

1. Creating at least 2 new room text files following the same format
2. Updating `rooms.txt` to include your new room files
3. Updating `connections.txt` to connect your new rooms to the existing world
4. Ensuring at least one new room is the exit room

**Requirements:**

- New rooms must be reachable from the starting room
- At least one room should be a dead-end (requires backtracking)
- The exit room should be one of your new rooms

**Deliverable**:

- New room text files
- Updated `rooms.txt` and `connections.txt`
- Your game should now have at least 5 total rooms

### Task 3: Test Your Game (10 points)

Play through your game multiple times to ensure:

- All rooms are reachable
- All connections work bidirectionally
- The exit room properly ends the game

**Deliverable**: A walkthrough text file (`walkthrough.txt`) showing the exact commands to reach the exit from the start.

Example:

```
go north
go east
look
go south
go west
```

### Task 4: Reflection Questions (30 points)

Answer the following questions in a file called `reflection.txt`. Each answer should be 2-4 sentences.

1. **Strings and Arrays Handling**: What challenges did you face working with C strings (char arrays)? What did C strings allow for that other array types didn't?

2. **Graph Data Structure**: The entire game that has been made resembles a graph. This is a very important data structure that we will revisit once again. What are the benefits of a graph data structure? What other situations do graphs lend well to?

3. **Rooms vs Nodes**: We have restricted ourselves with the Room data structure. Normal graphs usually can have any number of connections to individual nodes. How did we limit our game? How could we expand it by redesigning the data structure?

4. **Drawing**: With the fact that you have a graph in this game, draw the map of your game and include it in the submission. Save as `graph.png` or other valid file type.


### Task 5: Code Quality (10 points)

Ensure your final submission has:

- Consistent indentation and formatting
- Meaningful variable and function names
- Comments explaining complex logic

### Section 2 Grading Rubric

- Task 1: Customize existing rooms (20 points)
- Task 2: Add new rooms (30 points)
- Task 3: Walkthrough (10 points)
- Task 4: Reflection questions (30 points)
- Task 5: Code quality (10 points)
- Total: 100 points


## Submission Guidelines

### What to Submit

Create a ZIP file named `CS240-HW1-LastName.zip` containing:

#### Section 1 (in folder named `section1/`):

- `basic_game.c` - Your completed source code
- `room_files` - directory containing the following
	- All room files used
	- `rooms.txt` and `connections.txt`

#### Section 2 (in folder named `section2/`):

- `custom_game.c` - Your completed source code
- `room_files` - directory containing the following
	- All room files used in your customized version
	- `rooms.txt` and `connections.txt`
- `reflection.txt` - reflection question answers
- `graph.png` - Your graph drawing