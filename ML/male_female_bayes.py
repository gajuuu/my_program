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

num_bins = 10
range_h = (80, 220)
range_w = (30, 180)

predictions = np.zeros(len(y_test))
predictions_h = np.zeros(len(y_test))
predictions_w = np.zeros(len(y_test))

# Get the number of data for each bin and the edge of bins
m_h_hist, bin_m_h = np.histogram(m_heights_list, bins=num_bins, range=range_h)
m_w_hist, bin_m_w = np.histogram(m_weights_list, bins=num_bins, range=range_w)
f_h_hist, bin_f_h = np.histogram(f_heights_list, bins=num_bins, range=range_h)
f_w_hist, bin_f_w = np.histogram(f_weights_list, bins=num_bins, range=range_w)

# Get the center of each bin
bin_centers_h = (bin_m_h[:-1] + bin_m_h[1:]) / 2
bin_centers_w = (bin_m_w[:-1] + bin_m_w[1:]) / 2

for i in range(len(x_test)):
    # height and weight of the test sample
    test_h = x_test[i][0]
    test_w = x_test[i][1]

    # Get the nearest bin index
    nearest_bin_index_h = np.argmin(abs(bin_centers_h - test_h))
    nearest_bin_index_w = np.argmin(abs(bin_centers_w - test_w))

    # print(f"nearest bin for w {nearest_bin_index_w}")
    # print(f"test_w {test_w}")
    # print(f"center_w {bin_centers_w}")

    # Calculate each likelihood
    m_h_likelihood = m_h_hist[nearest_bin_index_h] / len(m_heights_list)
    f_h_likelihood = f_h_hist[nearest_bin_index_h] / len(f_heights_list)
    m_w_likelihood = m_w_hist[nearest_bin_index_w] / len(m_weights_list)
    f_w_likelihood = f_w_hist[nearest_bin_index_w] / len(f_weights_list)

    # Calculate priori probabilities
    prior_m = len(m_heights_list) / len(x_train)
    prior_f = len(f_heights_list) / len(x_train)

    # print(prior_m)
    # print(prior_f)
    # print(m_h_likelihood)
    # print(f_h_likelihood)
    # print(m_w_likelihood)
    # print(f_w_likelihood)

    # Calculate posterior probabilities
    post_m_h = prior_m * m_h_likelihood
    post_f_h = prior_f * f_h_likelihood
    post_m_w = prior_m * m_w_likelihood
    post_f_w = prior_f * f_w_likelihood
    post_m_both = prior_m * m_h_likelihood * m_w_likelihood
    post_f_both = prior_f * f_h_likelihood * f_w_likelihood

    if post_m_h > post_f_h:
        predictions_h[i] = 0
    else:
        predictions_h[i] = 1

    if post_m_w > post_f_w:
        predictions_w[i] = 0
    else:
        predictions_w[i] = 1

    if post_m_both > post_f_both:
        predictions[i] = 0
    else:
        predictions[i] = 1

accuracy_h = np.mean(predictions_h == y_test)
print(f'Classification Accuracy (by heights): {accuracy_h}')

accuracy_w = np.mean(predictions_w == y_test)
print(f'Classification Accuracy (by weights): {accuracy_w}')

accuracy = np.mean(predictions == y_test)
print(f'Classification Accuracy (by both): {accuracy}')