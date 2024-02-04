import numpy as np
import matplotlib.pyplot as plt


# Linear solver
def my_linefit(x, y):
    n = len(x)

    if n == 0:
        return

    sum_x = np.sum(x)
    sum_y = np.sum(y)
    sum_xy = sum(xi * yi for xi, yi in zip(x, y))
    sum_x_squared = sum(xi ** 2 for xi in x)

    b = ((sum_x_squared * sum_y) - (sum_xy * sum_x)) \
        / (n * sum_x_squared - (sum_x * sum_x))
    a = (-1 * b * sum_x + sum_xy) / sum_x_squared

    return a, b


def on_click(event):
    if event.button == 1:
        x.append(event.xdata)
        y.append(event.ydata)
        plt.plot(event.xdata, event.ydata, 'kx')
        plt.draw()
    elif event.button == 3 and len(x) >= 2:
        a, b = my_linefit(x, y)
        xp = np.arange(-2, 5, 0.1)
        plt.plot(xp, a * xp + b, 'r-')
        print(f"My fit: a={a} and b={b}")
        plt.draw()


# def main():
x = []
y = []

fig, ax = plt.subplots()
ax.set_xlim(-2, 5)
ax.set_ylim(0, 3)
fig.canvas.mpl_connect('button_press_event', on_click)
plt.show()

#
# if __name__ == "__main__":
#     main()
