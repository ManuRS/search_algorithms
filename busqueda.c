/*********************************************************
*                                                        *
* Fichero: busqueda.c                                    *
* Autores: Manuel Reyes y Adrian Bueno                   *
* Fecha: NOV 2013                                        *
*                                                        *
* Descripcion: Implementacion funciones para busqueda.   *
*                                                        *
*********************************************************/

#include "tiempos.h"
#include "ordenar.h"
#include "busqueda.h"

#include <stdlib.h>
#include <math.h>


/**********************************************************************
*                                                                     *
*                          TAD DICCIONARIO                            *
*                                                                     *
***********************************************************************/


/***************************************************/
/* Funcion:  ini_diccionario                       */
/* Autores:  Manuel Reyes y Adrian Bueno           */
/*                                                 */
/* Crea e inicializa un diccionario.               */
/*                                                 */
/* Entrada:                                        */
/*      - int tamanio: tamanio del diccionario     */
/*      - char orden: ORDENADO / NO_ORDENADO       */
/* Salida:                                         */
/*      - Dirreccion diccionario                   */ 
/*      - NULL si ocurre un error.                 */
/***************************************************/

PDICC ini_diccionario (int tamanio, char orden){

    PDICC pdi = (PDICC) malloc (sizeof(DICC));

    if (tamanio < 0) return NULL;
    if( orden != ORDENADO && orden != NO_ORDENADO ) return NULL;

    pdi->tabla = (int*) malloc (tamanio * sizeof(int));
    pdi-> tamanio = tamanio;
    pdi->orden = orden;
    pdi->n_datos = 0;

	return pdi;
}

/***************************************************/
/* Funcion:  libera_diccionario                    */
/* Autores:  Manuel Reyes y Adrian Bueno           */
/*                                                 */
/* Elimina un diccionario.                         */
/*                                                 */
/* Entrada:                                        */
/*      - PDICC: Direccion de un diccionario.      */
/* Salida:                                         */
/*      - void                                     */
/***************************************************/

void libera_diccionario(PDICC pdicc){

    if (pdicc == NULL) return;

	free(pdicc->tabla);
    free(pdicc);
    return;
}

/***************************************************/
/* Funcion:  inserta_diccionario                   */
/* Autores:  Manuel Reyes y Adrian Bueno           */
/*                                                 */
/* Inserta una clave en un diccionario.            */
/*                                                 */
/* Entrada:                                        */
/*      - PDICC: Direccion de un diccionario.      */
/* Salida:                                         */
/*      - Numero de operaciones basicas (ob)       */
/*      - ERR si ocurre algun error                */
/***************************************************/

int inserta_diccionario(PDICC pdicc, int clave){

    int i, flag=0, ob = 0;

    if (pdicc == NULL) return ERR;
    if (pdicc->n_datos >= pdicc->tamanio) return ERR;

    pdicc->tabla[pdicc->n_datos] = clave;
    ob++;

    if ( pdicc->orden == ORDENADO ) {

        for (i=pdicc->n_datos; i > 0; i--){
            flag=0;
            if( pdicc->tabla[i] < pdicc->tabla[i-1]){
                swap(&(pdicc->tabla[i-1]),&(pdicc->tabla[i]));
                ob++;
                flag=1;
            }
            if (flag==0) i=0;
        }
    }

    pdicc->n_datos++;
    return ob;
}

/*****************************************************/
/* Funcion:  insercion_masiva_diccionario            */
/* Autores:  Manuel Reyes y Adrian Bueno             */
/*                                                   */
/* Inserta N claves en un diccionario.               */
/*                                                   */
/* Entrada:                                          */
/*      - PDICC: Direccion de un diccionario.        */
/*      - int *claves: Claves a insertar.            */
/*      - int n_claves: Numero de claves a insertar. */
/* Salida:                                           */
/*      - Numero de operaciones basicas (ob)         */
/*      - ERR si ocurre algun error                  */
/*****************************************************/

int insercion_masiva_diccionario (PDICC pdicc,int *claves, int n_claves){

    int i, ob;

    if (pdicc == NULL || claves == NULL) return ERR;

    if ( pdicc->orden == ORDENADO ) {
        quicksort_medio(claves, 0, n_claves-1);
    }

    for(i=0; i < n_claves; i++){
        ob = inserta_diccionario(pdicc, claves[i]);
    }

    return ob;
}

/*******************************************************************/
/* Funcion:  busca_diccionario                                     */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario.                              */
/*                                                                 */
/* Entrada:                                                        */
/*      - PDICC pdicc: Direccion de un diccionario.                */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/*      - pfunc_busqueda metodo: funcion para realizar la busqueda */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - ERR si ocurre algun error                                */
/*******************************************************************/

int busca_diccionario(PDICC pdicc, int clave, int * ppos, pfunc_busqueda metodo){

    int ob=0;

    if (pdicc == NULL || ppos == NULL || metodo == NULL) return ERR;

    ob = metodo (pdicc->tabla, 0, pdicc->n_datos, clave, ppos);

    return ob;
}

/***************************************************/
/* Funcion:  imprime_diccionario                   */
/* Autores:  Manuel Reyes y Adrian Bueno           */
/*                                                 */
/* Imprime las claves de un diccionario.           */
/*                                                 */
/* Entrada:                                        */
/*      - PDICC: Direccion de un diccionario.      */
/* Salida:                                         */
/*      - void                                     */
/***************************************************/

void imprime_diccionario(PDICC pdicc){

    int i;

    if (pdicc == NULL) return;

    for (i=0; i < pdicc->n_datos ; i++){
        fprintf(stdout,"%d\n",pdicc->tabla[i]);
    }
    return;
}




/**********************************************************************
*                                                                     *
*                        FUNCIONES DE BUSQUEDA                        *
*                                                                     *
***********************************************************************/



/*******************************************************************/
/* Funcion:  bbin                                                  */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario usando busqueda binaria.      */
/* (con recursion)                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - int * tabla: Direccion de la tabla donde se guardan las  */
/*                     claves del diccionario                      */
/*      - int P: Primera posicion del diccionario donde buscar.    */
/*      - int U: Ultima posicion del diccionario donde buscar.     */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - NO_ENCONTRADO si no ha encontrado la clave a buscar      */
/*******************************************************************/

int bbin (int *tabla,int P,int U,int clave,int * ppos){
   
    int ob = 0;

    if ( tabla == NULL || ppos == NULL ) return ERR;

    return bbin_1 (tabla, P, U-1, clave, ppos, ob);
}

int bbin_1 (int *tabla,int P,int U,int clave,int *ppos, int ob){

    int M = (P+U)/2;

    if (U < P) {
        return NO_ENCONTRADO;
    }
   
    if (tabla[M] == clave){
        ob++; 
        *ppos= M;
        return ob;
    }

    else if (tabla[M] < clave){

         return bbin_1(tabla, M+1, U, clave, ppos, ob+1);
    }
    else {

        return bbin_1(tabla, P, M-1, clave, ppos, ob+1);
    }
}

/*******************************************************************/
/* Funcion:  bbin_rec                                              */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario usando busqueda binaria.      */
/* (sin recursion)                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - int * tabla: Direccion de la tabla donde se guardan las  */
/*                     claves del diccionario                      */
/*      - int P: Primera posicion del diccionario donde buscar.    */
/*      - int U: Ultima posicion del diccionario donde buscar.     */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - NO_ENCONTRADO si no ha encontrado la clave a buscar      */
/*******************************************************************/

int bbin_nrec (int *tabla,int P,int U,int clave,int *ppos){

    int ob = 0;

    return bbin_2 (tabla, P, U-1, clave, ppos, ob);
}

int bbin_2 (int *tabla,int P,int U,int clave,int *ppos, int ob){
    int M;
    
    while (P<=U){
        M=(P+U)/2;
        if(tabla[M]==clave){
            ob++;
            *ppos = M;
            return ob;
        }
        else if(tabla[M]<clave){
            P=M+1;
            ob++;
        }
        else {
            U=M-1;
            ob++;
        }
    } 
    return NO_ENCONTRADO;
}

/*******************************************************************/
/* Funcion:  blin                                                  */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario usando busqueda lineal.       */
/* (sin recursion)                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - int * tabla: Direccion de la tabla donde se guardan las  */
/*                     claves del diccionario                      */
/*      - int P: Primera posicion del diccionario donde buscar.    */
/*      - int U: Ultima posicion del diccionario donde buscar.     */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - NO_ENCONTRADO si no ha encontrado la clave a buscar      */
/*******************************************************************/

int blin(int *tabla,int P,int U,int clave,int *ppos){

	int i,ob=0;
	int n_datos = U-P;

	for(i=0; i<n_datos; i++){
		ob++;
		if(clave == tabla[i]){
			*ppos= i;
			return ob;
		}	
	}
	return NO_ENCONTRADO;
}

/*******************************************************************/
/* Funcion:  blin_rec                                              */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario usando busqueda lineal.       */
/* (con recursion)                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - int * tabla: Direccion de la tabla donde se guardan las  */
/*                     claves del diccionario                      */
/*      - int P: Primera posicion del diccionario donde buscar.    */
/*      - int U: Ultima posicion del diccionario donde buscar.     */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - NO_ENCONTRADO si no ha encontrado la clave a buscar      */
/*******************************************************************/

int blin_rec(int *tabla,int P,int U,int clave,int *ppos){

	if(P>U){
		return NO_ENCONTRADO;
	}
	else if(clave == tabla[P]){
		*ppos = P;
		return 1; /*ob*/
	}
	else
		return blin_rec(tabla,P+1,U,clave,ppos)+1;
}

/*******************************************************************/
/* Funcion:  blin_auto                                             */
/* Autores:  Manuel Reyes y Adrian Bueno                           */
/*                                                                 */
/* Busca una clave en un diccionario usando busqueda lineal        */
/* automatizada. Las claves mas buscadas se iran moviendo a las    */
/* posiciones mas bajas para encontrarlas mas rapido.              */
/* (sin recursion)                                                 */
/*                                                                 */
/* Entrada:                                                        */
/*      - int * tabla: Direccion de la tabla donde se guardan las  */
/*                     claves del diccionario                      */
/*      - int P: Primera posicion del diccionario donde buscar.    */
/*      - int U: Ultima posicion del diccionario donde buscar.     */
/*      - int clave: Clave a buscar                                */
/*      - int * ppos: Aqui se guarda la posicion en donde          */
/*                  se encuentra la clave en el diccionario.       */
/* Salida:                                                         */
/*      - Numero de operaciones basicas (ob)                       */
/*      - NO_ENCONTRADO si no ha encontrado la clave a buscar      */
/*******************************************************************/

int blin_auto(int *tabla,int P,int U,int clave,int *ppos){

	int i,ob=0;
	int n_datos = U-P;

	for(i=0; i<n_datos; i++){
		ob++;
		if(clave == tabla[i]){	
                        if(i>0) {
                            swap(&tabla[i],&tabla[i-1]);
                            i = i-1;
                            *ppos = i;
                        };
                        *ppos= i;
			return ob;
		}	
	}
	return NO_ENCONTRADO;
}



/**************************************************************************
 *  Funciones de geracion de claves
 *
 *  Descripcion: Recibe el numero de claves que hay que generar
 *               en el parametro n_claves. Las claves generadas
 *               iran de 1 a max. Las claves se devuelven en 
 *               el parametro claves que se debe reservar externamente
 *               a la funcion.
 **************************************************************************/
  
/********************************************************************************
 *  Funcion: generador_claves_uniforme
 *               Esta fucnion genera todas las claves de 1 a max de forma 
 *               secuencial. Si n_claves==max entonces se generan cada clave
 *               una unica vez.
 *********************************************************************************/
void generador_claves_uniforme(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) claves[i] = 1 + (i % max);

  return;
}

/*********************************************************************************
 *  Funcion: generador_claves_potencial
 *               Esta funcion genera siguiendo una distribucion aproximadamente
 *               potencial. Siendo los valores mas pequenos mucho mas probables
 *               que los mas grandes. El valor 1 tiene una probabilidad del 50%,
 *               el dos del 17%, el tres el 9%, etc.
 *********************************************************************************/
void generador_claves_potencial(int *claves, int n_claves, int max)
{
  int i;

  for(i = 0; i < n_claves; i++) {
    claves[i] = (1+max) / (1 + max*((double)rand()/RAND_MAX));
  }

  return;
}

