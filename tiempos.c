/*****************************************************
*                                                    *
* Fichero: tiempos.c                                 *
* Autor: Manuel Reyes y Adrian Bueno                 *
* Fecha: NOV 2013                                    *
*                                                    *
* Descripcion: Funciones para medicion de tiempos    *
*                                                    *
******************************************************/

#include "tiempos.h"
#include "ordenar.h"
#include "busqueda.h"


/*******************************************************************/
/* Funcion:  genera_tiempos_busqueda                               */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Funcion para preparar los datos enviados a                      */
/* tiempo_medio_busqueda asi como controlar                        */
/* el numero de llamadas.                                          */
/* Tambien llama a guarda_tabla_tiempos para                       */
/* almacenar los datos.                                            */
/*                                                                 */
/* Entrada:                                                        */
/*      - pfunc_busqueda metodo: puntero a la funcion de busqueda  */
/*      - pfunc_generador_claves generador: pt a func que genera claves    */
/*      - int orden: indica si el diccionario sera ordenado o no   */
/*      - char* fichero: donde guardar los datos                   */
/*      - int num_min: Tamaño minimo de diccionario                */
/*      - int num_max: Tamaño maximo de diccionario                */
/*      - int incr: Incremento tamaño de diccionario               */
/*      - double fclaves: factor que indica cuantas claves buscar  */
/* Salida:                                                         */
/*      - OK                                                       */
/*      - ERR si ocurre algun error                                */
/*******************************************************************/

short genera_tiempos_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden, char* fichero, int num_min, int num_max, int incr, double fclaves, int n_ciclos){

    PTIEMPO ptiempo;
    int tamanio;
    int i,j;

    if(metodo == NULL || generador == NULL || fichero == NULL || num_min<0 || num_max < num_min || incr < 1 || fclaves < 1 || n_ciclos < 1) return ERR;

    tamanio = ((num_max - num_min)/incr)+1;
    ptiempo = (PTIEMPO) malloc (tamanio * sizeof (TIEMPO));
    if (ptiempo == NULL) return ERR;

    for (i=num_min, j=0; j<tamanio; i+=incr, j++){
        if (tiempo_medio_busqueda(metodo,generador, orden, i, fclaves, n_ciclos, &ptiempo[j]) == ERR){
            free(ptiempo);
            return ERR;
        }
    }
    if (guarda_tabla_tiempos(fichero, ptiempo, tamanio) == ERR){
        free(ptiempo);
        return ERR;
    }

    free(ptiempo);
    return OK;
}

/*******************************************************************/
/* Funcion:  tiempo_medio_busqueda                                 */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/*                                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - pfunc_busqueda metodo: puntero a la funcion de busqueda  */
/*      - pfunc_generador_claves generador: pt a func que genera claves    */
/*      - int orden: indica si el diccionario sera ordenado o no   */
/*      - int tamanio: numero del diccionario                      */
/*      - double fclaves: factor que indica cuantas claves buscar  */
/*      - PTIEMPO ptiempo: estructura donde guardad datos          */
/* Salida:                                                         */
/*      - OK                                                       */
/*      - ERR si ocurre algun error                                */
/*******************************************************************/

short tiempo_medio_busqueda(pfunc_busqueda metodo, pfunc_generador_claves generador, int orden,int tamanio, double fclaves, int n_ciclos, PTIEMPO ptiempo){

	int * perm;
	PDICC pdicc;
	clock_t ini, fin;
	int ob=0;
	unsigned int acc=0;
	int max_ob=0;
	int min_ob=INT_MAX;
	int i,j;
	int pos;
	int * claves;
	int n_claves = tamanio * fclaves;

	if(metodo==NULL || n_ciclos<1 || tamanio<1 || ptiempo==NULL)
		return ERR;


	/*Crear diccionario*/

	pdicc = ini_diccionario(tamanio,orden);

	if (pdicc == NULL){
		printf("\nERROR al reservar memoria para el diccionario.\n");
		return ERR;
	}

	/*Generar claves para el diccionario.*/

	perm = genera_perm(tamanio);

	if (perm == NULL) {
		printf("ERROR al generar las claves para el diccionario.\n");
		libera_diccionario(pdicc);
		return ERR;
	}
	
	/*Insertar claves en el diccionario.*/

	ob = insercion_masiva_diccionario(pdicc, perm, tamanio);

	if (ob == ERR) {
		printf("\nERROR al insertar claves en el diccionario.\n");
		free(perm);
		libera_diccionario(pdicc);
		return ERR;
	}

	/*Generar claves a buscar en el diccionario.*/

	claves = (int*) malloc ( n_claves * sizeof(int) );

	if (claves == NULL){
		printf("ERROR al reservar memoria para las claves a buscar.");
		libera_diccionario(pdicc);
		free(perm);		
		return ERR;
	}

	generador(claves, n_claves, tamanio-1);


	/*Buscar en el diccionario las claves generadas.*/
	ini = clock();

	for (j=0; j < n_ciclos; j++){
		for (i=0; i< n_claves; i++) {

                        ob=0;
			ob = busca_diccionario (pdicc, claves[i], &pos, metodo);
			if(ob == NO_ENCONTRADO || ob<0){
				free(claves);
				free(perm);
				libera_diccionario(pdicc);		
				return ERR;
			}
			acc+=ob;
			if(acc<0){
			    printf("n_ciclo: %d/%d\n", j, n_ciclos);
			    printf("n_clave: %d/%d\n", i, n_claves);
			    printf("clave:   %d\n", claves[i]);
			    printf("Overflow de acc");
			}
			if(ob>max_ob) max_ob=ob;
			if(ob<min_ob) min_ob=ob; 
		}
	}
	fin= clock();

	/*Guardar datos.*/

	ptiempo->tiempo = (double) (fin-ini)/(n_claves*n_ciclos)/CLOCKS_PER_SEC;
	ptiempo->n_ciclos = n_ciclos;
	ptiempo->tamanio = tamanio;
	ptiempo->medio_ob = (double) acc/n_claves/n_ciclos;
	ptiempo->min_ob = min_ob;
	ptiempo->max_ob = max_ob;

	/*Finalizacion y liberizacion de memoria*/

	free(perm);
	libera_diccionario(pdicc);
	free(claves);

	return OK;
}