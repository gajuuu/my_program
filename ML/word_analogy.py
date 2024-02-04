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
    user_input = input("\nEnter three words (EXIT to break): ")

    if user_input == 'EXIT':
        break
    else:
        three_words = user_input.rstrip().split("-")

        vector1 = vectors[three_words[0]]
        vector2 = vectors[three_words[1]]
        vector3 = vectors[three_words[2]]

        analogy = [r + q - p for p, q, r in zip(vector1, vector2, vector3)]

        gap_list = []
        for key in vectors:
            distance_from_analogy = np.sqrt(np.sum((i - j) ** 2 for i, j
                                                   in zip(vectors[key], analogy)))
            gap_list.append(distance_from_analogy)

        sorted_distances = sorted(gap_list)
        min_five = sorted_distances[:5]

        counter = 0
        for x in min_five:
            index = gap_list.index(x)
            if ivocab[index] not in three_words:
                counter += 1
                print(f"Word {counter}: {ivocab[index]}")
                if counter == 2:
                    break
