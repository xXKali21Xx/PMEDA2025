#ifndef LSO_H_INCLUDED
#define LSO_H_INCLUDED
#include "string.h"
#include "stdio.h"

typedef struct{
    char nombre[80]; //contiene el apellido
    char mail[24];
    char codigo[8];
    char condicion[10]; // 0 = Ausente , 1 = regular , 2 = promociona , 3 = Libre
    int nota;
}Alumno;
//Funcion auxiliar

/*Alumno Ingreso(Alumno *x){
    printf("Ingrese el nombre y apellido del alumno \n");
    scanf(" %[^\n]",(*x).nombre);
    fflush(stdin);
    printf("Ingrese el mail del alumno \n");
    scanf(" %[^\n]",(*x).mail);
    fflush(stdin);
    printf("Ingrese el codigo del alumno\n");
    scanf(" %[^\n]",(*x).codigo);
    fflush(stdin);
    printf("Ingrese la condicion del alumno\n");
    scanf(" %[^\n]",(*x).condicion);
    fflush(stdin);
    printf("Ingrese la nota del alumno \n");
    scanf("%d", &(*x).nota);
    fflush(stdin);
}*/
//Localizar
int localizar(Alumno lista[], int *cant, char cod[], int *exito, int *pos){
    int i = 0;
    if(*cant == 0){ //no hay elementos en la lista
        (*exito) = 2;
        (*pos) = 0;
    }else{
        while((i < *cant) && (strcmpi(lista[i].codigo,cod) < 0)){ //mientras que no salga de la lista y el codigo sea menor compara
            i++;
        }
        if((i < *cant) && (strcmpi(lista[i].codigo,cod) == 0)){ //si sigue dentro de la lista y el codigo comparado es igual se encontro
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
    if(*cant  >= 130){
        (*exito) = -1; // no hay epsacio
        pos = -1;
    }
    localizar(lista, cant, x.codigo, exito, &pos);
    if((*exito) == 1){ //se encontro el elemento por lo tanto no se puede insertar
        (*exito) = 0;
    }
    if((*exito) == 2){ // no se encontro el elemento por lo tanto se puede insertar
        for(i = (*cant); i > pos; i--){
            if(i<130){
                lista[i] = lista[i-1]; //hace el corrimiento
            }
        }
        lista[pos] = x;
        (*exito) = 1;
        (*cant)++;
    }
    return *exito;
}
//Baja
int Baja(Alumno lista[], char x[], int *cant, int *exito){
    int pos;
    int i;
    int opcion = 0;
    if((*cant) == 0){
        (*exito) = -1; //no hay elementos en la lista
    }
    localizar(lista,cant,x,exito,&pos);

    if((*exito) == 2){
        (*exito) = 2; //el elemento no se encontro en la lista
    }else{
        if((*exito) == 1){ //el elemento esta en la lista
            printf("Nombre y Apellido: %s \n", lista[pos].nombre );
            printf("Mail: %s \n", lista[pos].mail);
            printf("Codigo Alumno: %s \n", lista[pos].codigo);
            printf("Condicion: %s \n", lista[pos].condicion);
            printf("Nota: %d \n", lista[pos].nota);

            printf("------------------------------------------- \n"); //mostramos el elemento

            printf("ingrese 1 si quiere borrar el elemento \n");
            printf("ingrese 0 si NO quiere borrar el elemento \n"); // confirmacion de la baja
            scanf("%d", &opcion);
            while(opcion != 1 && opcion != 0){
                printf("ERROR, ingrese un valor correcto \n");
                printf("ingrese 1 si quiere borrar el elemento \n");
                printf("ingrese 0 si NO quiere borrar el elemento \n");
                scanf("%d", &opcion);
            }
            if(opcion == 1){ //en caso que si quiera borrarlo
                for(i = pos; i < (*cant); i++){
                    lista[i] = lista[i+1]; //suprimimos el elemento
                    break;
                }
                (*exito) = 1; // se borro
                (*cant)--; //decrementamos la cantidad total
            }else{
                (*exito) = 0; // no se borro
            }
        }
    }

    return (*exito);

}
//Modificar
int Modificar(Alumno lista[], int *cant, char cod[], int *exito) {
    int pos = 0;
    localizar(lista, cant, cod, exito, &pos);
    if (*exito == 1) {
        printf("Alumno encontrado: \n");
        printf("Codigo del alumno: %s \n", lista[pos].codigo);
        printf("Nombre: %s\n", lista[pos].nombre);
        printf("Mail: %s\n", lista[pos].mail);
        printf("Condicion: %s\n", lista[pos].condicion);
        printf("Nota: %d\n", lista[pos].nota);
        getchar();
        printf("Ingrese nuevo nombre: \n");
        scanf("%[^\n]s", lista[pos].nombre);
        getchar();
        printf("Ingrese nuevo mail: \n");
        scanf("%s", lista[pos].mail);
        getchar();
        printf("Ingrese nueva condicion: \n");
        scanf("%s", lista[pos].condicion);
        getchar();
        printf("Ingrese nueva nota: \n");
        scanf("%d", &lista[pos].nota);

        *exito = 1;
    } else {
        *exito = 0;
    }
    return *exito;
}


//Evocar
Alumno* Evocar(Alumno lista[], int *cant, char cod[], int *exito) {
    int pos = 0;
    localizar(lista, &cant, cod, exito, &pos);
    if (*exito == 1) {
        return &lista[pos];
    } else {
        return NULL;
    }
}

//Muestra
void muestra(Alumno lista[], int cant){
    int i = 0;
    printf("cant tiene: %d\n",cant);
    while(i < cant){
        printf("i: %d\n",i);
        printf("Nombre y Apellido: %s \n", lista[i].nombre );
        printf("Mail: %s \n", lista[i].mail);
        printf("Codigo Alumno: %s \n", lista[i].codigo);
        printf("Condicion: %s \n", lista[i].condicion);
        printf("Nota: %d \n", lista[i].nota);
        i++;
        printf("------------------------------------------- \n");
        if(i%5 == 0){
            printf("Presiones enter para continuar... \n");
            getchar();
        }
    }
}

//memorizacion previa
int memorizacion_previa(Alumno *lista, int *cant, int *exito) {
    FILE *fp;
    Alumno aux;
    int d=1;
    if ((fp = fopen("Alumnos.txt", "r")) == NULL) {
        printf("Error: No se encontro el archivo 'Alumnos.txt'\n");
        *exito = 0;
        return 0;
    }
    else{
        while (feof(fp)==0) {

        fscanf(fp, " %[^\n]", aux.codigo);
        fflush(stdin);
        fscanf(fp, " %[^\n]", aux.nombre);
        fflush(stdin);
        fscanf(fp, " %[^\n]", aux.mail);
        fflush(stdin);
        fscanf(fp, "%d", &aux.nota);
        fflush(stdin);
        fscanf(fp, " %[^\n]", aux.condicion);
        fflush(stdin);

        printf("Cargando alumno: %d \n", d);
        printf("Codigo: %s\n", aux.codigo);
        printf("Nombre: %s\n", aux.nombre);
        printf("Mail: %s\n", aux.mail);
        printf("Nota: %d\n", aux.nota);
        printf("Condicion: %s\n", aux.condicion);
        printf("---\n");
        d++;
        Alta(lista,aux,cant,exito);
        }
    }

    fclose(fp);
    *exito = 1;
    return 1;
}
#endif // LSO_H_INCLUDED
