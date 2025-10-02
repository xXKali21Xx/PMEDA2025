#ifndef COMPARACIONES_H_INCLUDED
#define COMPARACIONES_H_INCLUDED
typedef struct {
    float total_alta, max_alta;
    int contalta;
    float total_baja, max_baja;
    int contbaja;
    float total_evoex, max_evoex;
    int contevoex;
    float total_evonoex, max_evonoex;
    int contevonoex;
} Costos;

void mostrarResultados(int cantLSO, int cantLIBT, int cantABB, Costos lso, Costos libt, Costos abb) {
    printf("\n+-----------------------------------------------------------+\n");
    printf("|          CUADRO COMPARATIVO DE COSTOS                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| ESTRUCTURA           | %-8s | %-8s | %-8s |   |\n", "LSO", "LIBT", "ABB");
    printf("+-----------------------------------------------------------+\n");
    printf("| OPERACIONES DE ALTA                                       |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Costo Maximo         | %-8.2f | %-8.2f | %-8.2f |   |\n", lso.max_alta, libt.max_alta, abb.max_alta);
    printf("| Costo Promedio       | %-8.2f | %-8.2f | %-8.2f |   |\n", (lso.contalta > 0 ? lso.total_alta / lso.contalta : 0), (libt.contalta > 0 ? libt.total_alta / libt.contalta : 0), (abb.contalta > 0 ? abb.total_alta / abb.contalta : 0));
    printf("+-----------------------------------------------------------+\n");
    printf("| OPERACIONES DE BAJA                                       |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Costo Maximo         | %-8.2f | %-8.2f | %-8.2f |   |\n", lso.max_baja, libt.max_baja, abb.max_baja);
    printf("| Costo Promedio       | %-8.2f | %-8.2f | %-8.2f |   |\n", (lso.contbaja > 0 ? lso.total_baja / lso.contbaja : 0), (libt.contbaja > 0 ? libt.total_baja / libt.contbaja : 0), (abb.contbaja > 0 ? abb.total_baja / abb.contbaja : 0));
    printf("+-----------------------------------------------------------+\n");
    printf("| BUSQUEDAS EXITOSAS (EVOEX)                                |\n");
    printf("+----------------------+----------+----------+--------------+\n");
    printf("| Costo Maximo         | %-8.2f | %-8.2f | %-8.2f |   |\n", lso.max_evoex, libt.max_evoex, abb.max_evoex);
    printf("| Costo Promedio       | %-8.2f | %-8.2f | %-8.2f |   |\n", (lso.contevoex > 0 ? lso.total_evoex / lso.contevoex : 0), (libt.contevoex > 0 ? libt.total_evoex / libt.contevoex : 0), (abb.contevoex > 0 ? abb.total_evoex / abb.contevoex : 0));
    printf("+-----------------------------------------------------------+\n");
    printf("| BUSQUEDAS FALLIDAS (EVONOEX)                              |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| Costo Maximo         | %-8.2f | %-8.2f | %-8.2f |   |\n", lso.max_evonoex, libt.max_evonoex, abb.max_evonoex);
    printf("| Costo Promedio       | %-8.2f | %-8.2f | %-8.2f |   |\n", (lso.contevonoex > 0 ? lso.total_evonoex / lso.contevonoex : 0), (libt.contevonoex > 0 ? libt.total_evonoex / libt.contevonoex : 0), (abb.contevonoex > 0 ? abb.total_evonoex / abb.contevonoex : 0));
    printf("+-----------------------------------------------------------+\n");
    printf("| Alumnos Finales      | %-8d | %-8d | %-8d |   |\n", cantLSO, cantLIBT, cantABB);
    printf("+-----------------------------------------------------------+\n");
}


//Funciones auxiliares

void procesarAlta(Alumno data,
    Alumno lso[], int *cantLSO, Costos *costoLSO,
    LIBT *libt, int *cantLIBT, Costos *costoLIBT,
    arbol *abb, int *cantABB, Costos *costoABB) {

    int exito;
    float costo;

    // LSO
    costo = 0.0;
    Alta(lso, data, cantLSO, &exito, &costo);
    if (exito == 1) {
        costoLSO->total_alta += costo;
        costoLSO->contalta++;
        if (costo > costoLSO->max_alta) costoLSO->max_alta = costo;
    }

    // LIBT
    costo = 0.0;
    AltaLI(libt, data, cantLIBT, &exito, &costo);
    if (exito == 1) {
        costoLIBT->total_alta += costo;
        costoLIBT->contalta++;
        if (costo > costoLIBT->max_alta) costoLIBT->max_alta = costo;
    }

    // ABB
    costo = 0.0;
    AltaABB(abb, data, &exito, &costo, cantABB);
    if (exito == 1) {
        costoABB->total_alta += costo;
        costoABB->contalta++;
        if (costo > costoABB->max_alta) costoABB->max_alta = costo;
    }
}


void procesarBaja(Alumno data,
    Alumno lso[], int *cantLSO, Costos *costoLSO,
    LIBT *libt, int *cantLIBT, Costos *costoLIBT,
    arbol *abb, Costos *costoABB) {

    int exito;
    float costo;

    // LSO
    costo = 0.0;
    Baja(lso, data, cantLSO, &exito, &costo);
    if (exito == 1) {
        costoLSO->total_baja += costo;
        costoLSO->contbaja++;
        if (costo > costoLSO->max_baja) costoLSO->max_baja = costo;
    }

    // LIBT
    costo = 0.0;
    BajaLI(libt, data, cantLIBT, &exito, &costo);
    if (exito == 1) {
        costoLIBT->total_baja += costo;
        costoLIBT->contbaja++;
        if (costo > costoLIBT->max_baja) costoLIBT->max_baja = costo;
    }

    // ABB
    costo = 0.0;
    BajaABB(abb, data, &costo, &exito);
    if (exito == 1) {
        costoABB->total_baja += costo;
        costoABB->contbaja++;
        if (costo > costoABB->max_baja) costoABB->max_baja = costo;
    }
}


void procesarEvocacion(char* codigo,
    Alumno lso[], int cantLSO, Costos *costoLSO,
    LIBT *libt, int cantLIBT, Costos *costoLIBT,
    arbol *abb, Costos *costoABB) {

    int exito;
    float costo;

    // LSO
    costo = 0.0;
    Evocar(lso, &cantLSO, codigo, &exito, &costo);
    if (exito == 1) {
        costoLSO->total_evoex += costo;
        costoLSO->contevoex++;
        if (costo > costoLSO->max_evoex) costoLSO->max_evoex = costo;
    } else {
        costoLSO->total_evonoex += costo;
        costoLSO->contevonoex++;
        if (costo > costoLSO->max_evonoex) costoLSO->max_evonoex = costo;
    }
    //LIBT
    costo = 0.0;
    evocar(libt, codigo, &exito, &costo, cantLIBT);
    if (exito == 1) {
        costoLIBT->total_evoex += costo;
        costoLIBT->contevoex++;
        if (costo > costoLIBT->max_evoex) costoLIBT->max_evoex = costo;
    } else {
        costoLIBT->total_evonoex += costo;
        costoLIBT->contevonoex++;
        if (costo > costoLIBT->max_evonoex) costoLIBT->max_evonoex = costo;
    }
    //ABB
    costo = 0.0;
    evocarABB(abb, codigo, &exito, &costo);
    if (exito == 1) {
        costoABB->total_evoex += costo;
        costoABB->contevoex++;
        if (costo > costoABB->max_evoex) costoABB->max_evoex = costo;
    } else {
        costoABB->total_evonoex += costo;
        costoABB->contevonoex++;
        if (costo > costoABB->max_evonoex) costoABB->max_evonoex = costo;
    }
}


void Inicializar(
    int *cantLSO, Costos *costoLSO,
    LIBT *libt, int *cantLIBT, Costos *costoLIBT,
    arbol *abb, int *cantABB, Costos *costoABB) {

    *cantLSO = 0;
    memset(costoLSO, 0, sizeof(Costos));

    for (int i = 0; i < *cantLIBT; i++) {
        if (libt->alumnoslibt[i] != NULL) free(libt->alumnoslibt[i]);
    }
    libt->ultimo = -1;
    *cantLIBT = 0;
    memset(costoLIBT, 0, sizeof(Costos));

    free_abb_nodes(abb->raiz);
    init(abb);
    *cantABB = 0;
    memset(costoABB, 0, sizeof(Costos));
}

void free_abb_nodes(nodo *n) {
    if (n == NULL) return;
    free_abb_nodes(n->izquierda);
    free_abb_nodes(n->Derecha);
    free(n);
}


#endif // COMPARACIONES_H_INCLUDED
