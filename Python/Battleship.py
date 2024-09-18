"""
This program creates a so-called battleship game.
The player gives coordinates, and the program marks
the coordinates with a specific symbols.
The symbols depend on the results if the shot hit ships or not.
The ship sinks if it hits all the coordinates it has,
and the game ends if all the ships are sunk.
"""

BOARD_SIZE = 10
REFERENCE = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']


class Ship:

    def __init__(self, ship_type, size, coordinates):
        self.__type = ship_type
        self.__size = size
        self.__coordinates = coordinates
        self.__hits = 0

    def get_ship_type(self):
        """
        Gets the name of ship type
        :return: str, the ship type
        """
        return self.__type

    def get_ship_size(self):
        """
        Gets the ship size
        :return: int, the ship size
        """
        return self.__size

    def get_ship_coordinates(self):
        """
        Gets the coordinates of the ship place
        :return: list<str>, all the coordinates belonging to the ship
        """
        return self.__coordinates

    def add_hit_counts(self):
        """
        Add one to the number of hits that the ship received
        """
        self.__hits = self.__hits + 1

    def get_hit_counts(self):
        """
        Gets the number of hits that the ship received
        :return: int, the current hit counts
        """
        return self.__hits

    def is_hit(self, coordinate):
        """
        Checks if the shot hit the ship or not
        :param coordinate: str, the shot coordinate
        :return: bool, true if the coordinate belongs to ship's place,
        """
        return coordinate in self.__coordinates

    def is_sunk(self, hits):
        """
        Checks if the ship got sunk or not
        :param hits: int, the number of hits that the ship received
        :return: bool, true if the ship got sunk
        """
        return hits == self.__size


def validate_coordinate(coord):
    """
    Checks if the coordinate is valid
    :param coord: str, the target coordinate
    :return: bool, true if the coordinate is valid
    """
    try:
        if len(coord) == 2 \
                and 'A' <= coord[0].upper() <= 'J' \
                and 0 <= int(coord[1]) <= 9:
            return True
        else:
            return False
    except ValueError:
        return False


def read_file(filename):
    """
    Reads the file of the given file name.
    :param filename: str, the name of given file
    :return: list<Ship> | None, the list of ships
    """
    all_coordinates = []
    ship_list = []

    try:
        file = open(filename, mode='r')
        for line in file:
            if not line.strip():
                continue

            line = line.rstrip()
            contents = line.split(";")
            ship_type = contents[0]
            ship_coordinates = contents[1:len(contents)]
            ship_size = len(ship_coordinates)

            for coord in ship_coordinates:
                if not(validate_coordinate(coord)):
                    print("Error in ship coordinates!")
                    return None

                if coord in all_coordinates:
                    print("There are overlapping ships in the input file!")
                    return None

                all_coordinates.append(coord)

            ship = Ship(ship_type, ship_size, ship_coordinates)
            ship_list.append(ship)

        file.close()
        return ship_list

    except OSError:
        print(f"File can not be read!")
        return None


def create_board(board_size):
    """
    Creates the game board based on the given size
    :param board_size: int, the given size of the board game
    :return: list<str>, the list represents the game board
    """
    game_board = []
    # The list for a game board consists of a list of board size's rows.
    # Each row consists of a list of board size's spaces.
    for i in range(board_size):
        row = ' ' * board_size
        row_list = list(row)
        game_board.append(row_list)
    return game_board


def print_board(board):
    """
    Prints the given game board
    :param board: list, the list represents the game board
    """
    print()
    cols = " "  # the left side space of column index
    for char in REFERENCE:
        cols += " " + char
    print(cols)  # column index on top of the board
    for i in range(len(board[0])):  # len(board[0]) = board size
        print(f"{i}", end=' ')  # row index on left side
        for element in board[i]:
            print(element, end=' ')
        print(f"{i}")  # row index on right side
    print(cols)  # column index on bottom of the board
    print()


def mark_coord(board, col, row, is_hit):
    """
    Marks the shot coordinate with a specific symbol.
    The symbol varies by the situation if the coordinate
    belongs to the ship's place or not.
    :param board: list, the list represents the game board
    :param col: str, the column's element of the coordinate
    :param row: int, the row's element of the coordinate
    :param is_hit: bool, true if the shot hits the ship
    :return: list, the list represents the renewed game board
    """
    row = int(row)
    # Converts alphabet to int by getting a corresponding index
    # from the reference list
    index = int(REFERENCE.index(col))
    board_row = board[row]

    if is_hit:
        board_row[index] = 'X'
    else:
        board_row[index] = '*'

    return board


def mark_sunk_ship(board, ship):
    """
    Marks the ship place with the initial alphabet of the ship type
    if the ship got sunk.
    :param board: board: list, the list represents the game board
    :param ship: Ship, the sunk ship
    :return: list, the list represents the renewed game board
    """
    for coord in ship.get_ship_coordinates():
        row = int(coord[1])
        # Converts alphabet to int by getting a corresponding index
        # from the reference list
        index = int(REFERENCE.index(coord[0].upper()))
        board_row = board[row]
        # Marks the coordinate with the upper case initial alphabet
        # of the type of the ship
        board_row[index] = ship.get_ship_type()[0].upper()
    return board


def hit_ship(ship_list, coord):
    """
    Checks if there is a ship at the shot coordinates,
    and if so, return the ship.
    :param ship_list: the list of ships in the game board
    :param coord: the coordinate shot by a user
    :return: Ship | None
    """
    for ship in ship_list:
        if ship.is_hit(coord):
            return ship
    return None


def main():
    filename = input("Enter file name: ")
    ship_list = read_file(filename)
    if not ship_list:
        return

    been_shot_coord = []
    num_of_sunk_ship = 0
    game_board = create_board(BOARD_SIZE)

    while True:
        print_board(game_board)

        if num_of_sunk_ship == len(ship_list):
            print('Congratulations! You sank all enemy ships.')
            break

        coord = input("Enter place to shoot (q to quit): ")

        if coord == "q" or coord == "Q":
            print("Aborting game!")
            break

        if not validate_coordinate(coord):
            print('Invalid command!')
            continue

        x = coord[0].upper()
        y = coord[1]
        coord = x + y

        if coord in been_shot_coord:
            print("Location has already been shot at!")
            continue

        ship = hit_ship(ship_list, coord)
        been_shot_coord.append(coord)

        if not ship:
            game_board = mark_coord(game_board, x, y, False)
            continue

        ship.add_hit_counts()

        if ship.is_sunk(ship.get_hit_counts()):
            mark_sunk_ship(game_board, ship)
            num_of_sunk_ship += 1
            print(f'You sank a {ship.get_ship_type()}!')
        else:
            game_board = mark_coord(game_board, x, y, True)


if __name__ == "__main__":
    main()
