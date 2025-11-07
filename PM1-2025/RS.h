#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#include "LSO.h"
#include "RAL.h"
#define maxRS 85
typedef struct NodoRS{
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
int localizarRS(RS rs[], char codigo[], int *exito, float *costo, int *pos) {
    int i = hashing(codigo, maxRS);
    *pos = i;
    *exito = 0;
    *costo = 1.0;
    rs[i].aux = NULL;
    rs[i].cursor = rs[i].acc;

    while (rs[i].cursor != NULL) {
        *costo = *costo + 1;
        if (strcmpi(rs[i].cursor->elem.codigo, codigo) == 0) {
            *exito = 1;
            return 1;
        }

        rs[i].aux = rs[i].cursor;
        rs[i].cursor = rs[i].cursor->sig;
    }
    *exito = 0;
    return 0;
}

int AltaRS(RS rs[], Alumno alu, int *exito, float *costo) {
    //int i = hashing(alu.codigo, maxRS);
    int pos;
    localizarRS(rs, alu.codigo, exito, costo, &pos);
    if (*exito == 1) {
        *exito = 0;
        return *exito;
    }

    NodoRS *nuevo = (NodoRS *)malloc(sizeof(NodoRS));
    if (nuevo == NULL) {
        *exito = 0;
        return 2;
    }

    nuevo->elem = alu;
    nuevo->sig = rs[pos].acc;
    rs[pos].acc = nuevo;
    rs[pos].cant++;

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
    float costo = 0.0;
    int pos;
    localizarRS(rs, alu.codigo, exito, &costo, &pos);

    if (*exito == 0) {
        return 0;
    }
    if (comparacionRS(rs[pos].cursor->elem, alu)) {
        NodoRS* nodo_a_borrar = rs[pos].cursor;
        if (rs[pos].aux == NULL) {
            rs[pos].acc = nodo_a_borrar->sig;
        } else {
            rs[pos].aux->sig = nodo_a_borrar->sig;
        }
        free(nodo_a_borrar);
        rs[pos].cant--;
        *exito = 1;
        return 1;
    }
    *exito = 0;
    return 0;
}

int EvocarRS(RS rs[], char codigo[], Alumno *alu, int *exito, float *costo) {
    int pos;
    localizarRS(rs, codigo, exito, costo, &pos);
    if (*exito == 1) {
        *alu = rs[pos].cursor->elem;
        return 1;
    }
    return 0;
}
#endif // RS_H_INCLUDED
