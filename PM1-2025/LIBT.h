#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED
#include "LSO.h"
typedef struct
{
    Alumno *alumnoslibt[130];
    int ultimo;
} LIBT;

int localizarLSOBT(int exito, char codigo[], LIBT lista, float *costo, int cant){
    int li = 0, ls = cant;//limite inferior y superior inclusivo
    int t; //testigo
    (*costo) = 0.0;
    while(li < ls){
        t = (li + (ls + 1)) / 2;
        if(strcmp(lista.alumnoslibt[t]->codigo, codigo) <= 0){//compara el codigo con el testigo
            li = t;
            (*costo) += 1;
        }else{
            ls = t - 1;
            (*costo) += 1;
        }
    }

}


#endif // LIBT_H_INCLUDED
