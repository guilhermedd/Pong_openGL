import gymnasium as gym
import math
import random
import matplotlib
import matplotlib.pyplot as plt
from collections import namedtuple, deque
from itertools import count
import numpy as np

import torch
import torch.nn as nn
import torch.optim as optim
import torch.nn.functional as F


# Definir a rede neural
class QNetwork(nn.Module):
    def __init__(self, input_size, output_size):
        # input_size: tamanho da entrada ( geralmente é o número de estados)
        # output_size: tamanho da saída (geralmente é o número de ações)
        super(QNetwork, self).__init__()
        # Definir as camadas da rede neural

        # Primeira camada oculta
        self.fc1 = nn.Linear(input_size,
                             128)  # 128 é o número de neurônios da camada escondida. Esta é uma camada totalmente conectada ( significa que cada neurônio da camada escondida está conectado a todos os neurônios da camada de entrada)
        # Camada de saída
        self.fc2 = nn.Linear(128,
                             output_size)  # Esta é a camada de saída. O número de neurônios é igual ao número de ações possíveis

    def forward(self, x):  # x são os dados de entrada
        # Definir a passagem para frente da rede neural
        x = torch.relu(self.fc1(x))  # Passagem pela primeira camada oculta e função de ativação
        x = self.fc2(x)  # Passagem pela camada de saída
        return x


# Definir a classe do agente DQN
class DQN:
    def __init__(self, state_size, action_size):
        self.q_network = QNetwork(state_size,
                                  action_size)  # Rede neural que estima a Q-value. É a rede neural principal que será treinada para tomar decisões
        self.target_q_network = QNetwork(state_size,
                                         action_size)  # Rede neural que estima a Q-value. É uma cópia da rede neural principal que será usada para calcular a Q-value esperada
        self.target_q_network.load_state_dict(
            self.q_network.state_dict())  # Inicializa a rede neural target com os mesmos pesos da rede neural principal
        self.target_q_network.eval()  # Coloca a rede neural target no modo de avaliação (ela não será treinada)

        self.loss_fn = nn.MSELoss()  # Função de perda. Quantifica o erro entre a Q-value estimada e a Q-value esperada
        self.optimizer = optim.Adam(self.q_network.parameters(),
                                    lr=0.001)  # Otimizador. Algoritmo usado para atualizar os pesos da rede neural

    def train(self, state, action, reward, next_state, done):
        state = torch.tensor(state, dtype=torch.float32).unsqueeze(0)  # Add a batch dimension
        next_state = torch.tensor(next_state, dtype=torch.float32).unsqueeze(0)  # Add a batch dimension
        action = torch.tensor(action, dtype=torch.long).unsqueeze(0)  # Add a batch dimension
        reward = torch.tensor(reward, dtype=torch.float32).unsqueeze(0)  # Add a batch dimension
        done = torch.tensor(done, dtype=torch.float32).unsqueeze(0)  # Add a batch dimension

        q_values = self.q_network(state)
        q_value = q_values.gather(1, action.view(-1, 1)).squeeze(1)  # Fix the indexing

        next_q_values = self.target_q_network(next_state)
        next_q_value = next_q_values.max(1)[0]
        expected_q_value = reward + (1 - done) * 0.99 * next_q_value

        loss = self.loss_fn(q_value, expected_q_value.detach())
        self.optimizer.zero_grad()
        loss.backward()
        self.optimizer.step()

    def update_target_network(self):
        self.target_q_network.load_state_dict(
            self.q_network.state_dict())  # Copia os pesos da rede neural principal para a rede neural target


env = gym.make('CartPole-v1', render_mode='human')

state_size = env.observation_space.shape[0]  # Tamanho do estado
action_size = env.action_space.n  # Número de ações possíveis

dqn = DQN(state_size, action_size)

num_episodes = 1000
for episode in range(num_episodes):
    state = env.reset()
    total_reward = 0
    done = False

    while not done:
        env.render()
        # Escolhe uma ação usando a política epsilon-greedy
        epsilon = 0.1
        if np.random.uniform(-1, 0) < epsilon:  # Com probabilidade epsilon escolhe uma ação aleatória
            action = env.action_space.sample()  # Escolhe uma ação aleatória
        else:
            print(state)
            q_values = dqn.q_network(torch.tensor(state[0], dtype=torch.float32))  # Passa o estado atual pela rede neural
            action = q_values.argmax().item()  # Escolhe a ação com maior Q-value

        next_state, reward, done, _, _ = env.step(action)
        total_reward += reward

        # Treina a rede
        state_tensor = torch.tensor(state[0], dtype=torch.float32)
        dqn.train(state_tensor, action, reward, next_state,
                  done)  # Treina a rede neural principal usando a experiência atual (state, action, reward,
        # next_state, done)

        state = next_state
        # Treina a rede neural principal usando a experiência atual (state, action, reward,
        # next_state, done)

    if episode % 10 == 0:
        dqn.update_target_network()
        print(f'Episode {episode}, Total Reward: {total_reward}')

env.close()
