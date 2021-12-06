#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Imprime todos os valores de um vetor de inteiros de tamanho n
void imprimeVetor(int* v, int n);

// Imprime todos os valores de uma matriz de inteiros de tamanho n x m
void imprimeMatriz(int** mat, int n, int m);

typedef struct analise{
    clock_t tempoInicial;
    clock_t tempoFinal;
    double deltaTempo;
}Analise;

void iniciarTempo(Analise* a);
void finalizarTempo(Analise* a);
double getDeltaTempo(Analise* a);

// Retorna a média de um vetor de double, com tamanho n
double calculaMedia(double* v, int n);

// Lê um grafo armazenado em um arquivo texto, onde o número de vértices é seguido pela matriz de adjacência
int** leGrafo(char* nomeArquivo, int* n);

#endif