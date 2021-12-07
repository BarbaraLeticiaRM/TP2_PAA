#include "algoritmos.h"
#include <string.h>

int main(int argc, char* argv[]){
    srand(time(NULL)); // seed aleatória

    Analise a;
    int n, nLinhasRotulos, nColunasRotulos, flagClique = 0, flagSatisfabilidade = 0;
    int* solucao;
    int** matriz;
    int** rotulos;
    double media;
    double tempos[3]; // Vetor para armazenar o tempo

    // Processando qual problema deve ser executado
    if(!strcmp(argv[1], "1") || !strcmp(argv[1], "ci")){
        printf("> Problema 1: Conjunto Independente\n");
    }
    else if(!strcmp(argv[1], "2") || !strcmp(argv[1], "clique")){
        printf("> Problema 2: Clique\n");
        flagClique = 1;
    }
    else if(!strcmp(argv[1], "3") || !strcmp(argv[1], "satisfabilidade")){
        printf("> Problema 3: Satisfabilidade\n");
        flagSatisfabilidade = 1;
    }
    else{
        printf("ERRO: O problema nao foi selecionado corretamente!\n");
        return 0;
    }

    for(int instancia = 0; instancia < 3; instancia++){
        iniciarTempo(&a);
        
        if(flagSatisfabilidade == 0){
            if(instancia == 0)
                matriz = leGrafo("grafo1.txt", &n);
            else if(instancia == 1)
                matriz = leGrafo("grafo2.txt", &n);
            else
                matriz = leGrafo("grafo3.txt", &n);
        }
        else{
            if(instancia == 0)
                rotulos = leFormula("formula1.txt", &nLinhasRotulos, &nColunasRotulos);
            else if(instancia == 1)
                rotulos = leFormula("formula2.txt", &nLinhasRotulos, &nColunasRotulos);
            else
                rotulos = leFormula("formula3.txt", &nLinhasRotulos, &nColunasRotulos);
            
            matriz = rotulosEmMatriz(rotulos, nLinhasRotulos, nColunasRotulos, &n);
        }
        
        // Tratando o problema do Clique
        if(flagClique)
            entradaClique(matriz, n);

        solucao = bbConjuntoIndependente(matriz, n);
        printf("solucao:\n");

        if(flagSatisfabilidade == 0){
            imprimeVetor(solucao, n);
            printf("\n");
        }
        else{
            saidaSatisfabilidade(rotulos, solucao, nLinhasRotulos, nColunasRotulos, n);
        }

        finalizarTempo(&a);
        tempos[instancia] = (getDeltaTempo(&a));

        // Desalocando a memória alocada dinamicamente
        free(solucao);
        for(int i = 0; i < n; i++)
            free(matriz[i]);
        free(matriz);
        if(flagSatisfabilidade){
            for(int i = 0; i < nLinhasRotulos; i++)
                free(rotulos[i]);
            free(rotulos);
        }
    }

    // Imprimindo o tempo gasto das instâncias e a média do tempo
    media = calculaMedia(tempos, 3);

    for(int instancia = 0; instancia < 3; instancia++){
        printf("Tempo gasto na instancia %d: %.4lf segundos\n", instancia+1, tempos[instancia]);
    }
    printf("Media do tempo: %.4lf segundos\n", media);

    return 0;
}