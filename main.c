#include "algoritmos.h"

int main(){
    srand(time(NULL)); // seed aleatória

    Analise a;
    int n;
    int* solucao;
    int** matriz;
    double media;
    double tempos[3]; // Vetor para armazenar o tempo 

    // 3 instâncias sendo geradas
    for(int instancia = 0; instancia < 1; instancia++){ /////////////ESTÁ RODANDO SÓ UMA VEZ
        iniciarTempo(&a);
        
        matriz = leGrafo("grafo4.txt", &n);
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