#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED
#include "LSO.h"
#include <stdlib.h>

typedef struct
{
    Alumno *alumnoslibt[130];
    int ultimo;
} LIBT;

void localizarLIBT(LIBT *lista, char codigo[], int *exito, float *costo, int cant, int *pos) {
    if (cant == 0) {
        *exito = 0;
        *pos = 0;
        return;
    }

    int li = 0, ls = cant - 1;
    int m1, m2;

    while (li <= ls) {
        int tercio = (ls - li + 1) / 3;
        m1 = li + tercio;
        m2 = ls - tercio;

        *costo += 1;
        int comp1 = strcmpi(codigo, lista->alumnoslibt[m1]->codigo);

        if (comp1 == 0) {
            *pos = m1;
            *exito = 1;
            return;
        }

        if (comp1 < 0) {
            ls = m1 - 1;
        } else {
            // Solo consultar m2 si es necesario y válido
            if (m2 > m1) {
                *costo += 1;
                int comp2 = strcmpi(codigo, lista->alumnoslibt[m2]->codigo);
                if (comp2 == 0) {
                    *pos = m2;
                    *exito = 1;
                    return;
                }
                if (comp2 < 0) {
                    li = m1 + 1;
                    ls = m2 - 1;
                } else {
                    li = m2 + 1;
                }
            } else {
                 li = m1 + 1;
            }
        }
    }

    *exito = 0;
    *pos = li;
}

int AltaLI(LIBT *lista, Alumno x, int *cant, int *exito, float *costo){
    int pos = 0;
    int i = 0;
    float costoLocal = 0.0;

    if(*cant >= 130){
        *exito = -1; // No hay espacio
        return -1;
    }

    localizarLIBT(lista, x.codigo, exito, &costoLocal, *cant, &pos);
    *costo += costoLocal;

    if(*exito == 1){
        *exito = 0; // Elemento ya existe
        return 0;
    } else {
        Alumno *nuevo = (Alumno*) malloc(sizeof(Alumno));
        if(nuevo == NULL){
            *exito = -1;
            return -1;
        }
        *nuevo = x;

        // Corrimiento de punteros
        for(i = (*cant); i > pos; i--){
            lista->alumnoslibt[i] = lista->alumnoslibt[i-1];
            // CORREGIDO: costo por corrimiento de puntero es 0.5
            (*costo) += 0.5;
        }

        lista->alumnoslibt[pos] = nuevo;
        lista->ultimo = *cant;
        (*exito) = 1;
        (*cant)++;
        return 1;
    }
}

int BajaLI(LIBT *lista, Alumno x, int *cant, int *exito, float *costo){
    int pos;
    int i;
    float costoLocal = 0.0;

    localizarLIBT(lista, x.codigo, exito, &costoLocal, *cant, &pos);
    *costo += costoLocal;

    if(*exito == 0){
        *exito = 2; // Elemento no encontrado
        return 2;
    } else {
        // Confirmación por código comparando toda la tupla
        if(strcmpi(lista->alumnoslibt[pos]->nombre, x.nombre) == 0 &&
           strcmpi(lista->alumnoslibt[pos]->mail, x.mail) == 0 &&
           strcmpi(lista->alumnoslibt[pos]->condicion, x.condicion) == 0 &&
           lista->alumnoslibt[pos]->nota == x.nota){

            free(lista->alumnoslibt[pos]);

            // Corrimiento de punteros
            for(i = pos; i < (*cant)-1; i++){
                lista->alumnoslibt[i] = lista->alumnoslibt[i+1];
                (*costo) += 0.5;
            }

            (*exito) = 1;
            (*cant)--;
            lista->ultimo = (*cant) - 1;
            return 1;
        } else {
            *exito = 3; // Los datos no coinciden
            return 3;
        }
    }
    return -1;
}

Alumno* evocar(LIBT *lista, char cod[], int *exito, float *costo, int cant){
    int pos;
    float costoLocal = 0.0;
    localizarLIBT(lista, cod, exito, &costoLocal, cant, &pos);
    *costo += costoLocal;

    if (*exito == 1) {
        return lista->alumnoslibt[pos];
    } else {
        return NULL;
    }
}

void muestralibt(LIBT *lista, int cant){
    int i = 0;
    printf("----- LISTA DE ALUMNOS LIBT ----- \n");
    if(cant == 0) printf("La lista está vacía.\n");
    while(i < cant){
        printf("  Alumno %d:\n", i + 1);
        printf("  Nombre y Apellido: %s \n", lista->alumnoslibt[i]->nombre);
        printf("  Mail: %s \n", lista->alumnoslibt[i]->mail);
        printf("  Codigo Alumno: %s \n", lista->alumnoslibt[i]->codigo);
        printf("  Condicion: %s \n", lista->alumnoslibt[i]->condicion);
        printf("  Nota: %d \n", lista->alumnoslibt[i]->nota);
        printf("---------------------------------\n");
        i++;

        if(i % 5 == 0 && i < cant){
            printf("Presione Enter para continuar...");
            getchar();
        }
    }
}

#endif // LIBT_H_INCLUDED
