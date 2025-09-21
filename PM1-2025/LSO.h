#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "string.h"
#include "stdio.h"

typedef struct{
    char nombre[80];
    char mail[24];
    char codigo[8];
    char condicion[11]; // CORREGIDO: de 10 a 11 para el char nulo '\0'
    int nota;
}Alumno;

//Localizar
int localizar(Alumno lista[], int *cant, char cod[], int *exito, int *pos, float *costo){
    int i = 0;
    *costo = 0.0;

    if(*cant == 0){
        *exito = 0; // Lista vacia
        *pos = 0;
        return *exito;
    }

    while((i < *cant) && (strcmpi(lista[i].codigo,cod) < 0)){
        (*costo) += 1.0;
        i++;
    }

    if (i < *cant) {
        (*costo) += 1.0;
        if(strcmpi(lista[i].codigo,cod) == 0){
            *exito = 1; // Encontrado
            *pos = i;
        } else {
            *exito = 0; // No encontrado
            *pos = i;
        }
    } else {
        *exito = 0; // No encontrado, insertar al final
        *pos = i;
    }
    return *exito;
}

int Alta(Alumno lista[], Alumno x, int *cant, int *exito, float *costo){
    int pos = 0;
    int i = 0;
    float costoLocal = 0.0;

    if(*cant >= 130){
        *exito = -1; // Lista llena
        return *exito;
    }

    localizar(lista, cant, x.codigo, exito, &pos, &costoLocal);
    *costo += costoLocal;

    if(*exito == 1){
        *exito = 0; // Elemento ya existe
    } else {
        // Calcular costo de corrimiento
        int shifts = (*cant) - pos;
        // CORREGIDO: Costo de corrimiento de tupla es 1
        *costo += shifts * 1.0;

        // Realizar corrimientos
        for(i = (*cant); i > pos; i--){
            lista[i] = lista[i-1];
        }
        lista[pos] = x;
        *exito = 1;
        (*cant)++;
    }
    return *exito;
}

//Baja
int Baja(Alumno lista[], Alumno x, int *cant, int *exito, float *costo){
    int pos;
    int i;
    float costoLocal = 0.0;

    if(*cant == 0){
        *exito = 0; // Lista vacía
        return *exito;
    }

    localizar(lista, cant, x.codigo, exito, &pos, &costoLocal);
    *costo += costoLocal;

    if(*exito == 0){
        *exito = 2; // No se encontró
    } else {
        // Confirmación por código comparando toda la tupla [cite: 73]
        if(strcmpi(lista[pos].nombre, x.nombre) == 0 &&
           strcmpi(lista[pos].mail, x.mail) == 0 &&
           strcmpi(lista[pos].condicion, x.condicion) == 0 &&
           lista[pos].nota == x.nota)
        {
            // El costo de corrimiento es 1 por tupla
            *costo += (*cant) - 1 - pos;

            for(i = pos; i < (*cant)-1; i++){
                lista[i] = lista[i+1];
            }
            (*exito) = 1; // Borrado exitoso
            (*cant)--;
        } else {
            *exito = 3; // Los datos no coinciden, no se borra
        }
    }
    return *exito;
}

//Evocar
Alumno* Evocar(Alumno lista[], int *cant, char cod[], int *exito, float *costo) {
    int pos = 0;
    float costoLocal = 0.0;
    localizar(lista, cant, cod, exito, &pos, &costoLocal);
    *costo += costoLocal;

    if (*exito == 1) {
        return &lista[pos];
    } else {
        return NULL;
    }
}

//Muestra
void muestralso(Alumno lista[], int cant){
    int i = 0;
    printf("----- LISTA DE ALUMNOS LSO ----- \n");
    if(cant == 0) printf("La lista está vacía.\n");
    while(i < cant){
        printf("Alumno %d:\n", i + 1);
        printf("  Nombre y Apellido: %s \n", lista[i].nombre );
        printf("  Mail: %s \n", lista[i].mail);
        printf("  Codigo Alumno: %s \n", lista[i].codigo);
        printf("  Condicion: %s \n", lista[i].condicion);
        printf("  Nota: %d \n", lista[i].nota);
        printf("---------------------------------\n");
        i++;
        if(i % 5 == 0 && i < cant){
            printf("Presione Enter para continuar...");
            getchar();
        }
    }
}

#endif // LSO_H_INCLUDED
