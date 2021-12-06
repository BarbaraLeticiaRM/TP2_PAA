#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "funcoes.h"

// Encontra o maior número de vértices independentes de um grafo por meio de Branch and Bound
int* bbConjuntoIndependente(int** mat, int n);

// Verifica se a solução é completa ou não, retornando 1 ou 0, respectivamente
int bbEhCompleta(int* v, int n);

// Verifica se a solução é consistente ou não, retornando 1 ou 0, respectivamente
int bbEhConsistente(int** mat, int* v, int n);

// Retorna a primeira solução consistente e completa para o Branch and Bound
int* bbPrimeiraSolucao(int** mat, int n);

// Verifica se a solução é promissora ou não, retornando 1 ou 0, respectivamente
int bbEhPromissora(int* solucao, int* melhor, int n);

// Realiza o Branch and Bound para Otimização
void bbOtimizacao(int** mat, int* solucao, int* melhor, int n, int i);

// Altera a matriz de adjacência recebida como parâmetro para a entrada do problema de Clique
void entradaClique(int** mat, int n);

#endif