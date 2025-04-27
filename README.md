
---

# Slime Staffs BrainFuck Compiler

A simple and fast **Brainfuck compiler** — with custom extensions for integer support, a stack, and more control over the execution!

---

## Original Brainfuck Commands

| Command | Description |
|:--------|:------------|
| `+` | Increment the current cell by 1 |
| `-` | Decrement the current cell by 1 |
| `[` | Start a loop if the current cell is greater than 0 |
| `]` | End a loop if the current cell is less than 0 |
| `.` | Output the current cell's value as ASCII |
| `,` | Input a character (ASCII) into the current cell |

---

## Custom Commands

| Command | Description |
|:--------|:------------|
| `:` | Output the current cell's value as an **integer** |
| `;` | Input an **integer** into the current cell |
| `#` | Push the current cell's value onto the **stack** |
| `$` | Pop a value from the **stack** into the current cell |
| `/` | Move the **stack pointer** one position to the right |
| `\` | Move the **stack pointer** one position to the left |

---

##  Compiler Options

- `--step` — **Step-by-step execution** instead of compiling instantly.

When using `--step`, you can type:

| Command | Description |
|:--------|:------------|
| `x` | Execute the rest of the program instantly |
| `q` | Quit the program |

---

## Coming Soon

- `--edit` mode: After compiling, you'll be able to **edit the compiled output** before executing it!

---

## Project Status

Core features implemented  
New features under development  

---

> *Built for fun, learning, and experiments!*

---
