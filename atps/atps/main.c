//
//  main.c
//  atps
//
//  Created by Caio Henrique Silva on 07/04/16.
//  Copyright © 2016 Caio Henrique Silva. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct Residencia {
    char rua[25];
    int numCasa;
    int numMedidor;
    float medidaConsumo;
};

struct Residencia vetResidencias[1000];

int randomInteger (int low, int high)
{
    int k;
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}


long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    return milliseconds;
}


int buscaMedidaLinear(int medida)
{
    long start = current_timestamp();
    for (int i = 0; i < 1000; i++) {
        if (vetResidencias[i].medidaConsumo == medida) {
            long end = current_timestamp();
            long time = end - start;
            printf("Esta consulta levou %ldms", time);
            return i;
        }
    }
    
    long end = current_timestamp();
    long time = end - start;
    printf("\n\nEsta consulta levou %ldms", time);
    
    return -1;
}

void bubbleSort() {
    int aux;

    for (int i = 0; i < 1000; i++) {
        if (vetResidencias[i].medidaConsumo > vetResidencias[i+1].medidaConsumo) {
            aux = vetResidencias[i+1].medidaConsumo;
            vetResidencias[i+1].medidaConsumo = vetResidencias[i].medidaConsumo;
            vetResidencias[i].medidaConsumo = aux
        }
    }
}

void insertionSort() {
    
}

void selectionSort() {

}

void mergeSort() {
    
}





int main(int argc, const char * argv[])
{
    int vetorMedidas[1000];
    for (int i = 0; i < 1000; i++) {
        vetorMedidas[i] = randomInteger(1, 99999);
        vetResidencias[i].medidaConsumo = vetorMedidas[i];
        vetResidencias[i].numCasa = i;
        printf("%d, ", vetorMedidas[i]);
    }
    
    int sair, valor;
    do {
        
        
        int escolha, escolhaOrd, sairOrd;
        printf("\n\n\nDigite a opcao desejada: \n1. Pesquisa\n2. Ordenacao\n3. Sair\n>> ");
        scanf("%d", &escolha);
        
        switch (escolha) {
            case 1:
                
                printf("Digite o valor de medida a ser pesquisado: ");
                scanf("%ud", &valor);
                
                int resultBuscaLinear = buscaMedidaLinear(valor);
                
                if (resultBuscaLinear > 0) {
                    printf("\n\nFoi encontrada a casa de numero %d com o valor %d de medida", resultBuscaLinear, valor);
                } else {
                    printf("\n\nNenhuma casa foi encontrada");
                }
                
                break;
            case 2:
                
                do {
                    printf("Digite o algoritmo de ordenação desejado: \n1. Bubble Sorte \n2. Insertion Sort \n3. Selection Sorte \n4. Merge Sort \n5. Sair\n>> ");
                    scanf("%d", &escolhaOrd);
                    
                    switch (escolhaOrd) {
                        case 1:
                            bubbleSort();
                            break;
                        case 2:
                            insertionSort();
                            break;
                        case 3:
                            selectionSort();
                            break;
                        case 4:
                            mergeSort();
                            break;
                        case 5:
                            return 0;
                            break;
                        default:
                            printf("Opcao incorreta, tente novamente! \n\n\n");
                            break;
                    }
                } while (sairOrd == 0);
                
                break;
            case 3:
                return 0;
                break;
            default:
                printf("Opcao incorreta, tente novamente! \n\n\n");
                break;
        }
        
        
        
    } while(sair == 0);
    
    return 0;
}
