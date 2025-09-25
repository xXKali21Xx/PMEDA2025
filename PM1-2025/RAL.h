#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "LSO.h"
#define maxRAL 150 //sacar bien la cuenta


int hashing(char* x, int M){
    int longitud, i;
    int contador = 0;
    longitud = strlen(x);
    for(i = 0;  i<longitud; i++){
        contador +=((int)x[i] * (i+1));
    }
    return (contador % M);
}
//usamos la misma estructura para RAC
typedef struct{
    int estado; //1 virgen, 2 libre, 3 ocupada
    Alumno alumno;
}Celda;

typedef struct{
    Celda  arreglo[maxRAL];
    int cantidad;
}rebalse;

void iniRAL(rebalse *ral){ //inicializar el rebalse
    int i = 0;
    (*ral).cantidad = 0;
    while(i < maxRAL){
        (*ral).arreglo[i].estado = 1;
        i++;
    }
}

#endif // RAL_H_INCLUDED
