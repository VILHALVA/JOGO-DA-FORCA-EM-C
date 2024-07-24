#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_TENTATIVAS 6
#define MAX_LINHA 100
#define MAX_PALAVRAS 100

void mostrar_forca(int erros);
void mostrar_palavra(char* palavra, int* letras_adivinhadas, int tamanho);
int verificar_palpite(char* palavra, char palpite, int* letras_adivinhadas, int tamanho);
char* escolher_palavra_aleatoria(const char* arquivo);

int main() {
    char* palavra = escolher_palavra_aleatoria("word.txt");
    if (palavra == NULL) {
        printf("Erro ao ler o arquivo de palavras.\n");
        return 1;
    }

    int tamanho = strlen(palavra);
    int letras_adivinhadas[tamanho];
    int erros = 0;
    char palpite;
    int acertou = 0;

    memset(letras_adivinhadas, 0, sizeof(letras_adivinhadas));

    printf("Bem-vindo ao Jogo da Forca!\n");
    printf("Tente adivinhar a palavra.\n");

    while (erros < MAX_TENTATIVAS && !acertou) {
        mostrar_forca(erros);
        mostrar_palavra(palavra, letras_adivinhadas, tamanho);

        printf("Digite uma letra: ");
        scanf(" %c", &palpite);
        palpite = tolower(palpite);

        if (!verificar_palpite(palavra, palpite, letras_adivinhadas, tamanho)) {
            erros++;
        }

        acertou = 1;
        for (int i = 0; i < tamanho; i++) {
            if (!letras_adivinhadas[i]) {
                acertou = 0;
                break;
            }
        }
    }

    if (acertou) {
        printf("Parabéns! Você adivinhou a palavra: %s\n", palavra);
    } else {
        mostrar_forca(erros);
        printf("Que pena! Você perdeu. A palavra era: %s\n", palavra);
    }

    free(palavra);
    return 0;
}

void mostrar_forca(int erros) {
    switch (erros) {
        case 0:
            printf("  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n");
            break;
        case 1:
            printf("  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========\n");
            break;
        case 2:
            printf("  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n");
            break;
        case 3:
            printf("  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n");
            break;
        case 4:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n");
            break;
        case 5:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n");
            break;
        case 6:
            printf("  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n");
            break;
    }
}

void mostrar_palavra(char* palavra, int* letras_adivinhadas, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (letras_adivinhadas[i]) {
            printf("%c ", palavra[i]);
        } else {
            printf("_ ");
        }
    }
    printf("\n");
}

int verificar_palpite(char* palavra, char palpite, int* letras_adivinhadas, int tamanho) {
    int acertou = 0;
    for (int i = 0; i < tamanho; i++) {
        if (palavra[i] == palpite) {
            letras_adivinhadas[i] = 1;
            acertou = 1;
        }
    }
    return acertou;
}

char* escolher_palavra_aleatoria(const char* arquivo) {
    FILE* file = fopen(arquivo, "r");
    if (!file) {
        return NULL;
    }

    char* palavras[MAX_PALAVRAS];
    char linha[MAX_LINHA];
    int num_palavras = 0;

    while (fgets(linha, sizeof(linha), file)) {
        linha[strcspn(linha, "\n")] = '\0';  
        palavras[num_palavras] = malloc(strlen(linha) + 1);
        strcpy(palavras[num_palavras], linha);
        num_palavras++;
    }
    fclose(file);

    if (num_palavras == 0) {
        return NULL;
    }

    srand(time(NULL));
    int indice = rand() % num_palavras;

    char* palavra_aleatoria = palavras[indice];
    for (int i = 0; i < num_palavras; i++) {
        if (i != indice) {
            free(palavras[i]);
        }
    }

    return palavra_aleatoria;
}
