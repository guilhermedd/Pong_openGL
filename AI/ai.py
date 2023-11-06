import subprocess
import pyautogui
import time
import os

# Must be in Game dir
os.chdir('../Game')

# Comando para executar o programa em C (substitua "seu_programa" pelo nome do seu executável)
executar_comando = ["./pong.out"]

# Inicie o processo e redirecione a saída padrão para um PIPE
processo = subprocess.Popen(
    executar_comando, stdout=subprocess.PIPE, universal_newlines=True)

# Lista para armazenar os valores
valores = []

# Aguarde alguns segundos para o jogo iniciar
time.sleep(0.5)  # Ajuste este valor conforme necessário

# Pressione a tecla de espaço
pyautogui.press('1')
time.sleep(0.2)
pyautogui.press('space')
time.sleep(0.2)

# Loop para ler a saída em tempo real
for linha in processo.stdout:
    recent_value = linha.split(',')
    # print(recent_value)
    if 'Point' in recent_value[0]:
        print("Repetido")
        pyautogui.press('space')
    elif 'Erro ao carregar a textura da imagem' in recent_value[0]:
        continue
    else:
        recent_value = [float(x) for x in recent_value]
        print(recent_value)

# Aguarde o término do processo
processo.wait()

# Após o término, imprima a média final
