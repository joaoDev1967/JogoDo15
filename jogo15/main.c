#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

int jogo[4][4] = {
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {8, 9, 10, 11},
    {12, 13, 14, 15}
};

int posicao[2];
int numMoviveis[4] = {0, 0, 0, 0};

void posicaoDoZero(int posicao[2], int jogo[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (jogo[i][j] == 0) {
                posicao[0] = i;
                posicao[1] = j;
                return;
            }
        }
    }
}

void mostarJogo(int jogo[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if(jogo[i][j]!=0){
               printf("%2d ", jogo[i][j]);
            }
            else{
                printf("___");
            }
        }
        printf("\n");
    }
}

void encontrarNumMoviveis(int numMoviveis[4],int jogo[4][4],int posicao[2]) {
    numMoviveis = {0, 0, 0, 0};
    posicaoDoZero(posicao, jogo);
    // baixo0, direita1, esquerda2, cima3
    int i = posicao[0];
    int j = posicao[1];

    if (i != 0) {
        numMoviveis[0] = jogo[i + 1][j];
    } else {
        numMoviveis[0] = 0;
    }

    if (j != 3) {
        numMoviveis[1] = jogo[i][j + 1];
    } else {
        numMoviveis[1] = 0;
    }

    if (j != 0) {
        numMoviveis[2] = jogo[i][j - 1];
    } else {
        numMoviveis[2] = 0;
    }

    if (i != 3) {
        numMoviveis[3] = jogo[i - 1][j];
    } else {
        numMoviveis[3] = 0;
    }
}

bool inArray(int array[16], int num) {
    for (int i = 0; i < 16; i++) {
        if (array[i] == num) {
            return true;
        }
    }
    return false;
}

void embaralharJogo(int jogo[4][4]) {
    int numsSorteados[16];
    for(int i=0;i<16;i++){
        numsSorteados[i]=-1;
    }
    int num = 0;
    int idSorteio = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (idSorteio == 0) {
                num = rand() % 16;
                numsSorteados[idSorteio] = num;
                jogo[i][j] = num;
                idSorteio++;
            } else {
                while (inArray(numsSorteados, num) && idSorteio <= 16) {
                    num = rand() % 16;
                }
                numsSorteados[idSorteio] = num;
                jogo[i][j] = num;
                idSorteio++;
            }
        }
    }
}

int main(void) {
    srand(time(NULL));
    mostarJogo(jogo);
    for(int i=0;i<3;i++){
        embaralharJogo(jogo);
        printf("\n\n\n\n");
        mostarJogo(jogo);
        encontrarNumMoviveis(numMoviveis,jogo,posicao);
        for(int i=0;i<4;i++){
            printf("%d",numMoviveis[i]);
        }
    }
    return 0;
}
