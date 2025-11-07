#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "LSO.h"
#define maxRAL 174

int hashing(char* x, int M){
    int longitud, i;
    int contador = 0;
    longitud = strlen(x);
    for(i = 0; i < longitud; i++){
        contador += ((int)x[i]) * (i+1);
    }
    return (contador % M);
}

typedef struct{
    int estado; // 1 virgen, 2 libre, 3 ocupada
    Alumno alumno;
}Celda;

typedef struct{
    Celda arreglo[maxRAL];
    int cantidad;
}rebalse;

void iniRAL(rebalse *ral){
    int i = 0;
    (*ral).cantidad = 0;
    while(i < maxRAL){
        (*ral).arreglo[i].estado = 1;
        i++;
    }
}

int localizarRAL(char* codigo, rebalse ral, int *exito, float *costo, int *pos) {
    int i = hashing(codigo, maxRAL);
    int j = 0;
    int primeraLibre = -1;

    *exito = 0;
    *costo = 0;
    while(j < maxRAL){
        *costo = *costo + 1;
        i = (i + 1) % maxRAL;
        if(ral.arreglo[i].estado == 3 && strcmpi(ral.arreglo[i].alumno.codigo, codigo) == 0){
            *exito = 1;
            *pos = i;
            return 1;
        }

        if(ral.arreglo[i].estado == 2 && primeraLibre == -1){
            primeraLibre = i;
        }

        if(ral.arreglo[i].estado == 1){
            if (primeraLibre != -1) {
                *pos = primeraLibre;
            } else {
                *pos = i;
            }
            return 0;
        }


        j++;
    }

    if(primeraLibre != -1){
        *pos = primeraLibre;
    }
    return 0;
}

int AltaRAL(rebalse *ral, Alumno alu, float *costo, int *exito){
    int pos = 0;
    *costo = 0;

    if((*ral).cantidad >= maxRAL){
        *exito = 0;
        return 2; // Estructura llena
    }

    localizarRAL(alu.codigo, *ral, exito, costo, &pos);

    if(*exito == 1){
        *exito = 0; // Ya existe
        return 0;
    }

    // Insertar el elemento
    (*ral).arreglo[pos].alumno = alu;
    (*ral).arreglo[pos].estado = 3;
    (*ral).cantidad++;
    *exito = 1;
    return 1;
}

void muestraRAL(rebalse ral){
    int i = 0;
    while(i < maxRAL){
        if(ral.arreglo[i].estado == 3){
            printf("  Posicion [%d] - OCUPADA\n", i);
            printf("  Nombre: %s\n", ral.arreglo[i].alumno.nombre);
            printf("  Mail: %s\n", ral.arreglo[i].alumno.mail);
            printf("  Codigo: %s\n", ral.arreglo[i].alumno.codigo);
            printf("  Condicion: %s\n", ral.arreglo[i].alumno.condicion);
            printf("  Nota: %d\n", ral.arreglo[i].alumno.nota);
            printf("-----------------------\n");
        } else if(ral.arreglo[i].estado == 1){
            printf("  Posicion [%d] - VIRGEN\n", i);
        } else if(ral.arreglo[i].estado == 2){
            printf("  Posicion [%d] - LIBRE\n", i);
        }
        i++;
        if(i % 10 == 0 && i < maxRAL){
            printf("\nPresione Enter para continuar...\n");
            getchar();
        }
    }
}

int comparacion(rebalse ral, Alumno alu, int pos){
    if(strcmpi(ral.arreglo[pos].alumno.codigo, alu.codigo) != 0){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.condicion, alu.condicion) != 0){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.mail, alu.mail) != 0){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.nombre, alu.nombre) != 0){
        return 0;
    }
    if(ral.arreglo[pos].alumno.nota != alu.nota){
        return 0;
    }
    return 1;
}

int BajaRAL(rebalse *ral, Alumno x, int *exito){
    int pos = 0;
    float costo = 0;

    if((*ral).cantidad == 0){
        *exito = 0;
        return 2; // Estructura vacía
    }

    localizarRAL(x.codigo, *ral, exito, &costo, &pos);

    if(*exito == 1 && comparacion(*ral, x, pos)){
        (*ral).arreglo[pos].estado = 2; // Libre
        (*ral).cantidad--;
        *exito = 1;
        return 1;
    }

    *exito = 0;
    return 0;
}

int EvocarRAL(rebalse ral, char codigo[], Alumno *aux, int *exito, float *costo){
    int pos;
    *costo = 0;

    localizarRAL(codigo, ral, exito, costo, &pos);

    if(*exito == 1){
        *aux = ral.arreglo[pos].alumno;
        return pos;
    }

    return 0;
}

#endif // RAL_H_INCLUDED
