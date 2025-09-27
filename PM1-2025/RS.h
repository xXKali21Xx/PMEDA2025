#ifndef RS_H_INCLUDED
#define RS_H_INCLUDED
#define maxRS 150
typedef struct{
    Alumno elem;
    struct NodoRS *sig;
}NodoRS;

typedef struct{
    NodoRS *acc;
    NodoRS *cursor;
    NodoRS *aux;
    int cant;
}RS;

void initRS(RS *rs){
	int i;
	for(i = 0; i < M_RS; i++){
		rs[i].acc = NULL;
		(*rs).aux = NULL;
        (*rs).cursor = NULL;
	}
	(*rs).cant = 0;
}
#endif // RS_H_INCLUDED
