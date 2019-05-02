# C++ PONG
## Intro
This is a test of the viability of running a "game" with only C++, no GUI, and only 4 libraries (iostream, conio.h, windows.h, and time.h). Right now, I have copied over the program from a YouTube series (below) and will be trying to optimize it so that the screen doesn't update every single time an action occurs.

## Preliminary Findings
This project was straight-forward and logically sound, however, the root of the problem was not in the code... It was in the premise. Updating the entire canvas everytime the ball moved created a glitchy effect making the game hard to play. Another shortfall of this program is that the inputs from the keyboard do not update if you hold down a key (basically input lag), which is annoying IMO.

## Plan for Changes
To begin, I'm going to draw the borders once, then only update the interior of the game when the ball moves. This will fix some of the glitchiest parts of the canvas. Also, I will probably remap the keyboard controls to the up/down arrow keys and keep 'w' and 's' as they are. As for the lagfrom the keys, I'll need to do further research into how to make a smooth scrolling effect up and down on the screen.

## Sources (No Code from this is mine, yet..)
1) [C++ Tutorial 21 - Simple Pong Game (Part 1)](https://www.youtube.com/watch?v=y8QL62SDlcQ)
2) [C++ Tutorial 21 - Simple Pong Game (Part 2)](https://www.youtube.com/watch?v=soqGGnxK92c)
3) [C++ Tutorial 21 - Simple Pong Game (Part 3)](https://www.youtube.com/watch?v=Z6hUxXCzKYE)
