import numpy as np
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
from sklearn.tree import DecisionTreeRegressor
from sklearn.ensemble import RandomForestRegressor

x_train = np.loadtxt("disease_X_train.txt")
y_train = np.loadtxt("disease_Y_train.txt")
x_test = np.loadtxt("disease_X_test.txt")
y_test = np.loadtxt("disease_Y_test.txt")

# print(f"y_train: {y_train}")
# print(f"y_test: {y_test}")

# Calculate the mean of the training data
baseline_prediction = np.mean(y_train)
# print(f"baseline_prediction: {baseline_prediction}")

# Create an array of baseline predictions for the test data
baseline_predictions = [baseline_prediction] * len(y_test)
# print(f"baseline_predictions: {baseline_predictions}")

# Compute Mean Squared Error (MSE)
baseline_mse = mean_squared_error(y_test, baseline_predictions)

# Print the baseline MSE
print(f"Baseline MSE: {baseline_mse:.2f}")

model1 = LinearRegression()
model1.fit(x_train, y_train)
linear_predictions = model1.predict(x_test)
linear_mse = mean_squared_error(y_test, linear_predictions)
print(f"Test Set MSE (Linear Regression): {linear_mse:.2f}")

model2 = DecisionTreeRegressor()
model2.fit(x_train, y_train)
tree_predictions = model2.predict(x_test)
tree_mse = mean_squared_error(y_test, tree_predictions)
print(f"Test Set MSE (Decision Tree): {tree_mse:.2f}")

model3 = RandomForestRegressor()
model3.fit(x_train, y_train)
forest_predictions = model3.predict(x_test)
forest_mse = mean_squared_error(y_test, forest_predictions)
print(f"Test Set MSE (Random Forest): {forest_mse:.2f}")