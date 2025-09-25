#ifndef RAC_H_INCLUDED
#define RAC_H_INCLUDED
#define maxRAC 150
void iniRAC(rebalse *ral){ //inicializar el rebalse
    int i = 0;
    (*ral).cantidad = 0;
    while(i < maxRAL){
        (*ral).arreglo[i].estado = 1;
        i++;
    }
}

#endif // RAC_H_INCLUDED
