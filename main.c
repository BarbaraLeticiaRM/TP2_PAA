#include "algoritmos.h"

int main(){
    srand(time(NULL)); // seed aleatória

    Analise a;
    int n;
    int* solucao;
    int** matriz;
    double media;
    double tempos[3]; // Vetor para armazenar o tempo 

    // Conjunto Independente
    printf("> Problema 1: Conjunto Independente\n");
    for(int instancia = 0; instancia < 3; instancia++){
        iniciarTempo(&a);
        
        if(instancia == 0)
            matriz = leGrafo("grafo1.txt", &n);
        else if(instancia == 1)
            matriz = leGrafo("grafo2.txt", &n);
        else
            matriz = leGrafo("grafo3.txt", &n);

        solucao = bbConjuntoIndependente(matriz, n);
        printf("solucao:\n");
        imprimeVetor(solucao, n);
        printf("\n");

        finalizarTempo(&a);
        tempos[instancia] = (getDeltaTempo(&a));

        // Desalocando a memória alocada dinamicamente
        free(solucao);
        for(int i = 0; i < n; i++)
            free(matriz[i]);
        free(matriz);
    }

    // Imprimindo o tempo gasto das instâncias e a média do tempo
    media = calculaMedia(tempos, 3);

    for(int instancia = 0; instancia < 3; instancia++){
        printf("Tempo gasto na instancia %d: %.4lf segundos\n", instancia+1, tempos[instancia]);
    }
    printf("Media do tempo: %.4lf segundos\n", media);

    // Clique
    printf("> Problema 2: Clique\n");
    for(int instancia = 0; instancia < 3; instancia++){
        iniciarTempo(&a);
        
        if(instancia == 0)
            matriz = leGrafo("grafo1.txt", &n);
        else if(instancia == 1)
            matriz = leGrafo("grafo2.txt", &n);
        else
            matriz = leGrafo("grafo3.txt", &n);

        entradaClique(matriz, n);
        solucao = bbConjuntoIndependente(matriz, n);
        printf("solucao:\n");
        imprimeVetor(solucao, n);
        printf("\n");

        finalizarTempo(&a);
        tempos[instancia] = (getDeltaTempo(&a));

        // Desalocando a memória alocada dinamicamente
        free(solucao);
        for(int i = 0; i < n; i++)
            free(matriz[i]);
        free(matriz);
    }

    // Imprimindo o tempo gasto das instâncias e a média do tempo
    media = calculaMedia(tempos, 3);

    for(int instancia = 0; instancia < 3; instancia++){
        printf("Tempo gasto na instancia %d: %.4lf segundos\n", instancia+1, tempos[instancia]);
    }
    printf("Media do tempo: %.4lf segundos\n", media);

    return 0;
}