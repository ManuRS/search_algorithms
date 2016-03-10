
/**
 *
 * Descripcion: Funciones de cabecera para busqueda 
 *
 * Fichero: busqueda.h
 * Autor: 
 * Version: 1.0
 * Fecha: 22-09-2011
 *
 */

#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_

/* constantes */

#define NO_ENCONTRADO -2

#define ORDENADO 1
#define NO_ORDENADO 0

/* definiciones de tipos */
typedef struct diccionario {
  int tamanio; /* tamano de la tabla */
  int n_datos; /* numero de datos en la tabla */
  char orden;  /* tabla ordenada o desordenada */
  int *tabla;  /* tabla de datos */
} DICC, *PDICC;

typedef int (* pfunc_busqueda)(int*, int, int, int, int*);
typedef void (* pfunc_generador_claves)(int*, int, int);

/* TAD Diccionario */
PDICC ini_diccionario (int tamanio, char orden);
void libera_diccionario(PDICC pdicc);
int inserta_diccionario(PDICC pdicc, int clave);
int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves);
int busca_diccionario(PDICC pdicc, int clave, int *ppos, pfunc_busqueda metodo);
void imprime_diccionario(PDICC pdicc);

/* Funcoiones de busqueda del TAD Diccionario */
int bbin(int *tabla,int P,int U,int clave,int *ppos);
int bbin_nrec(int *tabla,int P,int U,int clave,int *ppos);
int bbin_1 (int *tabla,int P,int U,int clave,int *ppos, int acc);
int bbin_2 (int *tabla,int P,int U,int clave,int *ppos, int acc);

int blin(int *tabla,int P,int U,int clave,int *ppos);
int blin_auto(int *tabla,int P,int U,int clave,int *ppos);
int blin_rec(int *tabla,int P,int U,int clave,int *ppos);

/**
 *  Funciones de geracion de claves
 *
 *  Descripcion: Reciben el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               van de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 *
 */
void generador_claves_uniforme(int *claves, int n_claves, int max);
void generador_claves_potencial(int *claves, int n_claves, int max);

#endif

