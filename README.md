# Connect Four
---
### Introduction

Edinburgh Napier University Algorithms and Data Structures [SET08122] coursework assignment. Objective of this coursework was to demonstrate my understanding of both theory and practise of the module. My specific task was to implement a simple, command-line only (no GUI or graphics) version of the “Connect Four” game using the C programming language.

---

### To run
* cl coursework.c func.c
* coursework
---

### Functionality

* Displaying the game board
* Placing and removing (one or multiple times) tokens
* When making a undo it can be removed
* Replay of games (depending on the gamemode)
* Gamemodes:
  * Normal Connect Four
  * Competitive Connect Four (undo not allowed)
  * Vs Bot (Easy and Hard difficulty) (undo not supported)
  * Pop Out (undo and replays are NOT supported)
  * Pop 10
  * 5-in-a-Row (undo and replays are NOT supported)
* Various methods (diagonal, horizontal, vertical checking and so on...)
* Wrong input checking
* Algorithms and Data Structures mainly used:
  * Stacks
  * Arrays
  * 2D Arrays
  
---

### Future Improvements

Possible future improvements could include:

* Adding functionality for various board sizes
* Adding undo and redo functionality where not supported
* Adding replay saving functionality where not supported
* Adding "Power Up" gamemode
* Making "Vs Bot" gamemode harder and better

---

More information can be seen in the report.
