"""
This program reads user input,
calculates some statistical characteristics,
and displays them.
"""

import math


def read_measurement():
    """
    Reads seawater levels that the user input and returns
    a list of these values.

    :return: list, the list of values the user input
    which is sorted in ascending order
    """
    # initialise the list
    measurements = []

    # Do the loop until user inputs empty line
    while True:
        # convert the user input(string) to float
        user_input = input()
        # the condition to stop the loop
        if user_input == "":
            break
        else:
            sea_level = float(user_input)
            # add the value to the list
            measurements.append(sea_level)

    return sorted(measurements)


def median(float_list):
    """
    Calculates the median of the values of the list.

    :param float_list: list, the list of values(floats)
    :return: float, the median of the values of the list
    """

    # Divide cases according to whether the number of
    # elements is even or odd.
    if len(float_list) % 2 == 1:
        # Return the element right in the middle of the list
        return float_list[math.floor(len(float_list) / 2)]
    else:
        # Add the two elements in the middle of the list
        # and divide by two
        return ((float_list[len(float_list) // 2 - 1]
                 + float_list[len(float_list) // 2]) / 2)


def mean(float_list):
    """
    Calculates the mean of the values of the list.

    :param float_list: list, the list of values(floats)
    :return: float, the mean of the values of the list
    """
    # add all elements of the list and divide by
    # the number of elements
    return sum(float_list) / len(float_list)


def deviation(float_list):
    """
    Calculates the standard deviation of the values of the list.

    :param float_list: list, the list of values(floats)
    :return: float, the deviation of the values of the list
    """
    # initialise the variance
    variance = 0
    # Subtract the mean from each value,
    # square it, divide by (number of elements - 1)
    # and add it together using the loop.
    for element in float_list:
        variance += (element - mean(float_list)) ** 2 \
                    / (len(float_list) - 1)

    # Square the variance to get the standard deviation
    return math.sqrt(variance)


def main():
    print("Enter seawater levels in centimeters one per line.\n"
          "End by entering an empty line.")

    measurements = read_measurement()

    if len(measurements) < 2:
        return print("Error: At least two measurements must be entered!")
    else:
        print(f"Minimum:   {measurements[0]:.2f} cm")
        print(f"Maximum:   {measurements[-1]:.2f} cm")
        print(f"Median:    {median(measurements):.2f} cm")
        print(f"Mean:      {mean(measurements):.2f} cm")
        print(f"Deviation: {deviation(measurements):.2f} cm")


if __name__ == "__main__":
    main()
