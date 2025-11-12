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

void inicializarCostos(Costos *c) {
    c->total_evoex = 0;
    c->max_evoex = 0;
    c->contevoex = 0;
    c->total_evonoex = 0;
    c->max_evonoex = 0;
    c->contevonoex = 0;
}

void ComparacionEstruct(rebalse *ral, rebalse *rac, RS rs[],
                         Costos *costoRAL, Costos *costoRAC, Costos *costoRS) {
    iniRAL(ral);
    iniRAC(rac);
    initRS(rs);
    inicializarCostos(costoRAL);
    inicializarCostos(costoRAC);
    inicializarCostos(costoRS);

    FILE *fp = fopen("Operaciones-Alumno.txt", "r");
    if (fp == NULL) {
        perror("Error al abrir el archivo 'Operaciones-Alumnos.txt'");
        return;
    }

    int codigoOperador;
    Alumno aux;
    int exito;
    float costo;

    while (fscanf(fp, "%d", &codigoOperador) == 1) {
        switch (codigoOperador) {
            case 1: // Alta
                fscanf(fp, " %[^\n]", aux.codigo);
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.mail);
                fscanf(fp, "%d", &aux.nota);
                fscanf(fp, " %[^\n]", aux.condicion);

                AltaRAL(ral, aux, &costo, &exito);
                AltaRAC(rac, aux, &exito);
                AltaRS(rs, aux, &exito, &costo);
                break;

            case 2: // Baja
                fscanf(fp, " %[^\n]", aux.codigo);
                fscanf(fp, " %[^\n]", aux.nombre);
                fscanf(fp, " %[^\n]", aux.mail);
                fscanf(fp, "%d", &aux.nota);
                fscanf(fp, " %[^\n]", aux.condicion);

                BajaRAL(ral, aux, &exito);
                BajaRAC(rac, aux, &exito);
                BajaRS(rs, aux, &exito);
                break;

            case 3: // Evocaci�n
                fscanf(fp, " %[^\n]", aux.codigo);

                Alumno aluEvocada;

                // RAL
                costo = 0;
                exito = 0;
                EvocarRAL(*ral, aux.codigo, &aluEvocada, &exito, &costo);

                if (exito) {
                    costoRAL->total_evoex += costo;
                    costoRAL->contevoex++;
                    if (costo > costoRAL->max_evoex) costoRAL->max_evoex = costo;
                } else {
                    costoRAL->total_evonoex += costo;
                    costoRAL->contevonoex++;
                    if (costo > costoRAL->max_evonoex) costoRAL->max_evonoex = costo;
                }

                // RAC
                costo = 0;
                exito = 0;
                EvocarRAC(*rac, aux.codigo,&aluEvocada,&exito, &costo);

                if (exito) {
                    costoRAC->total_evoex += costo;
                    costoRAC->contevoex++;
                    if (costo > costoRAC->max_evoex) costoRAC->max_evoex = costo;
                } else {
                    costoRAC->total_evonoex += costo;
                    costoRAC->contevonoex++;
                    if (costo > costoRAC->max_evonoex) costoRAC->max_evonoex = costo;
                }

                // RS
                costo = 0;
                exito = 0;
                EvocarRS(rs, aux.codigo, &aluEvocada, &exito, &costo);

                if (exito) {
                    costoRS->total_evoex += costo;
                    costoRS->contevoex++;
                    if (costo > costoRS->max_evoex) costoRS->max_evoex = costo;
                } else {
                    costoRS->total_evonoex += costo;
                    costoRS->contevonoex++;
                    if (costo > costoRS->max_evonoex) costoRS->max_evonoex = costo;
                }
                break;

            default:
                printf("Error: Codigo de Operacion no Reconocido: %d\n", codigoOperador);
                break;
        }
    }

    fclose(fp);
    printf("Archivo Procesado\n");
}

void mostrarResultados(Costos ral, Costos rac, Costos rs) {
    printf("\n+------------------------------------+-----------+-----------+-----------+\n");
    printf("|        CUADRO COMPARATIVO DE COSTOS DE LA EVOCACION                    |\n");
    printf("+------------------------------------+-----------+-----------+-----------+\n");
    printf("| ESTRUCTURA                         | %-9s | %-9s | %-9s |\n", "RAL", "RAC", "RS");
    printf("+------------------------------------+-----------+-----------+-----------+\n");
    printf("| BUSQUEDAS EXITOSAS                                                     |\n");
    printf("+------------------------------------+-----------+-----------+-----------+\n");
    printf("| Costo Maximo                       | %-9.2f | %-9.2f | %-9.2f |\n",
           ral.max_evoex, rac.max_evoex, rs.max_evoex);
    printf("| Costo Promedio                     | %-9.2f | %-9.2f | %-9.2f |\n",
           (ral.contevoex > 0 ? ral.total_evoex / ral.contevoex : 0),
           (rac.contevoex > 0 ? rac.total_evoex / rac.contevoex : 0),
           (rs.contevoex > 0 ? rs.total_evoex / rs.contevoex : 0));
    printf("+------------------------------------+-----------+-----------+-----------+\n");
    printf("| BUSQUEDAS FALLIDAS                                                     |\n");
    printf("+------------------------------------+-----------+-----------+-----------+\n");
    printf("| Costo Maximo                       | %-9.2f | %-9.2f | %-9.2f |\n",
           ral.max_evonoex, rac.max_evonoex, rs.max_evonoex);
    printf("| Costo Promedio                     | %-9.2f | %-9.2f | %-9.2f |\n",
           (ral.contevonoex > 0 ? ral.total_evonoex / ral.contevonoex : 0),
           (rac.contevonoex > 0 ? rac.total_evonoex / rac.contevonoex : 0),
           (rs.contevonoex > 0 ? rs.total_evonoex / rs.contevonoex : 0));
    printf("+------------------------------------+-----------+-----------+-----------+\n");
}

#endif // COMPARACIONES_H_INCLUDED
