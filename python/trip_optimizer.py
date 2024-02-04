"""
This program reads file, reads the user's input,
and follows the user's command.

The following commands are possible.
1. display: to display all the distance data
2. add: to add new data
3. remove: to remove data
4. neighbours: to display the connections from a particular city
               to all of its neighbours
5. route: to display the route which one should take when travelling
          from the departure city to the destination city.
"""


# dictionary-dictionary


def find_route(data, departure, destination):
    """
    This function tries to find a route between <departure>
    and <destination> cities. It assumes the existence of
    the two functions fetch_neighbours and distance_to_neighbour
    (see the assignment and the function templates below).
    They are used to get the relevant information from the data
    structure <data> for find_route to be able to do the search.

    The return value is a list of cities one must travel through
    to get from <departure> to <destination>. If for any
    reason the route does not exist, the return value is
    an empty list [].

    :param data: dict, A data structure of an unspecified type (you decide)
           which contains the distance information between the cities.
    :param departure: str, the name of the departure city.
    :param destination: str, the name of the destination city.
    :return: list[str], a list of cities the route travels through, or
           an empty list if the route can not be found. If the departure
           and the destination cities are the same, the function returns
           a two element list where the departure city is stores twice.
    """

    # +--------------------------------------+
    # |                                      |
    # |     DO NOT MODIFY THIS FUNCTION!     |
    # |                                      |
    # +--------------------------------------+

    if departure not in data:
        return []

    elif departure == destination:
        return [departure, destination]

    greens = {departure}
    deltas = {departure: 0}
    came_from = {departure: None}

    while True:
        if destination in greens:
            break

        red_neighbours = []
        for city in greens:
            for neighbour in fetch_neighbours(data, city):
                if neighbour not in greens:
                    delta = deltas[city] + distance_to_neighbour(data, city, neighbour)
                    red_neighbours.append((city, neighbour, delta))

        if not red_neighbours:
            return []

        current_city, next_city, delta = min(red_neighbours, key=lambda x: x[2])

        greens.add(next_city)
        deltas[next_city] = delta
        came_from[next_city] = current_city

    route = []
    while True:
        route.append(destination)
        if destination == departure:
            break
        destination = came_from.get(destination)

    return list(reversed(route))


def route_distance(distance_dict):
    """
    Reads the departure and destination city the user input,
    and displays the cities via to destination and
    the total distance to arrive at destination city.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    """

    # Initialize the value
    total_distance = 0
    # Read the user input
    departure = input("Enter departure city: ")
    # Call an original function get_destinations
    # and get the list of destinations in the <distance_dict>.
    destination_list = get_destinations(distance_dict)

    # If the city user input does not exist both as a departure and
    # destination city, this program prints an error message
    # when user input the city's name.
    if (departure not in distance_dict
            and departure not in destination_list):
        print(f"Error: '{departure}' is unknown.")
    # Otherwise, the user also inputs a destination city.
    else:
        destination = input("Enter destination city: ")
        # Call a function find_route and get the list of cities
        # via to destination.
        city_list = find_route(distance_dict, departure, destination)

        # If city_list is empty list, print a massage.
        if not city_list:
            print(f"No route found between '{departure}' and '{destination}'.")
        # Otherwise, get the total_distance of the route and
        # print information.
        else:
            for idx in range(1, len(city_list)):
                # If the departure city is equal to the destination city,
                # total_distance remains 0.
                if departure == destination:
                    break
                # Otherwise, add up the distances between
                # two neighbouring cities in the list.
                else:
                    total_distance += \
                        distance_dict[city_list[idx - 1]][city_list[idx]]
            print("-".join(city_list), end=" ")
            print(f"({total_distance} km)")


def read_distance_file(file_name):
    """
    Reads the distance information from <file_name> and stores it
    in a suitable data structure (you decide what kind of data
    structure to use). This data structure is also the return value,
    unless an error happens during the file reading operation.

    :param file_name: str, The name of the file to be read.
    :return: dict or None, A data structure containing the information
             read from the <file_name> or None if any kind of error happens.
    """

    # Initialize the dictionary
    distance_dict = {}

    # Use try-except structure to except OSError
    try:
        file = open(file_name, mode="r", encoding="utf-8")
        # Delete unnecessary spaces
        for line in file:
            line = line.rstrip()

            # If there are empty lines, ignore them and
            # continue the for_loop.
            if line == "":
                continue

            # Cut out the elements at ";" and save them as a list.
            line_list = line.split(";")
            key = line_list[0]
            inner_key = line_list[1]
            # Convert string into integer
            distance = int(line_list[2])

            # If the key does not yet exist as a key in the dictionary,
            # add new key and value set to the outer dictionary.
            if key not in distance_dict:
                distance_dict[key] = {inner_key: distance}
            # If the key already exist as a key in the dictionary,
            # add the inner_key and value to the inner dictionary.
            else:
                distance_dict[key][inner_key] = distance

        return distance_dict

    except OSError:
        return None


def display_data(distance_dict):
    """
    Returns all the data in a certain format.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    """

    # Print all the data using for_loop.
    # Firstly, sort the departure cities in alphabetical order.
    for key in sorted(distance_dict):
        # Secondly, sort the destination cities in alphabetical order.
        for inner_key in sorted(distance_dict[key]):
            # Display in specified format.
            print(f"{key:14}{inner_key:14}{distance_dict[key][inner_key]:>5}")


def get_destinations(distance_dict):
    """
    Gets all destinations from <distance_dict>
    and returns the list of destinations.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    :return: list, the list of destinations
    """

    # Initialize the list
    destination_list = []
    # Check all the elements in the outer dictionary
    for key in distance_dict:
        # Check all the elements in the inner dictionary
        for inner_key in distance_dict[key]:
            #  If the key of the inner dictionary does not yet exist
            #  in the destination_list, add it to the list.
            if inner_key not in destination_list:
                destination_list.append(inner_key)
            #  If the key of the inner dictionary already exists
            #  in the destination_list, there is nothing to do.
            else:
                pass

    return destination_list


def add_data(distance_dict):
    """
    Adds new data which the user input to the <distance_dict>.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    :return: dict, a new dictionary added new data
    """

    # Read the user inputs.
    departure = input("Enter departure city: ")
    destination = input("Enter destination city: ")
    distance_str = input("Distance: ")

    # Use try-except structure to display an error message
    # when something that cannot be converted into an integer is entered.
    try:
        # Convert the user input into integer
        distance = int(distance_str)

        # If the key does not yet exist as a key in the dictionary,
        # add new key and value set to the outer dictionary.
        if departure not in distance_dict:
            distance_dict[departure] = {destination: distance}
        # If the key already exist as a key in the dictionary,
        # add the inner_key and value to the inner dictionary.
        else:
            distance_dict[departure][destination] = distance

        return distance_dict

    except ValueError:
        print(f"Error: '{distance_str}' is not an integer.")


def remove_data(distance_dict):
    """
    Removes data which the user input from the <distance_dict>.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    :return: dict, a new dictionary removed data which the user input
    """

    # Read the user input
    departure = input("Enter departure city: ")
    # Call an original function get_destinations
    # and get the list of destinations in the <distance_dict>.
    destination_list = get_destinations(distance_dict)

    # If the city user input does not exist both as a departure and
    # destination city, print an error message
    # when user input the city's name.
    if (departure not in distance_dict
            and departure not in destination_list):
        print(f"Error: '{departure}' is unknown.")
    # Otherwise, the user also inputs a destination city.
    else:
        destination = input("Enter destination city: ")
        # If the cities user input exists as a departure and
        # destination city, delete the data set from the <distance_dict>.
        if (departure in distance_dict
                and destination in distance_dict[departure]):
            del distance_dict[departure][destination]
        # Otherwise, display an error message.
        else:
            print(f"Error: missing road segment between", end=" ")
            print(f"'{departure}' and '{destination}'.")


def fetch_neighbours(data, city):
    """
    Returns a list of all the cities that are directly
    connected to parameter <city>. In other words, a list
    of cities where there exist an arrow from <city> to
    each element of the returned list. Return value is
    an empty list [], if <city> is unknown or if there are no
    arrows leaving from <city>.

    :param data: dict, A data structure containing the distance
           information between the known cities.
    :param city: str, the name of the city whose neighbours we
           are interested in.
    :return: list[str], the neighbouring city names in a list.
             Returns [], if <city> is unknown (i.e. not stored as
             a departure city in <data>) or if there are no
             arrows leaving from the <city>.
    """

    # Initialize the list
    neighbours_list = []
    # If the value of parameter city exists as a key
    # in the outer dictionary <data>, add the names of cities,
    # the keys of inner dictionary, to the <neighbours_list>.
    if city in data:
        for neighbour in data[city]:
            neighbours_list.append(neighbour)

    return neighbours_list


def distance_to_neighbour(data, departure, destination):
    """
    Returns the distance between two neighbouring cities.
    Returns None if there is no direct connection from
    <departure> city to <destination> city. In other words
    if there is no arrow leading from <departure> city to
    <destination> city.

    :param data: dict, A data structure containing the distance
           information between the known cities.
    :param departure: str, the name of the departure city.
    :param destination: str, the name of the destination city.
    :return: int | None, The distance between <departure> and
           <destination>. None if there is no direct connection
           between the two cities.
    """

    # Use try-except structure to except KeyError
    try:
        return data[departure][destination]
    except KeyError:
        return None


def neighbours_info(distance_dict):
    """
    Reads the departure city the user input,
    and displays the neighbour cities of it and the distance
    between the departure city and them.

    :param distance_dict: dict, a dictionary which contains
    the data of distances.
    """

    # Read the user input
    departure = input("Enter departure city: ")
    # Call a function fetch_neighbours and get the list of
    # the neighbouring cities to the departure city.
    city_list = fetch_neighbours(distance_dict, departure)
    # Call an original function get-destinations
    # and get the list of destinations in the <distance_dict>.
    destination_list = get_destinations(distance_dict)

    # If the city user input does not exist both as a departure and
    # destination city, print an error message.
    if (departure not in distance_dict
            and departure not in destination_list):
        print(f"Error: '{departure}' is unknown.")
    # If the <city_list> is empty, print nothing.
    elif not city_list:
        pass
    # Otherwise, print the information about the neighbouring cities
    # to the departure city.
    else:
        # Sort the neighbouring cities in alphabetical order.
        for neighbour in sorted(city_list):
            # Call a function distance_to_neighbour and
            # get the distances between the neighbouring cities
            # and the departure city.
            distance = (distance_to_neighbour(distance_dict,
                                              departure, neighbour))
            # Display in specified format.
            print(f"{departure:<14}{neighbour:<14}{distance:5}")


def main():
    input_file = input("Enter input file name: ")

    distance_data = read_distance_file(input_file)

    if distance_data is None:
        print(f"Error: '{input_file}' can not be read.")
        return

    while True:
        action = input("Enter action> ")

        if action == "":
            print("Done and done!")
            return

        elif "display".startswith(action):
            display_data(distance_data)

        elif "add".startswith(action):
            add_data(distance_data)

        elif "remove".startswith(action):
            remove_data(distance_data)

        elif "neighbours".startswith(action):
            neighbours_info(distance_data)

        elif "route".startswith(action):
            route_distance(distance_data)

        else:
            print(f"Error: unknown action '{action}'.")


if __name__ == "__main__":
    main()
