#include <stdio.h>
#include <stdlib.h>
#include "LSO.h"
int main()
{
    Alumno *alumnoLSO = (Alumno*)malloc(sizeof(Alumno)*130); // LSO
    int cant = 0;
    int exito = 0;
    char codigo[7];

void mostrar_menu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE GESTION DE ALUMNOS\n");
    printf("   Estructura de Datos y Algoritmos I - 2025\n");
    printf("========================================\n");
    printf("1. Memorizacion Previa (cargar desde archivo)\n");
    printf("2. Ingresar nuevo alumno\n");
    printf("3. Eliminar alumno\n");
    printf("4. Modificar datos de alumno\n");
    printf("5. Consultar informacion de alumno\n");
    printf("6. Mostrar Estructura completa\n");
    printf("0. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opcion: ");
}

void limpiar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

    int opcion;
    int resultado;

    do {
        mostrar_menu();
        if (scanf("%d", &opcion) != 1) {
            printf("\nError: Ingrese un numero valido.\n");
            limpiar_buffer();
            continue;
        }
        limpiar_buffer();

        switch(opcion) {
            case 1:
                printf("\n--- MEMORIZACION PREVIA ---\n");
                resultado = memorizacion_previa(alumnoLSO,&cant,&exito);
                printf("Cantidad de alumnos cargados: %d\n",cant);
                if (resultado == 1) {
                    printf("Archivo cargado exitosamente\n");
                } else {
                    printf("Error al cargar el archivo 'Alumnos.txt'\n");
                }
                break;

            case 2:
                printf("\n--- INGRESAR NUEVO ALUMNO ---\n");
                Alumno aux;
                Ingreso(&aux);
                Alta(alumnoLSO,aux, &cant, &exito);
               // resultado = ingresar_alumno(&alumnoLSO);
                if (resultado == 1) {
                    printf("Alumno ingresado exitosamente\n");
                } else {
                    printf("Error al ingresar el alumno\n");
                }
                break;

            case 3:
                printf("\n--- ELIMINAR ALUMNO ---\n");
                printf("ingrese el codigo del alumno para eliminar\n");
                scanf("%s", codigo);
                Baja(alumnoLSO,codigo,&cant,&exito);
                if (exito == 1) {
                    printf("Alumno eliminado exitosamente\n");
                } else {
                    printf("Error al eliminar el alumno\n");
                }
                break;

            case 4:
                printf("\n--- MODIFICAR ALUMNO ---\n");
                printf("ingrese el codigo del alumno para modificar\n");
                scanf("%s", codigo);
                Modificar(alumnoLSO,&cant,codigo,&exito);
                if (exito == 1) {
                    printf("Datos del alumno modificados exitosamente\n");
                } else {
                    printf("Error al modificar al alumno\n");
                }
                break;

            case 5:
                printf("\n--- CONSULTAR ALUMNO ---\n");
              //  resultado = consultar_alumno(&alumnoLSO);
                if (resultado == 0) {
                    printf("Alumno no encontrado\n");
                }
                break;

            case 6:
                printf("\n--- MOSTRAR ESTRUCTURA COMPLETA ---\n");
                muestra(alumnoLSO,cant);
                break;

            case 0:
                printf("\nUsted a cerrado el programa correctamente\n");
                break;

            default:
                printf("\nOpcion no valida. Por favor seleccione una opcion del 0 al 6\n");
                break;
        }

        if (opcion != 0) {
            printf("\nPresione Enter para continuar...");
            getchar();
        }

    } while(opcion != 0);

    return 0;
}
