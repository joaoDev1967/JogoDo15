#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


int jogo[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

int posicao[2];
int numMoviveis[4] = {0, 0, 0, 0};

void posicaoDoZero(int posicao[2], int jogo[4][4]) {
    //retorna a posição em que o número zero está no jogo
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

void resetJogo(int jogo[4][4]){
    //Faz com que o tabuleiro volte à ordem padrão
    int ciclos=1;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(ciclos==16){ciclos=0;}
            jogo[i][j]=ciclos;
            ciclos++;
        }
    }
}

void mostrarJogo(int jogo[4][4]) {
    //mostra o jogo na tela
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
    //Mostra os número que podem se mover no jogo
    for(int i=0;i<4;i++){
        numMoviveis[i]=0;
    }
    posicaoDoZero(posicao, jogo);
    // cima0, direita1, esquerda2, baixo3
    int i = posicao[0];
    int j = posicao[1];

    if (i != 0) {
        //cima
        numMoviveis[0] = jogo[i - 1][j];
    } else {
        numMoviveis[0] = 0;
    }

    if (j != 3) {
        //direita
        numMoviveis[1] = jogo[i][j + 1];
    } else {
        numMoviveis[1] = 0;
    }

    if (j != 0) {
        //esquerda
        numMoviveis[2] = jogo[i][j - 1];
    } else {
        numMoviveis[2] = 0;
    }

    if (i != 3) {
        //baixo
        numMoviveis[3] = jogo[i + 1][j];
    } else {
        numMoviveis[3] = 0;
    }
}

bool inArray(int array[16], int num) {
    //verifica se um número especifico está dentro de um array númerico
    for (int i = 0; i < 16; i++) {
        if (array[i] == num) {
            return true;
        }
    }
    return false;
}

void embaralharJogo(int jogo[4][4]) {
    //Emabaralha a ordem dos números do jogo
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

bool verificarVitrotia(int jogo[4][4]){
    //verifica se o jogo está na ordem númerica que leva a vitória
    int sequencia=0, ciclos=1;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(ciclos==16){
                ciclos=0;
            }
            if(jogo[i][j]==ciclos){
                sequencia++;
            }
            ciclos++;
        }
    }
    if(sequencia==16){
        return true;
    }
    else{
        return false;
    }
}

void mostrarInstrucoes(){
    //mostra as intruções do jogo
    printf("Para jogar o jogo do 15 se faz necessario\nque voce ponha em ordem crescente os numeros embaralhados");
    printf("\nEis como o jogo deve ser organizado ao final: \n\n");
    mostrarJogo(jogo);
    printf("\nO espaco vazio deve estar no final\n\n");
}

void mover(int jogo[4][4], int posicao[2],int numMovido){
    //move um número especifico no jogo
    int linhaNumMovido=0;
    int colunaNumMovido=0;
    int linhaDoZero=posicao[0];
    int colunaDoZero=posicao[1];
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            if(jogo[i][j]==numMovido){
                linhaNumMovido=i;
                colunaNumMovido=j;
            }
        }
    }
    jogo[linhaDoZero][colunaDoZero]=numMovido;
    jogo[linhaNumMovido][colunaNumMovido]=0;
}

int main(void) {
    srand(time(NULL));
    char continuar='s';
    int ciclos=0;
    int numValido;
    while(tolower(continuar)=='s'){
        int moviemento=0;
        numValido=0;
        system("cls");
        if(ciclos==0){
            ciclos++;
            mostrarInstrucoes();
            embaralharJogo(jogo);
        }
        printf("\n\n");
        encontrarNumMoviveis(numMoviveis,jogo,posicao);
        while(numValido==0){
            for(int i=0;i<5;i++){
                printf("\n");
            }
            mostrarJogo(jogo);
            printf("Qual numero dentre esses ");
            for(int i=0;i<4;i++){
                if(numMoviveis[i]!=0){
                    printf("[%d]",numMoviveis[i]);
                }
            }
            printf(" voce deseja mover: ");
            scanf("%d",&moviemento);
            for(int i=0;i<4;i++){
                if(numMoviveis[i]==moviemento||moviemento==1889){
                    numValido=1;
                }
            }
            if(numValido==0){
                system("cls");
                printf("Voce digitou uma opcao invalida, por favor digite uma opcao valida");
                sleep(3);
                system("cls");
            }
        }
        if(moviemento!=1889){
            mover(jogo,posicao,moviemento);
        }
        else{
            resetJogo(jogo);
            mostrarJogo(jogo);
            sleep(2);
        }
        if(verificarVitrotia(jogo)){
            printf("\n\n\n\nVOCE VENCEU!!!\n\nDeseja jogar novamente[s/n]: ");
            scanf(" %c",&continuar);
            ciclos=0;
        }
        else{
            ciclos++;
        }

    }
    return 0;
}
