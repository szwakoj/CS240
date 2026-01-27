# C Review: Text Adventure Game
## Due Date: 2/13/26

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
- You will only need to implement movement and grabbing a single key for the commands
	- I.e. "go North", "go South", "grab key" (when in proper room)
- There will only need to be a minimum of 6 rooms that with a structure that contains:
	- at least one dead-end (you need to go back one in order to find the exit)
	- at least one cycle (you could loop in to the same rooms if you repeat the same commands)
	- a room with a key
	- a room with a locked door that will end the game when unlocked

In order to accomplish this game, we are going to split the work into to main parts:

- Section 1: Setting Up
	- This part will focus on setting up the basic data structures, reading file data, and creating the user interface for a small version of the full game
	- You will start by parsing a room files that I provide to you, creating a struct to store that data, and navigating the basic rooms by implementing the movement command parser
-  Section 2: Expanding the World
	 - With the data structures in place and a small example, you will now expand on the groundwork from the previous part and create your own room descriptions and layout while also adding in the key mechanics
## Section 1: Setting Up (basic_game.c)

Click [here](../homework/HW1_Start.zip) , to download the starting point that I have created for you. It is also on Brightspace, under Content->Homework 1. Unzip it into the place you are completing Homework 1, Section 1. 




  

## Section 2: Expanding the World (text_game.c)

