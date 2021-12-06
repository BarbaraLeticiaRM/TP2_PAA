#include "funcoes.h"

// Imprime todos os valores de um vetor de inteiros de tamanho n
void imprimeVetor(int* v, int n){
    int quebraLinha = 0;

    for(int i=0; i<n; i++){
        printf("%d ",v[i]);

        quebraLinha++;
        if(quebraLinha >= 25){
            printf("\n");
            quebraLinha = 0;
        }
    }
}

// Imprime todos os valores de uma matriz de inteiros de tamanho n x m
void imprimeMatriz(int** mat, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void iniciarTempo(Analise* a){
    a->tempoInicial = clock();
}

void finalizarTempo(Analise* a){
    a->tempoFinal = clock();
    
    a->deltaTempo = (double)(a->tempoFinal - a->tempoInicial) / CLOCKS_PER_SEC;
}

double getDeltaTempo(Analise* a){
    return a->deltaTempo;
}

// Retorna a média de um vetor de double, com tamanho n
double calculaMedia(double* v, int n){
    double soma = 0;

    for(int i = 0; i < n; i++){
        soma += v[i];
    }

    if(n == 0)
        return 0;
    else
        return soma / n;
}

// Lê um grafo armazenado em um arquivo texto, onde o número de vértices é seguido pela matriz de adjacência
int** leGrafo(char* nomeArquivo, int* n){
    FILE* f = fopen(nomeArquivo, "r");

    fscanf(f, "%d\n", n);

    int** matriz = (int **) malloc(*n * sizeof(int*));
    for(int i = 0; i < *n; i++){
        matriz[i] = (int *) malloc(*n * sizeof(int));
    }

    // Lendo o grafo
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            fscanf(f, "%d ", &matriz[i][j]);
        }
        fscanf(f, "\n");
    }

    fclose(f);

    return matriz;
}
