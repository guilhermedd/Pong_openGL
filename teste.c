#include <stdio.h>

int main()
{
    FILE *arquivo;
    int numeroExistente = 32;
    int numeroExistente2;
    int novoNumero = 42; // Seu novo número

    arquivo = fopen("arquivo.bin", "wb"); // Abra o arquivo binário para leitura
    fwrite(&numeroExistente, sizeof(int), 1, arquivo);
    fclose(arquivo); // Feche o arquivo

    if (arquivo != NULL)
    {
        // Leia o número existente do arquivo
        arquivo = fopen("arquivo.bin", "rb"); // Abra o arquivo binário para leitura
        fread(&numeroExistente2, sizeof(int), 1, arquivo);
        printf("O número existente no arquivo é: %d\n", numeroExistente2);
        fclose(arquivo); // Feche o arquivo
    }

    return 0;
}
