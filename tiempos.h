/**
 *
 * Descripcion: Funciones de cabecera para medicion de tiempos 
 *
 * Fichero: tiempos.h
 * Autor: 
 * Version: 1.0
 * Fecha: 11-11-2011
 *
 */

#ifndef TIEMPOS_H
#define TIEMPOS_H

/* constantes */

#define ERR -1
#define OK (!(ERR))

#include "busqueda.h"

/* definiciones de tipos */

typedef struct tiempo {
  int n_ciclos;    /* numero de veces que se repita la medici\'on de tiempos */
  int tamanio;     /* tamanio */
  double tiempo;   /* tiempo promedio */
  double medio_ob; /* numero premedio de veces que se ejecuta la OB */
  int min_ob;      /* minimo de ejecuciones de la OB */
  int max_ob;      /* maximo de ejecuciones de la OB */
} TIEMPO, *PTIEMPO;

/* short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int tamanio, PTIEMPO ptiempo); */

/* short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, 
                                int num_min, int num_max, int incr, int n_perms); */

/*  short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);  */

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, 
                                int orden, char* fichero, 
                                int num_min, int num_max, 
                                int incr, double fclaves, int n_ciclos);

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador,
                              int orden,
                              int tamanio, 
                              double fclaves,
                              int n_ciclos,
                              PTIEMPO ptiempo);


#endif

