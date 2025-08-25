#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "string.h"
typedef struct{
    char nombre[80]; //contiene el apellido
    char mail[23];
    char codigo[7];
    char condicion[10]; // 0 = Ausente , 1 = regular , 2 = promociona , 3 = Libre
    int nota;
}Alumno;

//Localizar
int localizar(Alumno lista[], int *cant, char cod[], int *exito, int *pos){
    int i = 0;
    if(cant == 0){ //no hay elementos en la lista
        (*exito) = 0;
        (*pos) = 0;
    }else{
        while((i < cant) && (strcmpi(lista[i].codigo,cod) < 0)){ //mientras que no salga de la lista y el codigo sea menor compara
            i++;
        }
        if((i < cant) && (strcmpi(lista[i].codigo,cod) == 0)){ //si sigue dentro de la lista y el codigo comparado es igual se encontro
            (*exito) = 1; //se encontro
            (*pos) = i;
        }else{ //no se encontro
            (*exito) = 2;
            (*pos) = i; // posicion donde se puede insertar el elemento
        }
    }
    return *exito;
}
//Alta
int Alta(Alumno lista[], Alumno x, int *cant, int *exito){
    int pos = 0;
    int i = 0;
    if((*cant) + 1 == 130){
        (*exito) = -1; // no hay epsacio
        pos = -1;
    }
    localizar(lista, cant, x.codigo, exito, &pos);
    if((*exito) == 1){ //se encontro el elemento por lo tanto no se puede insertar
        (*exito) = 0;
    }
    if((*exito) == 2){ // no se encontro el elemento por lo tanto se puede insertar
        for(i = (*cant); pos < i; i--){
            lista[i] = lista[i-1]; //hace el corrimiento
        }
        lista[i] = x;
        (*exito) = 1;
        (*cant)++;
    }
    return *exito;
}
//Baja
int Baja(Alumno lista[], char x[], int *cant, int *exito){
    int pos;
    if((*cant) == 0){
        (*exito) = -1; //no hay elementos en la lista
    }
    localizar(lista,cant,x,exito,&pos);
    if((*exito) == 2){
        (*exito) = 2; //el elemento no se encontro en la lista
    }else{

    }

}
//Modificar
//Evocar
//Muestra
void muestra(Alumno lista[], int cant){
    int i = 0;
    while(i < cant){
        printf("Nombre y Apellido: %s", lista[i].nombre );
        printf("Mail: %s", lista[i].mail);
        printf("Codigo Alumno: %s", lista[i].codigo);
        printf("Condicion: %s", lista[i].codigo);
        printf("Nota: %d", lista[i].nota);
        i++;
    }
}
//memorizacion previa
void memorizacion_previa(Alumno *lista,int *cant, int *exito) {
    FILE *fp;
    Alumno aux;
    fp = fopen("Alumnos.txt", "r");
    if (fp == NULL) {
        printf("Error: No se encontro el archivo 'Alumnos.txt'\n");
    }
    else{
        while (feof(fp)==0) {
        fscanf(fp, "%[^\n]", aux.codigo);
        fscanf(fp, "%[^\n]", aux.nombre);
        fscanf(fp, "%[^\n]", aux.mail);
        fscanf(fp, "%d", &aux.nota);
        fscanf(fp, "%[^\n]", aux.condicion);
        Alta(lista,aux,cant,exito);
        (*cant)++;
    }

    fclose(fp);

}
#endif // LSO_H_INCLUDED
