import numpy as np
import matplotlib.pyplot as plt

x_train = np.loadtxt("male_female_X_train.txt")
y_train = np.loadtxt("male_female_y_train.txt")

f_heights_list = []
m_heights_list = []
f_weights_list = []
m_weights_list = []

for data, key in zip(x_train, y_train):
    if key == 0:
        m_heights_list.append(data[0])
        m_weights_list.append(data[1])
    else:
        f_heights_list.append(data[0])
        f_weights_list.append(data[1])

num_bins = 10
range_h = (80, 220)
range_w = (30, 180)

plt.hist(m_heights_list, bins=num_bins, alpha=0.5, color='cyan', range=range_h, label='male')
plt.hist(f_heights_list, bins=num_bins, alpha=0.5, color='magenta', range=range_h, label='female')
plt.legend(loc='upper left')
plt.title('Training samples for two classes')
plt.xlabel('height')
plt.ylabel('number')

plt.figure()
plt.hist(m_weights_list, bins=num_bins, alpha=0.5, color='cyan', range=range_w, label='male')
plt.hist(f_weights_list, bins=num_bins, alpha=0.5, color='magenta', range=range_w, label='female')
plt.legend(loc='upper left')
plt.title('Training samples for two classes')
plt.xlabel('weight')
plt.ylabel('number')

plt.show()
