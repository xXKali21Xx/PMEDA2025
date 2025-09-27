#ifndef RAL_H_INCLUDED
#define RAL_H_INCLUDED
#include "LSO.h"
#define maxRAL 150 //sacar bien la cuenta


int hashing(char* x, int M){
    int longitud, i;
    int contador = 0;
    longitud = strlen(x);
    for(i = 0;  i<longitud; i++){
        contador +=((int)x[i] * (i+1));
    }
    return (contador % M);
}
//usamos la misma estructura para RAC
typedef struct{
    int estado; //1 virgen, 2 libre, 3 ocupada
    Alumno alumno;
}Celda;

typedef struct{
    Celda  arreglo[maxRAL];
    int cantidad;
}rebalse;

void iniRAL(rebalse *ral){ //inicializar el rebalse
    int i = 0;
    (*ral).cantidad = 0;
    while(i < maxRAL){
        (*ral).arreglo[i].estado = 1;
        i++;
    }
}


int localizarRAL(char* codigo, rebalse ral, int *exito, float *costo, int *pos){
    int i = hashing(codigo, maxRAL);
    int j = 0;
    while((ral.arreglo[i].estado != 1) && j < maxRAL){
        if(strcmpi(ral.arreglo[i].alumno.codigo, codigo) == 0 && ral.arreglo[i].estado == 3){
            *exito = 1;
            *pos = i;
            *costo = *costo + 1;
            return 1; //lo encontro
        }else{
            *pos = i; //devuelve la posicion ya que si no esta ocupada, puede ser libre
            exito = 0; //no lo encuentra
        }
        *costo = *costo + 1;
        i = (i+1) % maxRAL;
        j++; 
    }
    return 0; //caso que no se encuentre
}

int AltaRAL(rebalse *ral, Alumno alu, float *costo, int *exito){
    int pos = 0;
    if((*ral).cantidad >= maxRAL){
        return 2; //no se pudo dar de alta, rebalse lleno
    }else{
        localizarRAL(alu.codigo, *ral, exito, costo, &pos);
        if((*exito) == 1){
            (*exito) = 0; //no se pudo dar de alta, ya existe
            return 0;
        }else{
            (*ral).arreglo[pos].alumno = alu;
            (*ral).arreglo[pos].estado = 3; //ocupada
            (*ral).cantidad++;
            (*exito) = 1; //se pudo dar de alta
            return 1;
        }
    }
    
}
    
void muestraRAL(rebalse ral){
    int i = 0;
    while(i < maxRAL){
        if(ral.arreglo[i].estado == 3){
            printf("Nombre: %s\n", ral.arreglo[i].alumno.nombre);
            printf("Mail: %s\n", ral.arreglo[i].alumno.mail);
            printf("Codigo: %s\n", ral.arreglo[i].alumno.codigo);
            printf("Condicion: %s\n", ral.arreglo[i].alumno.condicion);
            printf("Nota: %d\n", ral.arreglo[i].alumno.nota);
            printf("-----------------------\n");
        }
        i++;
        if(ral.arreglo[i].estado == 1){
            printf("--------------------- La celda en %d es virgen ---------------------- \n", i);
        }if(ral.arreglo[i].estado == 2){
            printf("--------------------- La celda en %d es libre ---------------------- \n", i);
        }
        i++;
        if(i%5 == 0){
            printf("Presione una tecla para continuar...\n");
            getchar();
        }
    }
}

int BajaRAL(rebalse *ral, Alumno x, int *exito){
    int pos = 0;
    float costo = 0;
    if((*ral).cantidad == 0){
        (*exito) = 0; 
        return 2; //no se pudo dar de baja, rebalse vacio
    }
    localizarRAL(x.codigo, *ral, exito, &costo, &pos);
    if((*exito) == 1 && comparacion(*ral,x, pos )){ //si lo encontro y son iguales
        (*ral).arreglo[pos].estado = 2; //libre
        (*ral).cantidad--;
        (*exito) = 1; //se pudo dar de baja
        return 1;
    }else{
        (*exito) = 0; //no se pudo dar de baja, no existe
        return 0;
    }
}    

int EvocarRAL(rebalse ral, char codigo[], int *exito, float *costo){
    int pos;
    localizarRAL(codigo, ral, exito, costo, &pos);
    if((*exito) == 1){
        (*exito) =1; //se pudo evocar
        return pos;
    }else{
        (*exito) = 0; //no se pudo evocar, no existe
        return 0;
    }
}

//funcion para comparar dos alumnos
int comparacion(rebalse ral, Alumno alu, int pos){
    if(strcmpi(ral.arreglo[pos].alumno.codigo, alu.codigo) != 1 ){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.condicion, alu.condicion) != 1 ){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.mail, alu.condicion) != 1 ){
        return 0;
    }
    if(strcmpi(ral.arreglo[pos].alumno.nombre, alu.nombre) != 1 ){
        return 0;
    }
    if(ral.arreglo[pos].alumno.nota ==  alu.nota ){
        return 0;
    }
    return 1;
}
#endif // RAL_H_INCLUDED
