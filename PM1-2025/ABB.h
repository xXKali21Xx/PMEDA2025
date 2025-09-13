#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "LSO.h"
typedef struct{
    Alumno dato; //dato del alumno
    struct nodo *Derecha; //apunta al nodo derecho
    struct nodo *izquierda; //apunta al nodo izquierdo
}nodo;

typedef struct{
    nodo *raiz; //nodo raiz
    nodo *aux; //nodo auxiliar
    nodo *cursor; //cursor del nodo
    int cant; //cantidad de elementos en el arbol
}arbol;

void init(arbol *a){ //inicializa el arbol
    a->raiz = NULL;
    a->cursor = NULL;
    a->aux = NULL;
    a->cant = 0;
}

nodo* nuevonodoABB(Alumno x){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(n == NULL){
        return n; //caso de que no tenga memoria sale
    }
    n->dato = x;
    n->Derecha = NULL;
    n->izquierda= NULL;
    return n; //caso que tenga memoria crea un nodo con izq y derecha nulos
}

arbol nuevoarbol(){
    arbol a;
    a.raiz = NULL;
    a.aux = NULL;
    a.cant = 0;
    a.cursor = NULL;
    return a;
}
void localizarABB(arbol *a, char cod[], int *exito, float *costo) {

    if (a == NULL || a->raiz == NULL) {
        *exito = 0;
        return;
    }

    a->cursor = a->raiz;
    a->aux = NULL;

    while (a->cursor != NULL) {
        *costo = *costo + 1;

        int comparacion = strcmp(a->cursor->dato.codigo, cod);

        if (comparacion == 0) {
            *exito = 1;
            return;
        }

        a->aux = a->cursor;

        if (comparacion > 0) {
            a->cursor = a->cursor->izquierda;
        } else {
            a->cursor = a->cursor->Derecha;
        }
    }

    *exito = 0;
}
#endif // ABB_H_INCLUDED
