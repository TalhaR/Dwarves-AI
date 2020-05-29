# Dwarves-AI
Console-based game where dwarves gather resources.

Utilizes a BFS pathfinding algorithm to find the closest resources to gather.

![Dwarves-AI](dwarves.gif)

# Requirements
- *Unix-based terminal
  - On Windows, I recommend using WSL to install Ubuntu.
- "ncurses" Library
  - On Linux, run "sudo apt-get libncurses5-dev" in terminal.
  - On MacOS, run "brew install ncurses" in terminal.

# Instructions
1. Clone or download the repository .
2. Launch your preferred unix terminal and locate the directory. Resize window dimensions to ~80x40.
3. Run "make" to compile program.
4. Execute command "./dwarves" to run with 1 dwarf.
    * Optional: Execute "./dwarves b" to run with several dwarves.

# Controls
- While the game is running you can perform a few actions:
  - Press 'Q' to Quit.
  - Press 'P' to Pause.
  - Press 'F' to Fast-forward.