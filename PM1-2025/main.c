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

                printf("Ingrese el nombre y apellido del alumno \n");
                scanf(" %[^\n]", aux.nombre);
                fflush(stdin);
                printf("Ingrese el mail del alumno \n");
                scanf(" %[^\n]", aux.mail);
                fflush(stdin);
                printf("Ingrese el codigo del alumno\n");
                scanf(" %[^\n]", aux.codigo);
                fflush(stdin);
                printf("Ingrese la condicion del alumno\n");
                scanf(" %[^\n]", aux.condicion);
                fflush(stdin);
                printf("Ingrese la nota del alumno \n");
                scanf("%d", &aux.nota);
                fflush(stdin);

                Alta(alumnoLSO,aux, &cant, &exito);
               // resultado = ingresar_alumno(&alumnoLSO);
               if(exito == -1){
                printf("La lista esta llena \n");
               }
                if (exito == 1) {
                    printf("Alumno ingresado exitosamente\n");
                } else {
                    printf("Error al ingresar el alumno\n");
                }
                break;

            case 3:
                if(cant == 0){
                    printf("no hay elementos en la lista \n");
                    break;
                }
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
                if(cant == 0){
                    printf("no hay elementos en la lista \n");
                    break;
                }
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

            case 5: if (cant == 0) {
                        printf("no hay elementos en la lista.\n");
                        break;
                    }
                    printf("\n--- CONSULTAR ALUMNO ---\n");
                    printf("Ingrese el codigo del alumno a consultar: \n");
                    scanf("%s", codigo);
                    limpiar_buffer();

                    Alumno* alumno_encontrado = Evocar(alumnoLSO, &cant, codigo, &exito);

                    if (exito == 1 && alumno_encontrado != NULL) {
                        printf("\n=== INFORMACION DEL ALUMNO ===\n");
                        printf("Codigo: %s\n", alumno_encontrado->codigo);
                        printf("Nombre y Apellido: %s\n", alumno_encontrado->nombre);
                        printf("Mail: %s\n", alumno_encontrado->mail);
                        printf("Condicion: %s\n", alumno_encontrado->condicion);
                        printf("Nota: %d\n", alumno_encontrado->nota);
                        printf("================================\n");
                    } else {
                        printf("Error: Alumno no encontrado\n");
                    }
                    break;

            case 6:
                if(cant == 0){
                    printf("No hay elementos en la lista \n");
                    break;
                }
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
