import numpy as np

x_train = np.loadtxt("male_female_X_train.txt")
y_train = np.loadtxt("male_female_y_train.txt")
x_test = np.loadtxt("male_female_X_test.txt")
y_test = np.loadtxt("male_female_y_test.txt")

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

f_heights_test = []
m_heights_test = []
f_weights_test = []
m_weights_test = []

for data, key in zip(x_test, y_test):
    if key == 0:
        m_heights_test.append(data[0])
        m_weights_test.append(data[1])
    else:
        f_heights_test.append(data[0])
        f_weights_test.append(data[1])

# Random Classifier
random_predictions = np.random.randint(0, 2, len(y_test))
random_accuracy = np.mean(random_predictions == y_test)
print("Random Classifier Accuracy:", random_accuracy)

# Most Likely Class Classifier
prior_m_h = len(m_heights_list) / len(x_train)
prior_f_h = len(f_heights_list) / len(x_train)

most_likely_predictions = np.zeros(len(x_test))
for i in range(len(x_test)):
    if prior_m_h > prior_f_h:
        most_likely_predictions[i] = 0
    else:
        most_likely_predictions[i] = 1
most_likely_accuracy = np.mean(most_likely_predictions == y_test)
print("Most Likely Class Classifier Accuracy:", most_likely_accuracy)
