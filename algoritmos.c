#include "algoritmos.h"

// Encontra o maior número de vértices independentes de um grafo por meio de Branch and Bound
int* bbConjuntoIndependente(int** mat, int n){
    // Criando e inicializando os vetores de solucoes
    int* solucao = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        solucao[i] = -2;
    }

    int* melhor = malloc(n * sizeof(int));
    melhor = bbPrimeiraSolucao(mat, n);

    bbOtimizacao(mat, solucao, melhor, n, 0);

    free(solucao);

    return melhor;
}

// Verifica se a solução é completa ou não, retornando 1 ou 0, respectivamente
int bbEhCompleta(int* v, int n){
    for(int i = 0; i < n; i++){
        if(v[i] == -2)
            return 0;
    }
    return 1;
}

// Verifica se a solução é consistente ou não, retornando 1 ou 0, respectivamente
int bbEhConsistente(int** mat, int* v, int n){
    for(int i = 0; i < n; i++){ // Percorrendo o vetor de soluções
        if(v[i] == 1){
            for(int j = 0; j < n; j++){ // Percorrendo o vetor de soluções novamente
                if(i != j && v[j] == 1 && mat[i][j] == 1){
                    return 0;
                }
            }
        }
    }

    return 1;
}

// Retorna a primeira solução consistente e completa para o Branch and Bound
int* bbPrimeiraSolucao(int** mat, int n){
    int* solucao = malloc(n * sizeof(int));
    solucao[0] = 1;

    for(int i = 1; i < n; i++){
        solucao[i] = 1;
        if(!bbEhConsistente(mat, solucao, n)){
            solucao[i] = 0;
        }
    }

    return solucao;
}

// Verifica se a solução é promissora ou não, retornando 1 ou 0, respectivamente
int bbEhPromissora(int* solucao, int* melhor, int n){
    int contSolucao = 0, contMelhor = 0;

    for(int i = 0; i < n; i ++){
        if(solucao[i] == 1 || solucao[i] == -2)
            contSolucao++;
        if(melhor[i] == 1)
            contMelhor++;
    }

    return (contSolucao > contMelhor);
}

// Realiza o Branch and Bound para Otimização
void bbOtimizacao(int** mat, int* solucao, int* melhor, int n, int i){
    int j;

    if(bbEhCompleta(solucao, n)){
        igualaVetor(melhor, solucao, n);
    }
    else{
        j = 0;
        while(j <= 1){
            solucao[i] = j;

            if(bbEhConsistente(mat, solucao, n) && bbEhPromissora(solucao, melhor, n)){
                bbOtimizacao(mat, solucao, melhor, n, i+1);
            }
            solucao[i] = -2;
            j++;
        }
    }
}
