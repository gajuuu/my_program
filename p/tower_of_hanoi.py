"""
This program is a puzzle game called "Tower of Hanoi".
Blocks can only be stacked so that the larger ones are on the bottom.
The game is cleared when all the blocks can be moved to the rightmost space,
and a message is displayed.
However, if the game cannot be cleared within 15 moves,
the player loses the game and a specific message is displayed.
If the player manages to move all the blocks in the least possible moves,
a special message will be displayed.
"""
from tkinter import *


class HanoiTowerGame:
    def __init__(self, master):
        self.master = master
        self.master.title("Hanoi Tower Game")

        # Create a canvas for drawing the towers and blocks
        self.canvas = Canvas(self.master, width=400, height=300, bg='white')
        self.canvas.pack()

        # Initialize the towers with blocks
        self.tower1 = [3, 2, 1]
        self.tower2 = []
        self.tower3 = []
        self.towers = [self.tower1, self.tower2, self.tower3]
        self.moves_counter = 0
        self.draw_towers()

        # Initialize variables for handling block selection
        self.selected_block = None
        self.selected_tower = None

        self.reset_button = Button(self.master, text="Reset",
                                   command=self.reset_game)
        self.reset_button.pack()

        # Bind the left mouse button click to the on_click method
        self.canvas.bind("<Button-1>", self.on_click)

    # Draw towers and blocks on the canvas
    def draw_towers(self):
        self.canvas.delete("all")
        for i, tower in enumerate(self.towers):
            x = 200 + (i - 1) * 130
            y = 250

            # Draw tower base
            self.canvas.create_rectangle(x - 50, y - 100, x + 50, y,
                                         outline='black', width=2)

            # Draw blocks on the towers
            for j, block in enumerate(tower):
                width = 30 + block * 20
                height = 20
                self.canvas.create_rectangle(x - width / 2,
                                             y - height * (j + 1),
                                             x + width / 2, y - height * j,
                                             fill='blue')
        # Display the moves counter
        self.canvas.create_text(200, 50,
                                text=f"Moves: {self.moves_counter}",
                                font=("Arial", 12))

    # Handle mouse click event
    def on_click(self, event):
        x, y = event.x, event.y

        for i, tower in enumerate(self.towers):
            x_tower = 200 + (i - 1) * 130
            y_tower = 250

            # Checks if the mouse click coordinates (x, y) fall within
            # the boundaries of the current tower.
            if x_tower - 50 <= x <= x_tower + 50 \
                    and y_tower - 100 <= y <= y_tower:
                if self.selected_block is None:
                    self.select_block(i)
                else:
                    self.move_block(i)

        # Update the visual representation of the towers on the canvas
        self.draw_towers()

        # Check for game over conditions
        if self.moves_counter > 15:
            self.show_message("Moves too many! You lose!", color="red")
            self.canvas.unbind("<Button-1>")

        elif len(self.tower3) == 3:
            if self.moves_counter == 7:
                self.show_message("You won in the shortest number of moves!",
                                  color="green")
                self.canvas.unbind("<Button-1>")

            else:
                self.show_message("Congratulations! You won!", color="blue")
                self.canvas.unbind("<Button-1>")

    # Select a block from the clicked tower
    def select_block(self, tower):
        if self.towers[tower]:
            self.selected_tower = tower
            self.selected_block = self.towers[tower].pop()

    # Move the selected block to the clicked tower
    def move_block(self, tower):
        if not self.towers[tower] or self.towers[tower][-1] \
                > self.selected_block:
            self.towers[tower].append(self.selected_block)
            self.selected_block = None
            self.selected_tower = None
            self.moves_counter += 1

    # Display a message on the canvas
    def show_message(self, message, color):
        x = 200
        y = 100
        self.canvas.create_text(x, y, text=message,
                                font=("Arial", 16), fill=color)

    # Reset the game to its initial state
    def reset_game(self):
        self.tower1 = [3, 2, 1]
        self.tower2 = []
        self.tower3 = []
        self.towers = [self.tower1, self.tower2, self.tower3]
        self.moves_counter = 0
        self.draw_towers()
        self.canvas.bind("<Button-1>", self.on_click)


def main():
    # Create the main window and start the game
    root = Tk()
    gamegui = HanoiTowerGame(root)
    
    # Continue to run the game until the user closes the main window.
    root.mainloop()


if __name__ == "__main__":
    main()

