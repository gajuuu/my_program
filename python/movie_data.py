"""
A small program to manage movie related data. A dictionary of
dictionaries is used as the data structure.
The data is read from the text file and can be saved into the file.
"""

# Commands known to the program as global constants.
ADD_COMMAND = "a"
PRINT_COMMAND = "p"
SAVE_COMMAND = "s"
QUIT_COMMAND = "q"

# A message for an error that happens during the loading or saving of a file
# as a global constant.
FILE_ERROR_MESSAGE = "File processing error!"

# Separators in the text file as global constants.
PART_SEPARATOR = ";"
FACT_SEPARATOR = "="


def add_data(data):
    """Add a new fact to data. If the fact is related to a movie that has yet
    facts in the data, the movie is also added to the data.

    :param name: dict, a dictionary of dictionaries containing the movie data.
    """
    # Read the inputs from the user.
    name = input("Enter the name of the movie: ")
    fact_key = input("Enter the key: ")
    fact_value = input("Enter the value: ")

    # Add movie to the data, if the fact is related to a movie missing from
    # the data.
    if name not in data:
        data[name] = {}

    # Add the new fact to the data.
    data[name][fact_key] = fact_value


def read_choice():
    """Read a choice from the user and return it.

    :return: str, user's choice.
    """
    # Let us assume that the user is in wrong, as always.
    invalid_input = True

    # Read input, while it is invalid.
    while invalid_input:
        msg = ADD_COMMAND + ") Add, " + PRINT_COMMAND + ") Print, " + \
              SAVE_COMMAND + ") Save and " + QUIT_COMMAND + ") Quit: "
        print(msg)
        choice = input("Please, enter your selection: ")
        # A shorter alternative for a conditional expression applying
        # comparisons and logical operators.
        if choice in (ADD_COMMAND, PRINT_COMMAND, SAVE_COMMAND, QUIT_COMMAND):
            invalid_input = False
        else:
            print("Invalid choice!")

    # Return user's choice.
    return choice


def print_data(data):
    """Print the movie data. Does nothing, if there is no data.

    :param name: dict, a dictionary of dictionaries containing the movie data.
    """
    # Print the movie data. A nested loop is needed, because the data structure
    # is nested.
    for name in data:
        # Print the name of the movie.
        print(name)
        # Print the facts related to the named movie.
        for fact_key in data[name]:
            fact_value = data[name][fact_key]
            print("  -", fact_key, FACT_SEPARATOR, fact_value)


def load_data(file_name):
    """Tries to load movie data from a text file. Each line of the file has
    data of one movie. The format of a line is as follows:
    "movie name;1st key=1st value;2nd key=2nd value;...;nth key=nth value"
    The facts (key-value pairs) related to a movie and and the number of facts
    may vary. The file is assumed to be correctly formatted.

    :param file_name: str, the name of the file containing the data.
    :return: dict, a dictionary of dictonaries, where the key-value pairs
    of the returned dictionary are pairs of movie names and nested dictionaries,
    which consist of facts related of the movie. The return value is None,
    if an exception is raised.
    """
    try:
        # Try to open the file for the reading of the movie data.
        data_file = open(file_name, mode="r")

        # Initialize the a dictionary for the data.
        data = {}

        # Populate the dictionary, until the file has been processed.
        # A nested loop is needed, because the data structure is nested.
        for line in data_file:
            # Remove the character(s) that end the line.
            line = line.rstrip()

            # Split the line into names and facts.
            parts = line.split(PART_SEPARATOR)

            # Create a new nested dictionary for the facts.
            facts = {}

            # Populate the nested dictionary with facts taking into account
            # that the movie data starts with the name of the movie.
            for ind in range(1, len(parts)):
                # Add a new fact to the nested dictionary.
                fact_key, fact_value = parts[ind].split(FACT_SEPARATOR)
                facts[fact_key] = fact_value

            # Add the movie name and its facts in a nested dictionary into
            # the dictionary.
            data[parts[0]] = facts

        # Close the file.
        data_file.close()
    except OSError:
        # Make a note of an error.
        print(FILE_ERROR_MESSAGE)
        data = None

    # Return the data or the error code.
    return data


def save_data(file_name, data):
    """Tries to load movie data from a text file. Each line of the file has data
    of one movie. The format of a line is as follows:
    "movie name;1st key=1st value;2nd key=2nd value;...;nth key=nth value"
    The facts (key-value pairs) related to a movie and and the number of facts
    may vary.

    :param file_name: str, the name of the file containing the data.
    :param name: dict, a dictionary of dictionaries containing the movie data.
    """
    try:
        # Try to open the file for the saving of the data.
        data_file = open(file_name, mode="w")

        # Save movie data to the file. A nested loop is needed, because the data
        # structure is nested.
        for name in data:
            # The line starts with the movie name.
            line = name + PART_SEPARATOR

            # Add the facts of the movie to the line.
            for fact_key in data[name]:
                fact_value = data[name][fact_key]
                line += fact_key + FACT_SEPARATOR + fact_value
                line += PART_SEPARATOR

            # Remove the surplus separator from the end of the line by taking
            # a slice that ends to the second to last character.
            line = line[:-1]

            # Print a line of movie data and end the line.
            print(line, file=data_file)

        # Close the file.
        data_file.close()
    except OSError:
        # Make a note of an error.
        print(FILE_ERROR_MESSAGE)


def main():
    # The name of the file containing the movie data.
    FILE_NAME = "movie_data.txt"

    # Try to load the movie data.
    movie_data = load_data(FILE_NAME)
    print(movie_data)

    # Do not continue, if the data could not be loaded.
    if movie_data == None:
        return

    # Call functions until the user has had enough.
    do_the_loop = True
    while do_the_loop:
        # Decide what to do.
        choice = read_choice()
        if choice == ADD_COMMAND:
            add_data(movie_data)
        elif choice == PRINT_COMMAND:
            print_data(movie_data)
        elif choice == SAVE_COMMAND:
            save_data(FILE_NAME, movie_data)
        elif choice == QUIT_COMMAND:
            do_the_loop = False


if __name__ == "__main__":
    main()
