# Chess Game

## Overview
This is a classic Chess game developed in C++ using the **Simple and Fast Multimedia Library (SFML)**. It allows two players to play a standard game of chess on the same computer. The game features a simple and intuitive graphical user interface, making it easy to play and enjoy the game.

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

- **Exiting the Game**: You can exit the game by closing the window using the window's close button or pressing `Esc` (if implemented).
