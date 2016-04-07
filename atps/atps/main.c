//
//  main.c
//  atps
//
//  Created by Caio Henrique Silva on 07/04/16.
//  Copyright © 2016 Caio Henrique Silva. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct Residencia

{
    char rua[25];
    int numCasa;
    int numMedidor;
    float medidaConsumo;
} vetResidencias[1000];

int randomInteger (int low, int high)
{
    int k;
    double d;
    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}

int buscaMedidaLinear(int medida)
{
    for (int i = 0; i < sizeof(vetResidencias); i++) {
        if (vetResidencias[i].medidaConsumo == medida) {
            return 1;
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[])
{
    int vetorMedidas[1000];
    for (int i = 0; i < 1000; i++) {
        vetorMedidas[i] = randomInteger(1, 99999);
        vetResidencias[i].medidaConsumo = vetorMedidas[i];
    }
    
    return 0;
}
