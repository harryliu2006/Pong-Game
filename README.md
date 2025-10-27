# Lab 2: Pong Game

## Overview
Implements a terminal-based Pong game in C++ using object-oriented programming principles. The player controls a vertical paddle to deflect moving balls. Each successful hit increases the score, and missing a ball ends the game. Difficulty increases as the paddle shrinks and additional balls are introduced.

## Object-Oriented Structure

### Player Class
Represents the paddle controlled by the player.  
- Stores position (`x`, `y`) and dimensions (`width`, `height`).  
- Responds to keyboard input:
  - `'A'` → move up  
  - `'B'` → move down  
- The paddle height decreases by one unit every two hits (minimum height = 3).  
- Movement is constrained to the visible screen boundaries.  
- Drawn using the `addPixel()` function from the `Screen` class.

### Ball Class
Represents each moving ball in the game.  
- Tracks position, velocity, and ID.  
- Updates position each time step, applying gravity to the vertical velocity.  
- Bounces off walls and the player paddle.  
- Each paddle collision increases the score.  
- Rendered using `addPixel()` from the `Screen` class.

### Screen and IO Classes (Provided)
The files `Screen.cpp`, `Screen.h`, `io.cpp`, and `io.h` were provided by the course instructor.  
They handle all rendering and input/output functions for the terminal display.  
No modifications were made to these files.

## Game Loop (main.cpp)
The main function controls the game logic and flow:  
- Initializes the player, ball(s), and screen.  
- Reads user input via `get_input()`.  
- Updates paddle and ball positions each frame.  
- Checks for collisions and updates the score.  
- Shrinks the paddle and adds new balls as the score increases.  
- Renders each frame on the terminal.  
- Ends when the player quits or misses a ball.

## Game Rules
| Event | Effect |
|--------|---------|
| Every 2 hits | Paddle height decreases by 1 (minimum 3) |
| Every 5 hits | Adds one new ball (maximum 5) |
| Ball missed | Game over |
| Player presses `q` | Quit game |

## Controls
| Key | Action |
|------|---------|
| A | Move paddle up |
| B | Move paddle down |
| q | Quit game |
