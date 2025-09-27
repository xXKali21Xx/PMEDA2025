#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define maxRAC 150
#include "RAL.h"
#include "LSO.h"

void iniRAC(rebalse *ral){ //inicializar el rebalse
    int i = 0;
    (*ral).cantidad = 0;
    while(i < maxRAL){
        (*ral).arreglo[i].estado = 1;
        i++;
    }
}

int localizarRAC(char* codigo, rebalse rac, int *exito, float *costo, int *pos){
    int i = hashing(codigo, maxRAC);
    int j = 0;
    int k = 1;
    while((rac.arreglo[i].estado != 1) && j < maxRAC){
        if(strcmpi(rac.arreglo[i].alumno.codigo, codigo) == 0 && rac.arreglo[i].estado == 3){
            *exito = 1;
            *pos = i;
            *costo = *costo + 1;
            return 1; //lo encontro
        }else{
            *pos = i; //devuelve la posicion ya que si no esta ocupada, puede ser libre
            exito = 0; //no lo encuentra
        }
        *costo = *costo + 1;
        i = (i+k) % maxRAC;
        j++; 
        k++;
    }
    return 0; //caso que no se encuentre
}

int AltaRAC(rebalse *rac, Alumno alu, float *costo, int *exito){
    int pos = 0;
    if((*rac).cantidad >= maxRAC){
        return 2; //no se pudo dar de alta, rebalse lleno
    }else{
        localizarRAL(alu.codigo, *rac, exito, costo, &pos);
        if((*exito) == 1){
            (*exito) = 0; //no se pudo dar de alta, ya existe
            return 0;
        }else{
            (*rac).arreglo[pos].alumno = alu;
            (*rac).arreglo[pos].estado = 3; //ocupada
            (*rac).cantidad++;
            (*exito) = 1; //se pudo dar de alta
            return 1;
        }
    }
}

void muestraRAC(rebalse rac){
    int i = 0;
    while(i < maxRAC){
        if(rac.arreglo[i].estado == 3){
            printf("Nombre: %s\n", rac.arreglo[i].alumno.nombre);
            printf("Mail: %s\n", rac.arreglo[i].alumno.mail);
            printf("Codigo: %s\n", rac.arreglo[i].alumno.codigo);
            printf("Condicion: %s\n", rac.arreglo[i].alumno.condicion);
            printf("Nota: %d\n", rac.arreglo[i].alumno.nota);
            printf("-----------------------\n");
        }
        i++;
        if(rac.arreglo[i].estado == 1){
            printf("--------------------- La celda en %d es virgen ---------------------- \n", i);
        }if(rac.arreglo[i].estado == 2){
            printf("--------------------- La celda en %d es libre ---------------------- \n", i);
        }
        i++;
        if(i%5 == 0){
            printf("Presione una tecla para continuar...\n");
            getchar();
        }
    }
}

int BajaRAC(rebalse *rac, Alumno x, int *exito){
    int pos = 0;
    float costo = 0;
    if((*rac).cantidad == 0){
        (*exito) = 0; 
        return 2; //no se pudo dar de baja, rebalse vacio
    }
    localizarRAL(x.codigo, *rac, exito, &costo, &pos);
    if((*exito) == 1 && comparacionRAC(*rac,x, pos )){ //si lo encontro y son iguales
        (*rac).arreglo[pos].estado = 2; //libre
        (*rac).cantidad--;
        (*exito) = 1; //se pudo dar de baja
        return 1;
    }else{
        (*exito) = 0; //no se pudo dar de baja, no existe
        return 0;
    }
}    

int EvocarRAC(rebalse rac, char codigo[], int *exito, float *costo){
    int pos;
    localizarRAL(codigo, rac, exito, costo, &pos);
    if((*exito) == 1){
        (*exito) =1; //se pudo evocar
        return pos;
    }else{
        (*exito) = 0; //no se pudo evocar, no existe
        return 0;
    }
}

//funcion para comparar dos alumnos
int comparacionRAC(rebalse rac, Alumno alu, int pos){
    if(strcmpi(rac.arreglo[pos].alumno.codigo, alu.codigo) != 1 ){
        return 0;
    }
    if(strcmpi(rac.arreglo[pos].alumno.condicion, alu.condicion) != 1 ){
        return 0;
    }
    if(strcmpi(rac.arreglo[pos].alumno.mail, alu.condicion) != 1 ){
        return 0;
    }
    if(strcmpi(rac.arreglo[pos].alumno.nombre, alu.nombre) != 1 ){
        return 0;
    }
    if(rac.arreglo[pos].alumno.nota ==  alu.nota ){
        return 0;
    }
    return 1;
}
#endif // RAC_H_INCLUDED
