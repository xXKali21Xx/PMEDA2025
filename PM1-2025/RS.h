#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "LSO.h"
#include "RAL.h"
#define maxRS 85
typedef struct{
    Alumno elem;
    struct NodoRS *sig;
}NodoRS;

typedef struct{
    NodoRS *acc;
    NodoRS *cursor;
    NodoRS *aux;
    int cant;
}RS;

void initRS(RS *rs){
	int i;
	for(i = 0; i < maxRS; i++){
		rs[i].acc = NULL;
		rs[i].aux = NULL;
        rs[i].cursor = NULL;
        rs[i].cant = 0;
	}
}
int localizarRS(RS rs[], char codigo[], int *exito, float *costo, NodoRS **pos) {
    int i = hashing(codigo, maxRS);
    NodoRS *actual = rs[i].acc;
    *exito = 0;
    *costo = 1;
    while (actual != NULL) {
        *costo = *costo + 1;
        if (strcmpi(actual->elem.codigo, codigo) == 0) {
            *exito = 1;
            *pos = actual;
            return 1;
        }
        actual = actual->sig;
    }
    *pos = NULL;
    return 0;
}

int AltaRS(RS rs[], Alumno alu, int *exito, float *costo) {
    int i = hashing(alu.codigo, maxRS);
    NodoRS *pos = NULL;

    localizarRS(rs, alu.codigo, exito, costo, &pos);
    if (*exito == 1) {
        *exito = 0;
        return 0;
    }

    NodoRS *nuevo = (NodoRS *)malloc(sizeof(NodoRS));
    if (nuevo == NULL) {
        *exito = 0;
        return 2;
    }

    nuevo->elem = alu;
    nuevo->sig = rs[i].acc;
    rs[i].acc = nuevo;
    rs[i].cant++;

    *exito = 1;
    return 1;
}

void muestraRS(RS rs[]) {
    int i;
    for (i = 0; i < maxRS; i++) {
        printf("  Balde [%d]: ", i);
        if (rs[i].acc == NULL) {
            printf("Lista vacia.\n");
        } else {
            printf("(%d elementos)\n", rs[i].cant);
            NodoRS *actual = rs[i].acc;
            while (actual != NULL) {
                printf("     + Nombre: %s | Codigo: %s | Nota: %d\n", actual->elem.nombre, actual->elem.codigo, actual->elem.nota);
                actual = actual->sig;
            }
        }
        printf("----------------------------------------------------------\n");
        if ((i + 1) % 5 == 0) {
            printf("Presione Enter para continuar...\n");
            getchar();
        }
    }
}

int comparacionRS(Alumno a1, Alumno a2) {
    return (strcmpi(a1.codigo, a2.codigo) == 0 &&
            strcmpi(a1.nombre, a2.nombre) == 0 &&
            strcmpi(a1.mail, a2.mail) == 0 &&
            strcmpi(a1.condicion, a2.condicion) == 0 &&
            a1.nota == a2.nota);
}

int BajaRS(RS rs[], Alumno alu, int *exito) {
    int i = hashing(alu.codigo, maxRS);
    NodoRS *actual = rs[i].acc;
    NodoRS *anterior = NULL;
    *exito = 0;

    while (actual != NULL) {
        if (comparacionRS(actual->elem, alu)) {
            if (anterior == NULL) {
                rs[i].acc = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            free(actual);
            rs[i].cant--;
            *exito = 1;
            return 1;
        }
        anterior = actual;
        actual = actual->sig;
    }
    return 0;
}

int EvocarRS(RS rs[], char codigo[], Alumno *alu, int *exito, float *costo) {
    NodoRS *pos = NULL;
    localizarRS(rs, codigo, exito, costo, &pos);
    if (*exito == 1) {
        *alu = pos->elem;
        return 1;
    }
    return 0;
}
#endif // RS_H_INCLUDED
