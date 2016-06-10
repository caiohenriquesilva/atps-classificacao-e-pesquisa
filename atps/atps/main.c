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

    int i;
    for (i = 0; i < 1000; i++) {
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
    int aux, j, i;
    for (j = 999; j >= 1; j--) {
        for (i = 0; i < 1000; i++) {
            if (vetResidencias[i].medidaConsumo > vetResidencias[i+1].medidaConsumo) {
                aux = vetResidencias[i].medidaConsumo;
                vetResidencias[i].medidaConsumo = vetResidencias[i+1].medidaConsumo;
                vetResidencias[i+1].medidaConsumo = aux;
            }
        }
    }

    int m;
    for (m = 0; m < 1000; m++) {
        printf("%.0f, ", vetResidencias[m].medidaConsumo);
    }
}

void insertionSort() {
    int i, j, atual;

    for (i = 1; i < 1000; i++)
    {
        atual = vetResidencias[i].medidaConsumo;
        j = i - 1;

        while ((j >= 0) && (atual < vetResidencias[j].medidaConsumo))
        {
            vetResidencias[j + 1].medidaConsumo = vetResidencias[j].medidaConsumo;
            j = j - 1;
        }

        vetResidencias[j + 1].medidaConsumo = atual;
    }
}

void selectionSort() {
    int i, j, min, aux;
    for (i = 0; i < 999; i++)
    {
        min = i;
        for (j = (i+1); j < 1000; j++) {
            if(vetResidencias[j].medidaConsumo < vetResidencias[min].medidaConsumo)
                min = j;
        }
        if (i != min) {
            aux = vetResidencias[i].medidaConsumo;
            vetResidencias[i].medidaConsumo = vetResidencias[min].medidaConsumo;
            vetResidencias[min].medidaConsumo = aux;
        }
    }
}

void mergeSort(int * V, int inicio, int fim) {
    int i, j, k, metadeTamanho, *V_temp;

    if(inicio == fim) {
        return;
    }

    metadeTamanho = (inicio + fim ) / 2;
    mergeSort(V, inicio, metadeTamanho);
    mergeSort(V, metadeTamanho + 1, fim);

    i = inicio;
    j = metadeTamanho + 1;
    k = 0;
    V_temp = (int *) malloc(sizeof(int) * (fim - inicio + 1));

    while(i < metadeTamanho + 1 || j  < fim + 1) {
        if (i == metadeTamanho + 1 ) {
            V_temp[k] = V[j];
            j++;
            k++;
        }
        else {
            if (j == fim + 1) {
                V_temp[k] = V[i];
                i++;
                k++;
            }
            else {
                if (V[i] < V[j]) {
                    V_temp[k] = V[i];
                    i++;
                    k++;
                }
                else {
                    V_temp[k] = V[j];
                    j++;
                    k++;
                }
            }
        }
    }

    for(i = inicio; i <= fim; i++) {
        V[i] = V_temp[i - inicio];
    }

    free(V_temp);
}

void quickSort(int * V, int esq, int dir) {
	int pivo = esq,i,ch,j;

	for(i=esq+1;i<=dir;i++){
		j = i;
		if(V[j] < V[pivo]){
			ch = V[j];
			while(j > pivo){
				V[j] = V[j-1];
				j--;
			}

			V[j] = ch;
			pivo++;
		}
	}

	if(pivo-1 >= esq){
		quick(V,esq,pivo-1);
	}

	if(pivo+1 <= dir){
		quick(V,pivo+1,dir);
	}
}

void heapSort(int * V, int n) {
	int i = n / 2, pai, filho, t;
	for (;;) {
		if (i > 0) {
			i--;
			t = V[i];
		} else {
			n--;
			if (n == 0) return;
			t = V[n];
			V[n] = V[0];
		}

		pai = i;
		filho = i * 2 + 1;
		while (filho < n) {
			if ((filho + 1 < n)  &&  (V[filho + 1] > V[filho]))
				filho++;

			if (V[filho] > t) {
				V[pai] = V[filho];
				pai = filho;
				filho = pai * 2 + 1;
			} else {
				break;
			}
		}

		V[pai] = t;
	}
}



int main(int argc, const char * argv[])
{
    int vetorMedidas[1000], i;
    for (i = 0; i < 1000; i++) {
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
0, 
                do {
                    printf("Digite o algoritmo de ordenação desejado:");
                    printf("\n1. Bubble Sort");
                    printf("\n2. Insertion Sort");
                    printf("\n3. Selection Sort");
                    printf("\n4. Merge Sort");
                    printf("\n5. Quick Sort");
                    printf("\n6. Heap Sort");
                    printf("\n7. Sair\n");
                    printf("");
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
                            mergeSort(&vetResidencias, 0, 999);
                            break;
                        case 5:
                            quickSort(&vetResidencias, 0, 999);
                            break;
                        case 6:
                            heapSort(&vetResidencias, 999);
                            break;
                        case 7:
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
