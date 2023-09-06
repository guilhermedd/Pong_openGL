import subprocess
import pyautogui

# Comando para executar o programa em C (substitua "seu_programa" pelo nome do seu executável)
executar_comando = ["../pong.out"]

# Inicie o processo e redirecione a saída padrão para um PIPE
processo = subprocess.Popen(
    executar_comando, stdout=subprocess.PIPE, universal_newlines=True)

# Lista para armazenar os valores
valores = []

# Loop para ler a saída em tempo real
prev_value = [0, 0, 0, 0, 0]
for linha in processo.stdout:
    recent_value = linha.split(',')
    recent_value = [float(x) for x in recent_value]
    print(recent_value)
    if recent_value == prev_value:
        print("Repetido")
        pyautogui.press('space')
    prev_value = recent_value

# Aguarde o término do processo
processo.wait()

# Após o término, imprima a média final
media_final = sum(valores) / len(valores)
print("Média final:", media_final)
