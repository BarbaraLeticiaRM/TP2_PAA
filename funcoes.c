#include "funcoes.h"

// Função faz com que os elementos de "v" se tornem os elementos de "v2", ambos vetores de inteiros de tamanho n
void igualaVetor(int* v, int* v2, int n){
    for(int i = 0; i < n; i++){
        v[i] = v2[i];
    }
}

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

// Lê uma fórmula de satisfabilidade armazenada em um arquivo texto, onde o número de cláusulas é seguido
// pelas cláusulas em si
int** leFormula(char* nomeArquivo, int* nLinhasRotulos, int* nColunasRotulos){
    FILE* f = fopen(nomeArquivo, "r");

    int nLiteraisPorLinha, nLinhas = 0, aux;
    fscanf(f, "%d\n", &nLiteraisPorLinha);

    // Quantidade de literais presentes no arquivo
    while(!feof(f)){
        for(int i = 0; i < nLiteraisPorLinha; i++){
            fscanf(f, "%d ", &aux);
        }
        fscanf(f, "\n");
        nLinhas++;
    }

    *nLinhasRotulos = nLinhas;
    *nColunasRotulos = nLiteraisPorLinha;

    int** rotulos = (int **) malloc(*nLinhasRotulos * sizeof(int*));
    for(int i = 0; i < *nLinhasRotulos; i++){
        rotulos[i] = (int *) malloc(*nColunasRotulos * sizeof(int));
    }

    // Lendo a fórmula
    fseek(f, 0, SEEK_SET);
    fscanf(f, "%d\n", &aux);

    int i = 0, j = 0;
    while(!feof(f)){
        for(int k = 0; k < nLiteraisPorLinha; k++){
            fscanf(f, "%d ", &rotulos[i][j]);
            j++;
        }
        fscanf(f, "\n");
        i++;
        j = 0;
    }

    fclose(f);

    return rotulos;
}

// Retorna a linha da matriz de adjacência referente à posição de um literal no rótulo
int mapeiaPosicaoLiteral(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int posicaoLinha, int colunaLinha){
    int cont = -1, flag = 0;
    
    for(int i = 0; i < nLinhasRotulos; i++){
        if(flag == 1){
            break;
        }

        for(int j = 0; j < nColunasRotulos; j++){
            if(rotulos[i][j] != -1){
                cont++;
            }
            if(i == posicaoLinha && j == colunaLinha){
                flag = 1;
                break;
            }
        }
    }

    return cont;
}

// l e c conterão, respectivamente, a linha e a coluna da posição de um literal nos rótulos referente à
// uma posição do vetor de solução
void mapeiaSolucao(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int posicaoSolucao, int* l, int* c){
    int aux = -1, flag = 0;

    for(int i = 0; i < nLinhasRotulos; i++){
        if(flag == 1)
            break;

        for(int j = 0; j < nColunasRotulos; j++){
            if(rotulos[i][j] != -1){
                aux++;
            }

            if(aux == posicaoSolucao){
                *l = i;
                *c = j;
                flag = 1;
                break;
            }
        }
    }
}

// Gera uma matriz de adjacência a partir de uma matriz de rótulos de uma fórmula de satisfabilidade
int** rotulosEmMatriz(int** rotulos, int nLinhasRotulos, int nColunasRotulos, int* n){
    int aux = 0;

    for(int i = 0; i < nLinhasRotulos; i++){
        for(int j = 0; j < nColunasRotulos; j++){
            if(rotulos[i][j] != -1){
                aux++;
            }
        }
    }

    *n = aux;

    int** matriz = (int **) malloc(*n * sizeof(int*));
    for(int i = 0; i < *n; i++){
        matriz[i] = (int *) malloc(*n * sizeof(int));
    }

    // Gerando o grafo: inicializando todos os valores com 0
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            matriz[i][j] = 0;
        }
    }

    // Gerando o grafo: formando as arestas por cláusula
    int auxL, auxC;

    for(int i = 0; i < nLinhasRotulos; i++){
        for(int j = 0; j < nColunasRotulos; j++){
            if(rotulos[i][j] != -1){
                for(int k = 0; k < nColunasRotulos; k++){
                    if(rotulos[i][k] != -1 && j != k){
                        auxL = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, i, j);
                        auxC = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, i, k);
                        matriz[auxL][auxC] = 1;
                    }
                }
            }
        }
    }

    // Gerando o grafo: foramando as arestas entre literais e suas negações
    for(int j = 0; j < nColunasRotulos; j++){
        for(int i = 0; i < nLinhasRotulos; i++){

            // Se o literal estiver negado
            if(rotulos[i][j] == 0){
                for(int k = 0; k < nLinhasRotulos; k++){
                    if(rotulos[k][j] == 1 && i != k){
                        auxL = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, i, j);
                        auxC = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, k, j);
                        matriz[auxL][auxC] = 1;
                    }
                }
            }

            // Se o literal não estiver negado
            else if(rotulos[i][j] == 1){
                for(int k = 0; k < nLinhasRotulos; k++){
                    if(rotulos[k][j] == 0 && i != k){
                        auxL = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, i, j);
                        auxC = mapeiaPosicaoLiteral(rotulos, nLinhasRotulos, nColunasRotulos, k, j);
                        matriz[auxL][auxC] = 1;
                    }
                }
            }

        }
    }

    return matriz;
}
