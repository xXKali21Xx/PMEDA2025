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

void init(arbol a){ //inicializa el arbol
    a->raiz = null;
    a->cursor = null;
    a->aux = null;
    a->cant = 0;
}

nodo* nuevonodoABB(Alumno x){
    nodo* n = (nodo*)malloc(sieof(nodo));
    if(n == null){
        return n; //caso de que no tenga memoria sale
    }
    n->dato = x;
    n->Derecha = null;
    n->izquierda= null;
    return n; //caso que tenga memoria crea un nodo con izq y derecha nulos
}

arbol nuevoarbol(){
    arbol a;
    a->raiz = null;
    a->aux = null;
    a->cant = 0;
    a->cursor = null;
    return a;
}
#endif // ABB_H_INCLUDED
