import random
import numpy as np

vocabulary_file = 'word_embeddings.txt'

# Read words
print('Read words...')
with open(vocabulary_file, 'r', encoding="utf8") as f:
    words = [x.rstrip().split(' ')[0] for x in f.readlines()]

# Read word vectors
print('Read word vectors...')
with open(vocabulary_file, 'r', encoding="utf8") as f:
    vectors = {}  # dictionary
    for line in f:
        vals = line.rstrip().split(' ')
        vectors[vals[0]] = [float(x) for x in vals[1:]]  # vals[0]:word = key

vocab_size = len(words)
vocab = {w: idx for idx, w in enumerate(words)}
ivocab = {idx: w for idx, w in enumerate(words)}

# Vocabulary and inverse vocabulary (dict objects)
print('Vocabulary size')
print(len(vocab))
print(vocab['man'])
print(len(ivocab))
print(ivocab[10])

# W contains vectors for
print('Vocabulary word vectors')
vector_dim = len(vectors[ivocab[0]])
W = np.zeros((vocab_size, vector_dim))
for word, v in vectors.items():
    if word == '<unk>':
        continue
    W[vocab[word], :] = v

# Main loop for analogy
while True:
    input_term = input("\nEnter a word (EXIT to break): ")
    if input_term == 'EXIT':
        break
    else:
        distance_list = []
        for key in vectors:
            distance = np.sqrt(np.sum((j - i) ** 2 for i, j
                                      in zip(vectors[key],
                                             vectors[input_term])))
            distance_list.append(distance)

        sorted_distances = sorted(distance_list)
        min_three = sorted_distances[:3]

        print("\n                               Word       Distance\n")
        print("---------------------------------------------------------\n")
        for x in min_three:
            index = distance_list.index(x)
            print("%35s\t\t%f\n" % (ivocab[index], x))

