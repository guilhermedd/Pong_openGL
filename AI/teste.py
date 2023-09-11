import gym
import random

env = gym.make('CartPole-v1', render_mode="human")

episodes = 10

for episode in range(1, episodes + 1):
    state = env.reset()
    done = False
    score = 0

    while not done:
        action = random.choice([0, 1])
        state, reward, done, info , extra_info = env.step(action)  #  state = next_state | reward = reward for the action | done = is the episode done? | info = extra info | _ = extra info
        score += reward
        env.render()

    print('Episode:{} Score:{}'.format(episode, score))

env.close()
