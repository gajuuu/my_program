"""
This program reads user inputs about the amount of days
and the temperature of each day. It calculates and displays
the mean and median of those temperatures.
It compares each day's temperature and median value,
and according to the result, it also displays the differences
between each day's temperature and mean value.
"""


def mean(temp_list):
    """
    Calculates the mean of the values of the list.
    :param temp_list: list, the list of values(floats)
    :return: float, the mean of the values of the list
    """
    return sum(temp_list) / len(temp_list)


def median(temp_list):
    """
    Calculates the median of the values of the list.
    :param temp_list: list, the list of values(floats)
    :return: float, the median of the values of the list
    """
    sorted_temp = sorted(temp_list)
    # Divide cases according to whether the number of elements is
    # even or odd.
    if len(temp_list) % 2 != 0:
        return sorted_temp[len(temp_list) // 2]
    else:
        return (sorted_temp[len(temp_list) // 2 - 1]
                + sorted_temp[len(temp_list) // 2]) / 2


def over_or_at_median(temp_list, mean_value, median_value):
    """
    Compares each day's temperature and median value.
    If median value is higher, displays the differences
    between each day's temperature and mean value.
    :param temp_list: list[float], the list of values
    :param mean_value: float, the mean value of the list
    :param median_value: float, the median value of the list
    """
    print("Over or at median were: ")
    for index in range(len(temp_list)):
        temp = temp_list[index]
        if temp >= median_value:
            print(f"Day{index + 1:>3}.{temp:>6.1f}C "
                  f"difference to mean:{temp - mean_value:>6.1f}C")


def under_median(temp_list, mean_value, median_value):
    """
    Compares each day's temperature and median value.
    If median value is lower, displays the differences
    between each day's temperature and mean value.
    :param temp_list: list[float], the list of values
    :param mean_value: float, the mean value of the list
    :param median_value: float, the median value of the list
    """
    print("Under median were: ")
    for index in range(len(temp_list)):
        temp = temp_list[index]
        if temp < median_value:
            print(f"Day{index + 1:>3}.{temp:>6.1f}C "
                  f"difference to mean:{temp - mean_value:>6.1f}C")


def read_input():
    """
    Reads user inputs and adds each day's temperature to the list
    :return: list, the list of the temperatures
    """
    day = int(input("Enter amount of days: "))
    temp_list = []
    for i in range(day):
        temp = float(input(f"Enter day {i+1}. temperature in Celcius: "))
        temp_list.append(temp)
    return temp_list


def main():
    temp_list = read_input()
    mean_value = mean(temp_list)
    median_value = median(temp_list)

    print()
    print(f"Temperature mean: {mean_value:.1f}C")
    print(f"Temperature median: {median_value:.1f}C")
    print()
    over_or_at_median(temp_list, mean_value, median_value)
    print()
    under_median(temp_list, mean_value, median_value)


if __name__ == "__main__":
    main()
