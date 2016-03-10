/***********************************************************/
/* Programa: ejercicio2 Fecha:                             */
/* Autores:                                                */
/*                                                         */
/* Programa que escribe en un fichero                      */
/* los tiempos medios del algoritmo de                     */
/* busqueda                                                */
/*                                                         */
/* Entrada: Linea de comandos                              */
/* -num_min: numero minimo de elementos de la tabla        */
/* -num_max: numero minimo de elementos de la tabla        */
/* -incr: incremento                                       */
/* -fclaves: numero de claves a buscar                     */
/* -numP: Introduce el numero de permutaciones a promediar */
/* -fichSalida: Nombre del fichero de salida               */
/*                                                         */
/* Salida: 0 si hubo error                                 */
/*        -1 en caso contrario                             */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ordenar.h"
#include "busqueda.h"
#include "tiempos.h"

int main(int argc, char** argv)
{
  int i, num_min, num_max, incr, n_perms;
  char nombre[256], funcion[32], orden[4], generador[32];
  short ret;
  double fclaves;
 
  srand(time(NULL));

  if (argc != 19) {
    fprintf(stderr, "Error en los parametros de entrada:\n\n");
    fprintf(stderr, "%s -funcion <string> -orden <string> -generador <string> -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -fclaves <double> -numP <int> -fichSalida <string> \n");
    fprintf(stderr, "Donde:\n");
    fprintf(stderr, "-funcion: funcion a usar\n");
    fprintf(stderr, "-orden: orden si o no\n");
    fprintf(stderr, "-generador: normal o potencial\n");
    fprintf(stderr, "-num_min: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-num_max: numero minimo de elementos de la tabla\n");
    fprintf(stderr, "-incr: incremento\n");
    fprintf(stderr, "-fclaves: porcentaje de claves a buscar.\n");
    fprintf(stderr, "-numP: Introduce el numero de permutaciones a promediar\n");
    fprintf(stderr, "-fichSalida: Nombre del fichero de salida\n");
    exit(-1);
  }

  printf("Practica numero 3, apartado 2\n");
  printf("Realizada por: Manuel Reyes y Adrián Bueno\n");
  printf("Grupo: 126\n");

  /* comprueba la linea de comandos */
  for(i = 1; i < argc ; i++) {
    if (strcmp(argv[i], "-funcion") == 0) {
      strcpy(funcion, argv[++i]);
    } else if (strcmp(argv[i], "-orden") == 0) {
      strcpy(orden, argv[++i]);
    } else if (strcmp(argv[i], "-generador") == 0) {
      strcpy(generador, argv[++i]);
    } else if (strcmp(argv[i], "-num_min") == 0) {
      num_min = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-num_max") == 0) {
      num_max = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-incr") == 0) {
      incr = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fclaves") == 0) {
      fclaves = atof(argv[++i]);
    } else if (strcmp(argv[i], "-numP") == 0) {
      n_perms = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-fichSalida") == 0) {
      strcpy(nombre, argv[++i]);
    } else {
      fprintf(stderr, "Parametro %s es incorrecto\n", argv[i]);
      exit(-1);
    }
  }
 
  if (strcmp(orden, "no") == 0 && strcmp(funcion, "bbin") == 0){
    printf("La busqueda binaria requiere datos ordenados");
    exit(-1);
  }

  if (strcmp(orden, "no") == 0 && strcmp(funcion, "bbin_nrec") == 0){
    printf("La busqueda binaria requiere datos ordenados");
    exit(-1);
  }
  

  /* calculamos los tiempos */

  /*No ordenados*/
  if (strcmp(funcion, "blin") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin, generador_claves_uniforme, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin, generador_claves_potencial, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_rec") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin_rec, generador_claves_uniforme, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_rec") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin_rec, generador_claves_potencial, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_auto") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin_auto, generador_claves_uniforme, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_auto") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "no") == 0){
     ret = genera_tiempos_busqueda(blin_auto, generador_claves_potencial, NO_ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);
  
  /*Ordenados*/
  } else if (strcmp(funcion, "blin") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin, generador_claves_uniforme, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin, generador_claves_potencial, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_rec") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin_rec, generador_claves_uniforme, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_rec") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin_rec, generador_claves_potencial, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_auto") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin_auto, generador_claves_uniforme, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "blin_auto") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(blin_auto, generador_claves_potencial, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "bbin") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(bbin, generador_claves_uniforme, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "bbin") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(bbin, generador_claves_potencial, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "bbin_nrec") == 0 && strcmp(generador, "normal") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(bbin_nrec, generador_claves_uniforme, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);

  } else if (strcmp(funcion, "bbin_nrec") == 0 && strcmp(generador, "potencial") == 0 && strcmp(orden, "si") == 0){
     ret = genera_tiempos_busqueda(bbin_nrec, generador_claves_potencial, ORDENADO,  nombre, num_min, num_max, incr, fclaves, n_perms);
  
  /*Errores*/
  } else {
     printf ("Combinacion no adecuada\n");
     printf ("Funciones contempladas:\n bbin\n bbin_nrec \n blin\n blin_rec\n blin_auto\n");
     printf ("Recuerda:\n Orden si o no\n generador normal o potencial");
     exit(-1);
  }

  /*Finalizacion*/
  if (ret == ERR) { 
    printf("Error en la funcion genera_tiempos_busqueda\n");
    exit(-1);
  }

  printf("\n* Salida correcta *\n\n");
  return 0;
}
