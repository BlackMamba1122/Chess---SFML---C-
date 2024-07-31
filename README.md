# Chess Game

## Overview
This is a classic Chess game developed in C++ using the **Simple and Fast Multimedia Library (SFML)**. It allows two players to play a standard game of chess on the same computer. The game features a simple and intuitive graphical user interface, making it easy to play and enjoy the game.

## Looks

### Menu
<img src="https://github.com/user-attachments/assets/7642b34d-19ad-4f6a-a743-f5baa96b6c3e" alt="Menu" width="700"/>

### Startup
<img src="https://github.com/user-attachments/assets/da184499-d401-4a66-911f-f11eaabcf279" alt="Startup" width="700"/>

### Highlight Moves
<img src="https://github.com/user-attachments/assets/e53824c1-4821-4b08-bfce-0ed884a5190b" alt="Highlight Moves" width="700"/>

### Check
<img src="https://github.com/user-attachments/assets/ce8349ea-f2bb-4a1f-a7b7-e6a19123dfa7" alt="Check" width="700"/>

### CheckMate
<img src="https://github.com/user-attachments/assets/7859137c-dde5-472c-af28-696decca7bf2" alt="CheckMate" width="700"/>

## Features
- **Graphical User Interface (GUI)**: The game board and pieces are rendered using SFML, providing a clear and visually appealing interface.
- **Two-Player Mode**: Play against a friend in a local two-player mode.
- **Standard Chess Rules**: The game adheres to the standard rules of chess, including piece movements, check, checkmate, and stalemate.
- **Undo Move**: Players can undo their last move.
- **Move Validation**: Invalid moves are not allowed, ensuring that players adhere to the rules of chess.

## Getting Started

### Prerequisites
To run the game, you'll need:
- C++ Compiler (e.g., GCC, Clang, MSVC)
- SFML library installed on your system

### How to Play

- **Start the Game**: After launching the executable, the chessboard will appear with all the pieces in their starting positions.
  
- **Move Pieces**: 
  - **Select a Piece**: Click on the piece you want to move.
  - **Move the Piece**: After selecting the piece, click on the destination square to move it. The game will automatically highlight valid moves for the selected piece. If you click on an invalid square, the piece will not move.

- **Undo Move**: If you make a mistake or want to take back your last move, press the "Undo" button (if implemented). This will revert the last move made.

- **Check and Checkmate**: The game will notify you if you are in check. The game ends when one player’s king is in checkmate, meaning it cannot make any legal moves to escape the check.

- **Restarting the Game**: To restart the game, simply close and reopen the application.

- **Exiting the Game**: You can exit the game by closing the window using the window's close button or pressing Esc (if implemented).
