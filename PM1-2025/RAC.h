#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define maxRAC 163
#include <ctype.h>
#include "RAL.h"
#include "LSO.h"

void iniRAC(rebalse *rac) {
    rac->cantidad = 0;
    for (int i = 0; i < maxRAC; i++) {
        rac->arreglo[i].estado = 1;
    }
}

int localizarRAC(char* codigo, rebalse rac, int *pos, float *costo, int *exito) {
    for(int z = 0; codigo[z] != '\0'; z++){
        codigo[z] = toupper(codigo[z]);
    }
    int i = hashing(codigo, maxRAC);
    int j = 0;
    int primeraLibre = -1;

    *exito = 0;
    *costo = 0;

    for (int k = 0; k < maxRAC; k++) {

        if (k > 0) {
            j++;
            i = (i + j) % maxRAC;
        }

        *costo = *costo + 1;

        if (rac.arreglo[i].estado == 3) {
            if (strcmp(rac.arreglo[i].alumno.codigo, codigo) == 0) {
                *exito = 1;
                *pos = i;
                return 1;
            }
        }

        if (rac.arreglo[i].estado == 2 && primeraLibre == -1) {
                primeraLibre = i;
        }

        if (rac.arreglo[i].estado == 1) {
            if (primeraLibre != -1) {
                *pos = primeraLibre;
            } else {
                *pos = i;
            }
            return 0;
        }
    }

    if (primeraLibre != -1) {
        *pos = primeraLibre;
    } else {
        *pos = -1;
    }
    return 0;
}

int AltaRAC(rebalse *rac, Alumno alu, int *exito) {
    int pos;
    float costo;

    if (rac->cantidad >= maxRAC) return 2;

    localizarRAC(alu.codigo, *rac, &pos, &costo, exito);

    if (*exito == 1) {
        *exito = 0;
        return 0;
    }

    rac->arreglo[pos].alumno = alu;
    rac->arreglo[pos].estado = 3;
    rac->cantidad++;
    *exito = 1;
    return 1;
}

int comparacionAlumno(Alumno a, Alumno b) {
    return strcmpi(a.codigo, b.codigo) == 0 &&
           strcmpi(a.nombre, b.nombre) == 0 &&
           strcmpi(a.mail, b.mail) == 0 &&
           strcmpi(a.condicion, b.condicion) == 0 &&
           a.nota == b.nota;
}

int BajaRAC(rebalse *rac, Alumno x, int *exito) {
    int pos;
    float costo;

    if (rac->cantidad == 0) {
        *exito = 0;
        return 2;
    }

    localizarRAC(x.codigo, *rac, &pos, &costo, exito);

    if (*exito == 1 && comparacionAlumno(rac->arreglo[pos].alumno, x)) {
        rac->arreglo[pos].estado = 2;
        rac->cantidad--;
        *exito = 1;
        return 1;
    }

    *exito = 0;
    return 0;
}


int EvocarRAC(rebalse rac, char codigo[], Alumno *aux, int *exito, float *costo) {
    int pos;
    *costo = 0;

    localizarRAC(codigo, rac, &pos, costo, exito);

    if (*exito == 1) {
        *aux = rac.arreglo[pos].alumno;
        return pos;
    }
    return -1;
}

void muestraRAC(rebalse rac) {
    for (int i = 0; i < maxRAC; i++) {
        if (rac.arreglo[i].estado == 3) {
            Alumno a = rac.arreglo[i].alumno;
            printf("  Pos [%d] - OCUPADA\n", i);
            printf("  Nombre: %s\n", a.nombre);
            printf("  Mail: %s\n", a.mail);
            printf("  Codigo: %s\n", a.codigo);
            printf("  Condicion: %s\n", a.condicion);
            printf("  Nota: %d\n", a.nota);
            printf("-----------------------------\n");
        } else if (rac.arreglo[i].estado == 1) {
            printf("  Pos [%d] - VIRGEN\n", i);
        } else if (rac.arreglo[i].estado == 2) {
            printf("  Pos [%d] - LIBRE\n", i);
        }

        if ((i + 1) % 5 == 0 && i + 1 < maxRAC) {
            system("PAUSE");
        }
    }
}

#endif // RAC_H_INCLUDED
