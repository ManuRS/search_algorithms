/**
 *
 * Descripcion: Funciones de cabecera para ordenacion 
 *
 * Fichero: ordenar.h
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

#ifndef ORDENA_H
#define ORDENA_H

/* constantes */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include "tiempos.h"

#define ERR -1
#define OK (!(ERR))

/* definiciones de tipos */

typedef int (* pfunc_ordena)(int*, int, int);

typedef int (* pfunc_pivote)(int*, int, int);

/* Funciones */

/*Practica 1*/
int aleat_num(int inf, int sup);
int* genera_perm(int n);
int** genera_permutaciones(int n_perms, int tamanio);

int BubbleSortSinFlag(int* tabla, int ip, int iu);
int BubbleSort(int* tabla, int ip, int iu);

short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms,int tamanio, PTIEMPO ptiempo);
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms);
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N);

void swap(int* a, int* b);

/*Practica 2*/
int mergesort(int* tabla, int ip, int iu);
int merge(int* tabla, int ip, int iu, int imedio);
int CopiarTabla(int *TablaAux, int *tabla, int ip, int iu);

int quicksort_medio(int* tabla, int ip, int iu);
int quicksort_rand(int* tabla, int ip, int iu);
int quicksort_stat(int* tabla, int ip, int iu);

int quicksort(int* tabla, int ip, int iu, pfunc_pivote pivote);
int partir(int* tabla, int ip, int iu, pfunc_pivote pivote , int * m);

int medio(int *tabla, int ip, int iu);
int medio_rand(int *tabla, int ip, int iu);
int medio_stat(int *tabla, int ip, int iu);

#endif
