#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "LSO.h"
#include <stdlib.h>

typedef struct nodo{
    Alumno dato;
    struct nodo *Derecha;
    struct nodo *izquierda;
}nodo;

typedef struct{
    nodo *raiz;
    int cant;
}arbol;

void init(arbol *a){
    a->raiz = NULL;
    a->cant = 0;
}

nodo* nuevonodoABB(Alumno x){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(n == NULL){
        return n;
    }
    n->dato = x;
    n->Derecha = NULL;
    n->izquierda= NULL;
    return n;
}

void localizarABB(arbol *a, char cod[], int *exito, float *costo, nodo **cursor, nodo **padre) {
    *padre = NULL;
    *cursor = a->raiz;
    *exito = 0;

    while (*cursor != NULL && !(*exito)) {
        (*costo)++;
        int comp = strcmpi(cod, (*cursor)->dato.codigo);
        if (comp == 0) {
            *exito = 1;
        } else {
            *padre = *cursor;
            if (comp < 0) {
                *cursor = (*cursor)->izquierda;
            } else {
                *cursor = (*cursor)->Derecha;
            }
        }
    }
}

int AltaABB(arbol *a, Alumno x, int *exito, float *costo, int *cant){
    nodo *cursor = NULL, *padre = NULL;
    float costoLocal = 0.0;
    localizarABB(a, x.codigo, exito, &costoLocal, &cursor, &padre);

    if(*exito == 1){
        *exito = 0; // Elemento ya existe
        return 0;
    } else {
        nodo* nuevo = nuevonodoABB(x);
        if(nuevo != NULL){
            *costo += 0.5;
            if(padre == NULL){
                a->raiz = nuevo;
            } else {
                int comp = strcmpi(x.codigo, padre->dato.codigo);
                if(comp > 0){
                    padre->Derecha = nuevo;
                } else {
                    padre->izquierda = nuevo;
                }
            }
            a->cant++;
            if (cant != NULL) *cant = a->cant;
            *exito = 1;
            return 1;
        } else {
            *exito = -1; // Sin memoria
            return -1;
        }
    }
}

int BajaABB(arbol *a, Alumno b, float *costo, int *exito){
    nodo *cursor = NULL, *padre = NULL;
    float costoLocal = 0.0;
    localizarABB(a, b.codigo, exito, &costoLocal, &cursor, &padre);

    if(!(*exito)){
        *exito = 0; // No encontrado
        return 0;
    }

    // Confirmación por código
    if(!(strcmpi(cursor->dato.nombre, b.nombre) == 0 &&
         strcmpi(cursor->dato.mail, b.mail) == 0 &&
         strcmpi(cursor->dato.condicion, b.condicion) == 0 &&
         cursor->dato.nota == b.nota)){
        *exito = 2; // Los datos no coinciden
        return 2;
    }

    // Caso 1: Hoja
    if(cursor->izquierda == NULL && cursor->Derecha == NULL){
        if(cursor == a->raiz) a->raiz = NULL;
        else if(padre->izquierda == cursor) padre->izquierda = NULL;
        else padre->Derecha = NULL;
        free(cursor);
        *costo += 0.5;
    }
    // Caso 2: Un solo hijo (izquierdo)
    else if(cursor->Derecha == NULL){
        if(cursor == a->raiz) a->raiz = cursor->izquierda;
        else if(padre->izquierda == cursor) padre->izquierda = cursor->izquierda;
        else padre->Derecha = cursor->izquierda;
        free(cursor);
        *costo += 0.5;
    }
    // Caso 3: Un solo hijo (derecho)
    else if(cursor->izquierda == NULL){
        if(cursor == a->raiz) a->raiz = cursor->Derecha;
        else if(padre->izquierda == cursor) padre->izquierda = cursor->Derecha;
        else padre->Derecha = cursor->Derecha;
        free(cursor);
        *costo += 0.5;
    }
    // Caso 4: Dos hijos
    else {
        nodo *sucesor = cursor->izquierda;
        nodo *padreSucesor = cursor;
        while(sucesor->Derecha != NULL){
            padreSucesor = sucesor;
            sucesor = sucesor->Derecha;
            *costo += 1.0;
        }
        cursor->dato = sucesor->dato;
        if(padreSucesor == cursor){
            padreSucesor->izquierda = sucesor->izquierda;
        } else {
            padreSucesor->Derecha = sucesor->izquierda;
        }
        free(sucesor);
        *costo += 0.5;
    }

    a->cant--;
    *exito = 1;
    return 1;
}

Alumno evocarABB(arbol *a, char cod[], int *exito, float *costo) {
    nodo *cursor, *padre;
    float costoLocal = 0.0;
    localizarABB(a, cod, exito, &costoLocal, &cursor, &padre);
    *costo += costoLocal;

    if (*exito) {
        return cursor->dato;
    }
    Alumno vacio = {0};
    return vacio;
}

int muestranodo(nodo *raiz, int *contador){
    if(raiz == NULL){
        return 0;
    }

    printf("-----------------------------------------\n");
    printf("  Nodo Codigo: %s (Nombre: %s)\n", raiz->dato.codigo, raiz->dato.nombre);
    printf("  Mail: %s\n", raiz->dato.mail);
    printf("  Condicion: %s, Nota: %d\n", raiz->dato.condicion, raiz->dato.nota);

    if (raiz->izquierda != NULL) {
        printf("  Hijo Izquierdo -> Codigo: %s\n", raiz->izquierda->dato.codigo);
    } else {
        printf("  Hijo Izquierdo -> NULL\n");
    }

    if (raiz->Derecha != NULL) {
        printf("  Hijo Derecho   -> Codigo: %s\n", raiz->Derecha->dato.codigo);
    } else {
        printf("  Hijo Derecho   -> NULL\n");
    }
    (*contador)++;
    if (*contador % 5 == 0) {
        printf("Presione Enter para continuar...");
        getchar();
    }
    muestranodo(raiz->izquierda, contador);
    muestranodo(raiz->Derecha, contador);
    return 1;
}

int muestraABB(arbol *a){
    if(a->raiz == NULL){
        printf("Error:El Arbol esta vacio\n");
        return 0;
    }
    printf("----- LISTA DE ALUMNOS ABB ----- \n");
    int contador = 0;
    muestranodo(a->raiz, &contador);
    return 1;
}

#endif // ABB_H_INCLUDED
