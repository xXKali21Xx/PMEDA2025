#ifndef COMPARACIONES_H_INCLUDED
#define COMPARACIONES_H_INCLUDED

typedef struct {
    float acumulador; //acumula contador de costos
    float cantidad_maxima; //costo maximo
    float cant; //cantidad de elementos
    float resultado; // resultado de media
}costo;

void initcosto(costo a[]){
    int i;
    for(i=0;i<2;i++){
        a[i].acumulador = 0.0;
        a[i].cantidad_maxima = 0.0;
        a[i].cant = 0.0;
        a[i].resultado = 0.0;
    }
}


#endif // COMPARACIONES_H_INCLUDED
