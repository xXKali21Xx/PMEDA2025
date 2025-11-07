/*
    Conclusion del Analisis de Rendimiento:

    RS (Ganador): Es la estructura más eficiente en esta comparación de estructuras. En búsquedas muestra un rendimiento superior, ya que solo
    recorre listas enlazadas cortas en lugar de sondear un arreglo completo. Al evitar el clustering propio del direccionamiento abierto,
    mantiene costos promedio y máximos bajos y estables, incluso con factores de carga mayores a 1.

    RAC (Intermedio): Mejora notablemente respecto a RAL gracias al sondeo cuadrático, que reduce el agrupamiento primario y
    evita largas secuencias de celdas ocupadas. Sin embargo, no es efectivo al agrupamiento secundario, y
    su rendimiento se degrada más que el de RS a medida que aumenta el factor de carga.

    RAL (Menor eficiencia): Es la estructura con peor rendimiento. El sondeo lineal genera agrupamiento primario,
    formando bloques densos de colisiones que disparan los costos de búsqueda. Las secuencias de sondeo se vuelven extensas,
    elevando tanto el costo promedio como el máximo, incluso para búsquedas fallidas.

    +------------------------------------+-----------+-----------+-----------+
    |        CUADRO COMPARATIVO DE COSTOS DE LA EVOCACION                    |
    +------------------------------------+-----------+-----------+-----------+
    | ESTRUCTURA                         | RAL       | RAC       | RS        |
    +------------------------------------+-----------+-----------+-----------+
    | BUSQUEDAS EXITOSAS                                                     |
    +------------------------------------+-----------+-----------+-----------+
    | Costo Maximo                       | 81.00     | 11.00     | 6.00      |
    | Costo Promedio                     | 16.47     | 3.81      | 2.74      |
    +------------------------------------+-----------+-----------+-----------+
    | BUSQUEDAS FALLIDAS                                                     |
    +------------------------------------+-----------+-----------+-----------+
    | Costo Maximo                       | 94.00     | 12.00     | 4.00      |
    | Costo Promedio                     | 70.31     | 9.05      | 1.79      |
    +------------------------------------+-----------+-----------+-----------+
 */
#include "RAL.h"
#include "RAC.h"
#include "RS.h"
#include "Comparaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    rebalse estructuraRAL;
    rebalse estructuraRAC;
    RS estructuraRS[maxRAL];

    Costos costoRAL, costoRAC, costoRS;

    iniRAL(&estructuraRAL);
    iniRAC(&estructuraRAC);
    initRS(estructuraRS);

    int opcion;
    do {
        printf("\n+------------------------------+\n");
        printf("|        MENU PRINCIPAL        |\n");
        printf("+------------------------------+\n");
        printf("| 1. Comparar Estructuras      |\n");
        printf("| 2. Mostrar Contenidos        |\n");
        printf("| 3. Salir del Programa        |\n");
        printf("+------------------------------+\n");
        printf("Ingrese su opcion: ");
        scanf("%d", &opcion);
        getchar();
        switch (opcion) {
            case 1:
                ComparacionEstruct(&estructuraRAL, &estructuraRAC, estructuraRS,&costoRAL, &costoRAC, &costoRS);
                mostrarResultados(costoRAL, costoRAC, costoRS);
                break;
            case 2:
                printf("\n---- Contenido Rebalse Abierto Lineal ----\n");
                muestraRAL(estructuraRAL);
                printf("\n---- Contenido Rebalse Abierto Cuadratico ----\n");
                muestraRAC(estructuraRAC);
                printf("\n----- Contenido Rebalse Separado ----\n");
                muestraRS(estructuraRS);
                break;
            case 3:
                printf("Usted a Cerrado el Programa\n");
                break;
            default:
                printf("\nError: Opcion no valida. Intentelo de Nuevo\n");
        }
    } while (opcion != 0);

    return 0;
}




