/*
  Conclusion del Analisis de Rendimiento:

  ABB (Ganador): Es la más eficiente en todos los aspectos. Su costo de alta es mínimo (0.50)
  al no requerir corrimientos. La baja y la búsqueda son muy eficientes gracias a su
  complejidad logarítmica O(log n).

  LIBT (Intermedio): Representa una mejora clara respecto a la LSO gracias a su búsqueda
  binaria O(log n), pero su rendimiento en altas y bajas se ven afectadas por el costo
  de corrimiento de punteros.

  LSO (Menos eficiente): Es la estructura con el peor rendimiento debido a
  su búsqueda secuencial O(n) y el alto costo de desplazar registros
  completos en cada operación del alta o baja.

   +-----------------------------------------------------------+
   |          CUADRO COMPARATIVO DE COSTOS                     |
   +-----------------------------------------------------------+
   | ESTRUCTURA           | LSO      | LIBT     | ABB      |   |
   +-----------------------------------------------------------+
   | OPERACIONES DE ALTA                                       |
   +-----------------------------------------------------------+
   | Costo Maximo         | 91.00    | 45.50    | 0.50     |   |
   | Costo Promedio       | 23.01    | 11.51    | 0.50     |   |
   +-----------------------------------------------------------+
   | OPERACIONES DE BAJA                                       |
   +-----------------------------------------------------------+
   | Costo Maximo         | 91.00    | 45.50    | 1.50     |   |
   | Costo Promedio       | 22.38    | 11.19    | 0.98     |   |
   +-----------------------------------------------------------+
   | BUSQUEDAS EXITOSAS (EVOEX)                                |
   +----------------------+----------+----------+--------------+
   | Costo Maximo         | 100.00   | 14.00    | 12.00    |   |
   | Costo Promedio       | 45.13    | 11.18    | 6.43     |   |
   +-----------------------------------------------------------+
   | BUSQUEDAS FALLIDAS (EVONOEX)                              |
   +-----------------------------------------------------------+
   | Costo Maximo         | 71.00    | 14.00    | 11.00    |   |
   | Costo Promedio       | 24.18    | 10.32    | 5.85     |   |
   +-----------------------------------------------------------+
   | Alumnos Finales      | 71       | 71       | 71       |   |
   +-----------------------------------------------------------+
 */
#include "LSO.h"
#include "LIBT.h"
#include "ABB.h"
#include "Comparaciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Alumno lso[130];
    LIBT libt;
    arbol abb;
    int cantLSO = 0, cantLIBT = 0, cantABB = 0;
    Costos costoLSO, costoLIBT, costoABB;

    init(&abb);

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
                compararEstructuras(lso, &cantLSO, &costoLSO, &libt, &cantLIBT, &costoLIBT, &abb, &cantABB, &costoABB);
                mostrarResultados(cantLSO, cantLIBT, cantABB, costoLSO, costoLIBT, costoABB);
                break;
            case 2:
                printf("\n----- Contenido LSO -----\n");
                muestralso(lso, cantLSO);
                printf("\n----- Contenido LIBT -----\n");
                muestralibt(&libt, cantLIBT);
                printf("\n----- Contenido ABB  -----\n");
                muestraABB(&abb);
                break;
            case 3:
                printf("Usted a Cerrado el Programa\n");
                break;
            default:
                printf("\nError: Opcion no valida. Intentelo de Nuevo\n");
        }
    } while (opcion != 3);

    return 0;
}

void compararEstructuras(
    Alumno lso[], int *cantLSO, Costos *costoLSO,
    LIBT *libt, int *cantLIBT, Costos *costoLIBT,
    arbol *abb, int *cantABB, Costos *costoABB) {

    Inicializar(cantLSO, costoLSO, libt, cantLIBT, costoLIBT, abb, cantABB, costoABB);

    FILE *fp = fopen("Operaciones-Alumnos.txt", "r");
    if (fp == NULL) {
        printf("Error: No se pudo abrir 'Operaciones-Alumnos.txt'\n");
        return;
    }

    int operacion;
    Alumno alumnoTemp;
    char codigoBuffer[8];

    while (fscanf(fp, "%d\n", &operacion) == 1) {
        switch (operacion) {
            case 1: // Alta
                fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n",
                       alumnoTemp.codigo, alumnoTemp.nombre, alumnoTemp.mail, &alumnoTemp.nota, alumnoTemp.condicion);
                procesarAlta(alumnoTemp, lso, cantLSO, costoLSO, libt, cantLIBT, costoLIBT, abb, cantABB, costoABB);
                break;
            case 2: // Baja
                fscanf(fp, "%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]\n",
                       alumnoTemp.codigo, alumnoTemp.nombre, alumnoTemp.mail, &alumnoTemp.nota, alumnoTemp.condicion);
                procesarBaja(alumnoTemp, lso, cantLSO, costoLSO, libt, cantLIBT, costoLIBT, abb, costoABB);
                break;
            case 3: // Evocación
                fscanf(fp, "%[^\n]\n", codigoBuffer);
                procesarEvocacion(codigoBuffer, lso, *cantLSO, costoLSO, libt, *cantLIBT, costoLIBT, abb, costoABB);
                break;
        }
    }
    fclose(fp);
    printf("Archivo Procesado\n");
}




