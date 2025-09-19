#ifndef LIBT_H_INCLUDED
#define LIBT_H_INCLUDED
#include "LSO.h"
typedef struct
{
    Alumno *alumnoslibt[130];
    int ultimo;
} LIBT;

int localizarLSOBT(int *exito, char codigo[], LIBT lista[], float *costo, int cant, int *pos){
    int li = 0, ls = cant;//limite inferior y superior inclusivo
    int t; //testigo
   
    if (cant == 0){
        (*exito) = -1;
        (*pos) = 0;
        return -1; //lista vacia
    }
     t = ceil((li + ls) / 2);
    while((li <= ls) && strcmpi(lista->alumnoslibt[t]->codigo, codigo) != 0){
        if(strcmpi(lista->alumnoslibt[t]->codigo, codigo) < 0){
            ls = t - 1;
            
        }else{
            li = t + 1;
            
        } 
        (*costo) += 1;
        t = ceil((li + ls) / 2);
    }
    if(strcmpi(lista->alumnoslibt[t]->codigo, codigo) > 0){
        (*exito) = 0; 
        (*pos) = ls + 1; 
        (*costo) += 1;
        return (*exito);
    }
    (*pos) = t;
    (*exito) = 1;
    (*costo) += 1;
    return (*exito);
}

int AltaLI(LIBT lista[], Alumno x, int *cant, int *exito, float *costo ){
    int pos = 0;
    int i = 0;
    localizarLSOBT(exito, x.codigo, lista, costo, *cant, &pos); //revisar el & en costo
    if((*exito) == 1){
        return 0; //el elemento ya existe
    }else{
        Alumno *nuevo = (Alumno*) malloc(sizeof(Alumno));
        if(nuevo == NULL){
            return -1; //no hay memoria
        }
        *nuevo = x;
        for(i = (*cant); i > pos; i--){
            lista[i] = lista[i-1]; //hace el corrimiento
            (*costo) += 1;
        }
        lista[pos] = nuevo;
        (*exito) = 1;
        (*cant)++;
        (*costo) += 1;
        return 1; //se inserto el elemento
    }
    
}

int BajaLI(LIBT lista[], Alumno x, int *cant, int *exito, float *costo){
    int pos;
    int i;
    localizarLSOBT(exito, x.codigo, lista, costo, *cant, &pos);
    if((*exito) == 0){
        (*exito) = 2; //el elemento no se encontro en la lista
        return 2;
    }else{
        if((*exito) == 1){ //el elemento esta en la lista
            if(strcmpi(lista[pos]->codigo, x.codigo) == 0){
                if(strcmpi(lista[pos]->nombre, x.nombre) == 0){
                    if(strcmpi(lista[pos]->mail, x.mail) == 0){
                        if(strcmpi(lista[pos]->condicion, x.condicion) == 0){
                            if(lista[pos]->nota == x.nota){//coinciden todos los campos
                                free(lista[pos]); //libera la memoria del alumno
                                for(i = pos; i < (*cant)-1; i++){
                                    lista[i] = lista[i+1]; //suprimimos el elemento
                                    (*costo) += 1;
                                }
                                (*exito) = 1; // se borro
                                (*cant)--; //decrementamos la cantidad total
                                return 1;
                            }else{
                                return 3; //no coinciden todos los campos
                            }
                        }else{
                            return 3; //no coinciden todos los campos
                        }
                    }else{
                        return 3; //no coinciden todos los campos
                    }
                }else{
                    return 3; //no coinciden todos los campos
                }
            }else{
                return 3; //no coinciden todos los campos
            }   
        }
    }

}

int evocar(LIBT lista[], char cod[], int *exito, float *costo, int cant){
    int pos;
    localizarLSOBT(exito, cod, lista, costo, cant, &pos);
    if (*exito == 1) {
        return lista[pos];
    } else {
        return 0;
    }
}

void muestra(LIBT Lista[], int cant){
    int i = 0;
    while(i < cant){
        printf("----- LISTA DE ALUMNOS ----- \n");
        printf("Cantidad de alumnos: %d \n", &i+1);
        printf("Nombre y Apellido: %s \n", Lista.alumnoslibt[i]->nombre );
        printf("Mail: %s \n", Lista.alumnoslibt[i]->mail);
        printf("Codigo Alumno: %s \n", Lista.alumnoslibt[i]->codigo);
        printf("Condicion: %s \n", Lista.alumnoslibt[i]->condicion);
        printf("Nota: %d \n", Lista.alumnoslibt[i]->nota);

        printf("---------------------------- \n");
        i++;
        if(i % 5){
            printf("Presione una tecla para continuar... \n");
            getchar();
        }
    }


}
#endif // LIBT_H_INCLUDED
