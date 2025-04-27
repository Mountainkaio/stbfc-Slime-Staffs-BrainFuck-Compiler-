A simple BrainFuck compiler, with some custom things added.

BrainFuck original:

\+ - adds 1 to the current cell;

\- - subtracts 1 from the current cell;

[ - starts a loop if the current cell is greater than 0;

] - stops the loop if the current cell is lesser than 0;

. - prints the current cells value as ASCII;

, - takes user input as ASCII.

Original:

: - prints the current cells value as an integer;

; - takes user input as an integer;

\# - adds the current cells value to the stack pointer position; 

$ - replaces the current cells value with the current value of the stack pointer;

/ - moves the stack pointer to the right;

\ - moves the stack pointer to the left.

Addicional commands:

--step - shows the compilers current step, instead of compiling instantly.

--step commands:

x - executes the rest of the code instantly;

q - ends the program.

And that's it for now! I'm currently working in a '--edit' mode, where you can edit the result after compiling!
