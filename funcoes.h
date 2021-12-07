#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função faz com que os elementos de "v" se tornem os elementos de "v2", ambos vetores de inteiros de tamanho n
void igualaVetor(int* v, int* v2, int n);

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

// Lê uma fórmula de satisfabilidade armazenada em um arquivo texto, onde o número de cláusulas é seguido
// pelas cláusulas em si
int** leFormula(char* nomeArquivo, int* nLinhasRotulos, int* nColunasRotulos);

// Retorna uma linha ou coluna da matriz de adjacência referente à posição de um literal no rótulo
int mapeiaPosicaoLiteral(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int posicaoLinha, int colunaLinha);

// l e c conterão, respectivamente, a linha e a coluna da posição de um literal nos rótulos referente à
// uma posição do vetor de solução
void mapeiaSolucao(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int posicaoSolucao, int* l, int* c);

// Gera uma matriz de adjacência a partir de uma matriz de rótulos de uma fórmula de satisfabilidade
int** rotulosEmMatriz(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int* n);

#endif