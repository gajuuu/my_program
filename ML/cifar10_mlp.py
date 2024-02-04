import pickle
import numpy as np
import matplotlib.pyplot as plt
from random import random

import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense
import keras


def unpickle(file):
    with open(file, 'rb') as f:
        my_dict = pickle.load(f, encoding="latin1")
    return my_dict


test_datadict = unpickle('C:/Users/fm728/Downloads/ML/week5/cifar-10-batches-py/test_batch')
test_x = test_datadict["data"]
test_y = test_datadict["labels"]
# print("test_1")
# print(test_x.shape)

label_dict = unpickle('C:/Users/fm728/Downloads/ML/week5/cifar-10-batches-py/batches.meta')
label_names = label_dict["label_names"]
test_x = test_x / 255.0
test_y = np.array(test_y)
# print("test_2")
# print(test_x.shape)
# print(test_y)

# for i in range(test_x.shape[0]):
#     # Show some images randomly
#     if random() > 0.999:
#         plt.figure(1)
#         plt.clf()
#         plt.imshow(test_x[i])
#         plt.title(f"Image {i} label={label_names[test_y[i]]} (num {test_y[i]})")
#         plt.pause(1)

train_x = []
train_y = []
for i in range(1, 6):
    train_datadict = unpickle(f'C:/Users/fm728/Downloads/ML/week5/cifar-10-batches-py/data_batch_{i}')
    train_x.append(train_datadict["data"])
    train_y.extend(train_datadict["labels"])

train_x = np.concatenate(train_x) / 255.0
train_y = np.array(train_y)
# print("training")
# print(train_x.shape)
# print(train_y)


# one-hot encoding
def one_hot_encode(labels):
    encoded_labels = np.zeros((len(labels), 10))
    for index, label in enumerate(labels):
        encoded_labels[index][label] = 1
    return encoded_labels


one_hot_train_y = one_hot_encode(train_y)
# print(one_hot_train_y)

# Model sequential
model = Sequential()

model.add(Dense(200, input_dim=3072, activation='sigmoid'))
model.add(Dense(100, activation='sigmoid'))
# Output layer
model.add(Dense(10, activation='tanh'))

# I played with ...
# Learning rate: 0.5, 0,25, 0.1
# The Number of Epochs: 20, 30, 50, 100, 200
opt = keras.optimizers.SGD(learning_rate=0.1)
model.compile(optimizer=opt, loss='mse', metrics=['mse'])
num_epochs = 50

tr_hist = model.fit(train_x, one_hot_train_y, epochs=num_epochs, verbose=1)

predictions_train = model.predict(train_x)
label_predictions_train = predictions_train.argmax(axis=1)
# print(f"prediction_train: {predictions_train}")
# print(f"prediction_train_label: {label_predictions_train}")
# print(f"train_y: {train_y}")
tot_correct_train = np.sum(train_y == label_predictions_train)
accuracy_train = (tot_correct_train / len(train_y)) * 100
print(f'Classification accuracy (training data): {accuracy_train:.2f}%')

predictions_test = model.predict(test_x)
label_predictions_test = predictions_test.argmax(axis=1)
# print(f"prediction_test: {predictions_test}")
# print(f"prediction_test_label: {label_predictions_test}")
# print(f"test_y: {test_y}")
tot_correct_test = np.sum(test_y == label_predictions_test)
accuracy_test = (tot_correct_test / len(test_y)) * 100
print(f'Classification accuracy (test data): {accuracy_test:.2f}%')

plt.plot(tr_hist.history['loss'])
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['training'], loc='upper right')
plt.show()