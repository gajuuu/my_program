# Load OpenAI Gym and other necessary packages
import gym
import random
import numpy as np
import time

# Environment
env = gym.make("Taxi-v3", render_mode='ansi')
env.reset()

# Training parameters for Q learning
alpha = 0.9  # Learning rate
gamma = 0.9  # Future reward discount factor
num_of_episodes = 1000
num_of_steps = 500  # per each episode

# Q tables for rewards
# Q_reward = -100000*np.ones((500,6)) # All same
Q_reward = -100000 * np.random.random((500, 6))  # Random


# Training w/ random sampling of actions
# For counting interactions
tot_interactions = 0
epsilon = 0.1
action_size = env.action_space.n
state_size = env.observation_space.n
qtable = np.random.rand(state_size, action_size)

for episode in range(num_of_episodes):
    state = env.reset()[0]
    # Choose action (epsilon-greedy)
    if np.random.uniform() < epsilon:
        action = np.argmax(qtable[state, :])
    else:
        action = np.random.randint(0, action_size)
    # Run episode
    for step in range(num_of_steps):
        new_state, reward, done, truncated, info = env.step(action)
        tot_interactions += 1
        # Choose action (epsilon-greedy)
        if np.random.uniform() < epsilon:
            new_action = np.argmax(qtable[state, :])
        else:
            new_action = np.random.randint(0, action_size)
        # Update rule
        if done:
            qtable[state, action] = reward
            break
        else:
            qtable[state, action] = qtable[state, action] + \
                                    alpha * (reward + gamma * np.max(qtable[new_state, :])
                                             - qtable[state, action])
            state = new_state
            action = new_action

# Testing
state = env.reset()[0]
tot_reward = 0
for t in range(50):
    action = np.argmax(qtable[state, :])
    state, reward, done, truncated, info = env.step(action)
    tot_reward += reward
    print(env.render())
    time.sleep(1)
    if done:
        print("Total reward %d" % tot_reward)
        break

# Calculate averages
num_of_evals = 50
eval_rewards = []
eval_steps = []


def eval_policy(qtable, num_episodes, max_steps):
    rewards = []
    # actions = []
    num_interactions = []

    for episode in range(num_episodes):
        state = env.reset()[0]
        total_reward = 0
        # total_action = 0
        num_interaction = 0

        for step in range(max_steps):
            action = np.argmax(qtable[state, :])
            new_state, reward, done, truncated, info = env.step(action)
            num_interaction += 1
            total_reward += reward
            # total_action += action
            if done:
                break
            else:
                state = new_state
        rewards.append(total_reward)
        num_interactions.append(num_interaction)
        env.close()
    return sum(rewards) / num_episodes, sum(num_interactions) / num_episodes


for repeat in range(10):
    eval_reward, eval_step = eval_policy(qtable, num_of_evals*10, 100)
    eval_rewards.append(eval_reward)
    eval_steps.append(eval_step)

# print(eval_rewards)
eval_reward_mean = np.mean(np.asarray(eval_rewards))
eval_steps_mean = np.mean(np.asarray(eval_steps))
print(f'Average of total rewards: {eval_reward_mean:.4f}')
print(f'Average number of actions: {eval_steps_mean:.4f}')