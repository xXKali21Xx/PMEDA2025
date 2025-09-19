#ifndef ABB_H_INCLUDED
#define ABB_H_INCLUDED
#include "LSO.h"
typedef struct{
    Alumno dato; //dato del alumno
    struct nodo *Derecha; //apunta al nodo derecho
    struct nodo *izquierda; //apunta al nodo izquierdo
}nodo;

typedef struct{
    nodo *raiz; //nodo raiz
    nodo *aux; //nodo auxiliar
    nodo *cursor; //cursor del nodo
    int cant; //cantidad de elementos en el arbol
}arbol;

void init(arbol *a){ //inicializa el arbol
    a->raiz = NULL;
    a->cursor = NULL;
    a->aux = NULL;
    a->cant = 0;
}

nodo* nuevonodoABB(Alumno x){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    if(n == NULL){
        return n; //caso de que no tenga memoria sale
    }
    n->dato = x;
    n->Derecha = NULL;
    n->izquierda= NULL;
    return n; //caso que tenga memoria crea un nodo con izq y derecha nulos
}

arbol nuevoarbol(){
    arbol a;
    a.raiz = NULL;
    a.aux = NULL;
    a.cant = 0;
    a.cursor = NULL;
    return a;
}
void localizarABB(arbol *a, char cod[], int *exito, float *costo) {

    if (a == NULL || a->raiz == NULL) {
        *exito = 0;
        return;
    }

    a->cursor = a->raiz;
    a->aux = NULL;

    while (a->cursor != NULL) {
        *costo = *costo + 1;

        int comparacion = strcmp(a->cursor->dato.codigo, cod);

        if (comparacion == 0) {
            *exito = 1;
            return;
        }

        a->aux = a->cursor;

        if (comparacion > 0) {
            a->cursor = a->cursor->izquierda;
        } else {
            a->cursor = a->cursor->Derecha;
        }
    }

    *exito = 0;
}

//funcion auxiliar
int confirmacionbaja(arbol a, arbol b,){ //compara dos nodos
    if(strcmpi(a->cursor->dato.codigo,b->cursor->dato.codigo)==0){
        if(strcmpi(a->cursor->dato.nombre,b->cursor->dato.nombre)==0){
            if(strcmpi(a->cursor->dato.mail,b->cursor->dato.mail)==0){
                if(strcmpi(a->cursor->dato.codigo,b->cursor->dato.codigo)==0){
                    if(a->cursor->dato.nota == b->cursor->dato.nota){
                        return 1; //son iguales
                    }else{
                        return 0;//no son iguales
                    }
                }else{
                    return 0;
                }
            }else{
                return 0;
            }
        }else{
            return 0;
    }else{
        return 0;
    }
}
}
int BajaABB(arbol *a,char cod[],float *costo,int *exito){
    //localizarABB(a,cod,exito,costo);
    if(exito){
        if(confirmacionbaja(a,b)==1){
            //sin hijos
            if(a->cursor->Derecha == NULL && a->cursor->izquierda == NULL){
                if(a->cursor == a->raiz){ //es raiz
                    a->raiz = NULL;
                }
            }else{
                if(a->aux->izquierda == a->cursor){ //padre izq
                    a->aux->izquierda = NULL;
                }else{ //padre der
                    a->aux->Derecha = NULL;
                }
            free((void*)(a->cursor));
            *costo = *costo + 0.5;
            a->cant--;
            }
            //con hijo izquierdo
            if(a->cursor->Derecha == NULL && a->cursor->izquierda != NULL){
            if(a->cursor == a->raiz){ //es raiz
                a->raiz = a->cursor->izquierda;
            }
            if (a->aux->izquierda == a->cursor){ //padre izquierdo
            a->aux->izquierda = a->cursor->izquierda;
            }else{
                a->aux->Derecha = a->cursor->izquierda; //padre dercho
            }
            free((void*)(a->cursor));
            *costo = *costo + 0.5;
            a->cant--;
            }
            //con hijo der
            if(a->cursor->Derecha != NULL && a->cursor->izquierda == NULL){
                if(a->cursor == a->raiz){
                    a->raiz = a->cursor->Derecha;
                }
                if(a->aux->izquierda == a->cursor){ //padre izq
                    a->aux->izquierda = a->cursor->Derecha;
                }else{
                    a->aux->Derecha = a->cursor->Derecha; //padre der
                }
                free((void*)(a->cursor));
                *costo = *costo + 0.5;
                a->cant--;
            }
            //con dos hijos
            //Con dos hijo,Politica de Remplazo mayor de los menores
            if(a->cursor->Derecha != NULL && a->cursor->izquierda != NULL){
                nodo *mayor = a->cursor->izquierda; //apunta al hijo izquierdo
                nodo *padremayor = a->cursor; //apunta al padre mayor

                //busco el mayor dentro del arbol izquierdo
                while(mayor->dato != NULL){
                    padremayor = mayor;
                    mayor = mayor->Derecha;
                }

                //copio los datos del mayor en el nodo que voy a eliminar del arbol
                a->cursor->dato = mayor->dato;

                //el mayor puede tener hijo izquierdo
                if(padremayor->Derecha == mayor){ //mayor es hijo derecho
                    padremayor->Derecha = mayor->izquierda;
                }else{
                    padremayor->izquierda = mayor->izquierda; //mayor era hijo izquierdo
                }
                free((void*)(mayor));
                a->cant--;
                *costo = *costo + 1.5;
            }
        }else{
            *exito = 2; //no se pudo eliminar
            return -1; //no coinciden los datos
        }
    }else{
        *exito = 0; //no se encontro el alumno
        return -1;
    }
}

Alumno evocarABB(arbol *a, int *exito, float *costo, char cod[]){
    int exitoL;//va con el localizar
    Alumno x;
    //localizarABB
    if(exito){
        strcpy(x->correo, a->cursor->dato.correo);
        strcpy(x->nombre, a->cursor->dato.nombre);
        strcpy(x->codigo, a->cursor->dato.codigo);
        strcpy(x->condicion, a->cursor->dato.condicion);
        x->nota = a->cursor->dato.nota;
        (*exito) = 1;
        return x; //devuelve el alumno encontrado
    }else{
        (*exito) = 0;
        return x; //devuelve un alumno vacio
    }
}

void muestraABB(arbol a){
    if(a->raiz == NULL){
        return -1; //arbol vacio
    }
    //recorrido PRE-ORDEN
    printf("----------------------------------------- \n");
    printf("Nodo Numero: %d \n", a->cant);
    printf("Nombre: %s\n", a->cursor->dato.nombre);
    printf("Codigo: %s\n", a->cursor->dato.codigo);
    printf("Mail: %s\n", a->cursor->dato.mail);
    printf("Condicion: %s\n", a->cursor->dato.condicion);
    printf("Nota: %d\n", a->cursor->dato.nota);
    printf("----------------------------------------- \n");

    muestraABB(a->cursor->izquierda);
    muestraABB(a->cursor->Derecha);
>>>>>>> 209f4d6f5d90c13bdb9cd243e6ff9a193d611eec
}
int precargarOperacionesABB(arbol *a,float *costo,int *exito) {
    FILE *fp;
    int eleccion;
    Alumno aux;
    if ((fp = fopen("Operaciones-Alumnos.txt", "r")==NULL) {
        *exito = 0;
        return 0;
    }else{
    while (fscanf(fp, "%d", &eleccion) == 1) {
        switch (eleccion) {
            case 1:
                fscanf(fp, " %[^\n]", aux.codigo);
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.mail);
                fscanf(fp, "%d", &aux.nota);
                fscanf(fp, " %[^\n]", aux.condicion);
                altaABB(a,aux,costo,exito);
                break;

            case 2:
                fscanf(fp, " %[^\n]", aux.codigo);
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.mail);
                fscanf(fp, "%d", &aux.nota);
                fscanf(fp, " %[^\n]", aux.condicion);
                BajaABB(a,aux.codigo,costo,exito);
                break;

            case 3:
                fscanf(fp, " %[^\n]", aux.codigo);
                evocarABB(a,exito,costo,aux.codigo);
                break;
        }
     }
    }
    fclose(fp);
    *exito 1;
    return 1;
}

#endif // ABB_H_INCLUDED
