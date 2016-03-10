  /**************************************************************
 *                                                             *
 * Descripcion: Implementacion de funciones de ordenacion      *
 *                                                             *
 * Fichero: ordenar.c                                          *
 * Autores: Manuel Reyes y Adrian Bueno                        *
 * Version: 2.0                                                *
 *                                                             *
 * Fecha: 25-09-2013                                           *
 *                                                             *
 **************************************************************/

#include "tiempos.h"
#include "ordenar.h"
#include "busqueda.h"


/**********************************************************************
*                                                                     *
*                          PRACTICA 1                                 *
*                                                                     *
***********************************************************************/


/***************************************************/
/* Funcion: aleat_num Fecha:   25-09-2013          */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Rutina que genera un numero aleatorio           */
/* entre dos numeros dados                         */
/* Consultar captulo 7 (Random Numbers)            */
/* Numerical recipes in C:                         */
/* the art of scientic computing"                  */
/*                                                 */
/* Entrada:                                        */
/* int inf: limite inferior                        */
/* int sup: limite superior                        */
/* Salida:                                         */
/* int: numero aleatorio                           */
/***************************************************/
int aleat_num(int inf, int sup)
{
  return inf+rand()%(sup-inf+1);
}

/***************************************************/
/* Funcion: genera_perm Fecha:   29-09-2013        */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Rutina que genera una permutacion               */
/* aleatoria                                       */
/*                                                 */
/* Entrada:                                        */
/* int n: Numero de elementos de la                */
/* permutacion                                     */
/* Salida:                                         */
/* int *: puntero a un array de enteros            */
/* que contiene a la permutacion                   */
/* o NULL en caso de error                         */
/***************************************************/
int* genera_perm(int n)
{  
  int i;
  int* perm = (int*) malloc (n * sizeof(perm[0]));
  if(perm == NULL)
     return NULL;
  
  for(i=0;i<n;i++)
      perm[i]=i+1;
  
  for(i=0;i<n;i++)
      swap (&perm[i], &perm[aleat_num(i, n-1)]);
     
  return perm;  
}

/***************************************************/
/* Funcion: genera_permutaciones Fecha: 2-10-2013  */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Funcion que genera n_perms permutaciones        */
/* aleatorias de tamanio elementos                 */
/*                                                 */
/* Entrada:                                        */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Numero de elementos de cada        */
/* permutacion                                     */
/* Salida:                                         */
/* int**: Array de punteros a enteros              */
/* que apuntan a cada una de las                   */
/* permutaciones                                   */
/* NULL en caso de error                           */
/***************************************************/
int** genera_permutaciones(int n_perms, int tamanio)
{
  int i;
  int** perms = (int**) malloc (n_perms * sizeof(perms[0]));
  if (perms == NULL)
       return NULL;
  
  for(i=0; i < n_perms; i++){
       perms[i] = genera_perm(tamanio);
       if (perms[i] == NULL){
            int j;
            for (j=0 ; j<i ; i++)
            	free (perms[j]);
            free(perms);
            return NULL;
       }
  }
  return perms;
}

/***************************************************/
/* Funcion: BubbleSortSinFlag   Fecha: 2-10-2013   */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Funcion que ordena mediante el metodo de        */
/* comparacion de la burbuja.                      */
/* Version sin Flag que no comprueba que en un     */
/* determinado momento los elementos ya esten      */
/* ordenados.                                      */
/* Documentacion:                                  */
/* es.wikipedia.org/wiki/Ordenamiento_de_burbuja   */
/*                                                 */         
/* Entradas:                                       */
/* int* tabla: puntero a la tabla a ordenar        */
/* int ip: Indice inferior desde el que ordenar    */
/* int iu: Indice hasta el que ordenar             */
/* Salida:                                         */
/* Cont: Numero de veces que se realizo la OB      */
/* ERR en caso de error                            */
/***************************************************/
int BubbleSortSinFlag(int* tabla, int ip, int iu)
{
  int i,j;
  int cont=0;

  if (tabla == NULL)
      return ERR;

  for (i=iu; i>ip; i--){
      for (j=ip; j<i; j++){
          cont++;
          if (tabla[j]>tabla[j+1]){
             swap(&tabla[j],&tabla[j+1]);
          }
      }
  } 
  return cont;
}

/***************************************************/
/* Funcion: BubbleSort          Fecha: 3-10-2013   */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Funcion que ordena mediante el metodo de        */
/* comparacion de la burbuja.                      */
/* Version con Flag que comprueba que en un        */
/* determinado momento los elementos ya esten      */
/* ordenados.                                      */
/* Documentacion:                                  */
/* es.wikipedia.org/wiki/Ordenamiento_de_burbuja   */
/*                                                 */         
/* Entradas:                                       */
/* int* tabla: puntero a la tabla a ordenar        */
/* int ip: Indice inferior desde el que ordenar    */
/* int iu: Indice hasta el que ordenar             */
/* Salida:                                         */
/* Cont: Numero de veces que se realizo la OB      */
/* ERR en caso de error                            */
/***************************************************/
int BubbleSort(int* tabla, int ip, int iu)
{
  int i,j;
  int flag=1;
  int cont=0;

  if (tabla == NULL)
      return ERR;

  for (i=iu; i>ip && flag==1; i--){
      flag=0;
      for (j=ip; j<i; j++){
          cont++;
          if (tabla[j]>tabla[j+1]){
             swap(&tabla[j],&tabla[j+1]);
             flag=1;
          }
      }
  } 
  return cont;
}

/***************************************************/
/* Funcion: tiempo_medio_ordenacion                */
/* Fecha: 2-10-2013                                */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Funcion que mide diversos datos para el         */
/* analisis de un algoritmo, como son:             */
/* Tiempo total, Media_num_ob,                     */
/* Minimo_num_ob y Max_num_ob                      */
/*                                                 */         
/* Entradas:                                       */
/* pfunc_ordena metodo: referencia a funcion que   */
/*                      va a ordenar               */
/* int n_perms: Numero de permutaciones            */
/* int tamanio: Tamaño de las permutaciones        */
/* PTIEMPO ptiempo: estructura donde almacenar     */
/*                  datos, definida en ordenar.h   */
/* Salida:                                         */
/* OK si no hay errores                            */
/* ERR en caso de error                            */
/***************************************************/
short tiempo_medio_ordenacion(pfunc_ordena metodo, int n_perms, int tamanio, PTIEMPO ptiempo)
{
  int ** perms; 
  clock_t ini, fin;
  int ob=0;
  int acc=0;
  int max_ob=0;
  int min_ob=INT_MAX;
  int i;
  if(metodo==NULL || n_perms<1 || tamanio<1 || ptiempo==NULL)
        return ERR;

/*Generar permutaciones a calcular*/
  perms = genera_permutaciones(n_perms, tamanio);
  if (perms==NULL) return ERR;


/*Ordenamos permutaciones*/
  ini= clock();    
  for(i=0;i<n_perms;i++){ 
        ob= metodo(perms[i], 0, tamanio-1);
        acc+=ob;
        if(ob>max_ob) max_ob=ob;
        if(ob<min_ob) min_ob=ob; 
  }    
  fin= clock(); 

/*Datos*/
  ptiempo->tiempo = (double) (fin-ini)/n_perms/CLOCKS_PER_SEC;
  ptiempo->n_ciclos=n_perms;
  ptiempo->tamanio=tamanio;
  ptiempo->medio_ob=(double)acc/n_perms;
  ptiempo->min_ob=min_ob;
  ptiempo->max_ob=max_ob;

/*Finalizacion y liberizacion de memoria*/
  for (i=0 ; i<n_perms ; i++)
    free (perms[i]);
  free(perms);
  return OK;
}

/***************************************************/
/* Funcion: genera_tiempos_ordenacion              */
/* Fecha: 4-10-2013                                */
/* Autores:   Manuel Reyes                         */
/*                                                 */
/* Funcion para preparar los datos enviados a      */
/* tiempo_medio_ordenacion asi como controlar      */
/* el numero de llamadas.                          */
/* Tambien llama a guarda_tabla_tiempos para       */
/* almacenar los datos.                            */
/*                                                 */         
/* Entradas:                                       */
/* pfunc_ordena metodo: referencia a funcion que   */
/*                      va a ordenar               */
/* char* fichero: nombre del archivo donde         */
/*                 guardar los datos               */
/* int num_min: Tamaño minimo de permutaciones     */
/* int num_max: Tamaño maximo de permutaciones     */
/* int incr: Incremento tamaño de permutaciones    */
/* int n_perms: Numero de permutaciones            */
/*                                                 */
/* Salida:                                         */
/* OK si no hay errores                            */
/* ERR en caso de error                            */
/***************************************************/
short genera_tiempos_ordenacion(pfunc_ordena metodo, char* fichero, int num_min, int num_max, int incr, int n_perms)
{
  PTIEMPO ptiempo;
  int i, j, tamanio;

  if(metodo==NULL || fichero==NULL || num_min<0 || num_max<num_min || incr<1 || n_perms<1)
               return ERR;

  tamanio = ((num_max - num_min)/incr)+1;
  ptiempo = (PTIEMPO) malloc(tamanio*sizeof(TIEMPO));
  if (ptiempo==NULL) return ERR;

  for (i=num_min, j=0; j<tamanio; i+=incr, j++){
     if (tiempo_medio_ordenacion(metodo, n_perms, i, &ptiempo[j]) == ERR){
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

/***************************************************/
/* Funcion: genera_tiempos_ordenacion              */
/* Fecha: 4-10-2013                                */
/* Autores:   Manuel Reyes y Adrian Bueno          */
/*                                                 */
/* Funcion que imprime en un fichero campos de     */
/* la estructura PTIEMPO                          */
/*                                                 */         
/* Entradas:                                       */
/* char* fichero: nombre del archivo donde         */
/*                 guardar los datos               */
/* PTIEMPO tiempo: estructura definida en          */
/*                   ordenar.h cuyos campos son    */
/*                  guardados                      */
/* int N: Tamaño del array tiempo                  */        
/*                                                 */
/* Salida:                                         */
/* OK si no hay errores                            */
/* ERR en caso de error                            */
/***************************************************/
short guarda_tabla_tiempos(char* fichero, PTIEMPO tiempo, int N)
{
  FILE * fich;
  int i;

  if(fichero==NULL || tiempo==NULL || N<1) return ERR;

  fich = fopen (fichero, "a");
  if (fich == NULL) return ERR;

  fprintf(fich,"Tamanio\t\tTiempo\t\tMedia_num_ob\t\tMinimo_num_ob\tMax_num_ob\n");

  for(i=0;i<N;i++){
  fprintf (fich, "%d\t\t%.12f\t\t%.4f\t\t\t%d\t\t%d\n", tiempo[i].tamanio, tiempo[i].tiempo, tiempo[i].medio_ob, tiempo[i].min_ob, tiempo[i].max_ob);
  }

  fclose (fich);
  return OK;
}



/***************************************************/
/* Funcion: swap   Fecha: 27-9-2013                */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Funcion que intercambia los valores             */
/* de dos variables                                */
/*                                                 */
/* Entradas:                                       */
/*     int*a: puntero a numero 1 a intercambiar    */
/*     int*b: puntero a numero 2 a intercambiar    */
/* Salida: void                                    */
/*                                                 */
/***************************************************/
void swap (int* a, int* b)
{
	int aux;
	aux = *a;
	*a = *b;
	*b = aux;
}



/**********************************************************************
*                                                                     *
*                          PRACTICA 2                                 *
*                                                                     *
***********************************************************************/


/**************************************************
*                                                 *
*                   MERGESORT                     *
*                                                 *
***************************************************/


/***************************************************/
/* Funcion: mergesort                              */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Algoritmo de ordenacion divide y venceras       */
/* MergeSort.                                      */ 
/* En este caso la divion es tan simple como       */ 
/* partir la tabla por la mitad.                   */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a la tabla a ordenar */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/* Salida:                                         */
/*      - OB: el numero de operaciones basicas     */
/***************************************************/

int mergesort(int* tabla, int ip, int iu){

     int medio, ob=0, aux;

     if (ip > iu) return ERR;

     if (ip == iu) return OK;
 
     medio = (ip + iu)/2;
     
     aux = mergesort (tabla, ip, medio);
     if (aux==ERR) return ERR;
     ob = ob + aux; 

     aux = mergesort (tabla, medio +1, iu);
     if (aux==ERR) return ERR;
     ob = ob + aux;

     aux = merge (tabla, ip, medio, iu);
     if (aux==ERR) return ERR;

     return ob + aux;
}


/***************************************************/
/* Funcion: merge                                  */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Parte de mergesort que mezcla ordenadamente     */
/* las tablas                                      */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a la tabla a ordenar */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/*      - int imedio: indice medio de la tabla     */
/* Salida:                                         */
/*      - ob: el numero de operaciones basicas     */
/*      - ERR: en caso de error                    */
/***************************************************/

int merge(int* tabla, int ip, int imedio, int iu){

    int *TablaAux;
    int i,j,k;
    int ob=0;
    if (tabla == NULL) return ERR;

    TablaAux = (int *) malloc ((iu-ip+1) * sizeof(TablaAux[0]));
    if (TablaAux == NULL) return ERR;
    
    k = 0; 
    i = ip;  
    j = imedio +1; 

    while(i <= imedio && j <= iu){
          
          ob++;

          if (tabla[i] < tabla[j])
                 TablaAux[k++] = tabla[i++];
          else 
               TablaAux[k++] = tabla[j++];
     }          

     if (i > imedio){
               while( j <= iu){
                 TablaAux[k++] = tabla[j++]; 
               }
     }
     else if (j > iu){
               while (i <= imedio){
                     TablaAux[k++] = tabla[i++]; 
               }
     }
    
    if (CopiarTabla(TablaAux, tabla, ip, iu) == ERR){
          free(TablaAux);
          return ERR;
    }

    free(TablaAux);
    return ob;
}


/***************************************************/
/* Funcion: CopiarTabla                            */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*      					                       */
/* Funcion que copia el contenido de una tabla     */
/* en otra                                         */
/*                                                 */
/* Entradas:                                       */
/*      - int* TablaAux: tabla de la cual copiamos */
/*      - int* tabla: tabla destino                */
/*      - int ip: posicion de tabla en la que      */
/*                empezar a copiar                 */
/*      - int iu: posicion de tabla hasta la cual  */
/*                copiar                           */
/* Salida:                                         */
/*      - OK, ERR                                  */
/***************************************************/

int CopiarTabla(int *TablaAux, int *tabla, int ip, int iu){

    int i, k;
    
    if (TablaAux == NULL || tabla == NULL) return ERR;

    for (i = ip , k = 0; i <= iu ; i++,k++){

         tabla[i] = TablaAux[k];
    }
    return OK;
}





/**************************************************
*                                                 *
*                QUICKSORT                        *
*                                                 *
***************************************************/

/***************************************************/
/* Funcion: quicksort_metodo                       */
/* Autores: Manuel Reyes & Adrian Bueno            */ 
/*                                                 */
/* Funciones que nos permiten respetar nuestro     */
/* prototipo estandar de los metodos de ordenacion */
/* para quicksort                                  */ 
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a la tabla a ordenar */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/* Salida:                                         */
/*      - llamada a quicksort añadiendo el dato    */
/*        del pivote que queremos usar             */
/***************************************************/
int quicksort_medio(int* tabla, int ip, int iu){

     return quicksort(tabla, ip, iu, medio);
}

int quicksort_rand(int* tabla, int ip, int iu){

     return quicksort(tabla, ip, iu, medio_rand);	
}

int quicksort_stat(int *tabla, int ip, int iu){

    return quicksort(tabla, ip, iu, medio_stat);
}


/***************************************************/
/* Funcion: quicksort                              */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Algoritmo de ordenacion quicksort por el metodo */
/* divide y venceras que parte de una manera       */
/* elaborada eligiendo un pivote y mezcla de       */
/* manera sencilla                                 */
/*                                                 */   
/* Entradas:                                       */
/*      - int* tabla: puntero a la tabla a ordenar */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/*      - pfunc_pivote pivote: puntero a funcion   */
/*                     que elegira el pivote       */
/* Salida:                                         */
/*      - ob: El numero de operaciones basicas     */
/*      - ERR: en caso de error                    */
/***************************************************/
int quicksort(int* tabla, int ip, int iu, pfunc_pivote pivote){

    int m;
    int ob=0;

    if (ip > iu)
         return ERR;

    if (ip == iu)
         return OK;

    
    ob = ob + partir(tabla, ip, iu, pivote, &m);

    if (ip < m-1)
          ob = ob + quicksort (tabla, ip, m-1, pivote);
     
    if (m+1 < iu)
          ob = ob + quicksort (tabla, m+1, iu, pivote);

    return ob;
}

/***************************************************/
/* Funcion: partir                                 */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Esta funcion es parte de quicksort, se encarga  */
/* de partir la tabla de acuerdo al pivote         */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a la tabla a partir  */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/*      - pfunc_pivote pivote: puntero a funcion   */
/*                     que elegira el pivote       */
/* Salida:                                         */
/*      - ob: numero de operaciones basicas        */
/***************************************************/

int partir(int* tabla, int ip, int iu, pfunc_pivote pivote , int * m){

    int k, i;
    int ob=0;

    *m = pivote(tabla, ip, iu);
 
    k = tabla[*m];

    swap (&tabla[ip],&tabla[*m]);
    
    *m = ip;

    for( i = ip+1; i <= iu; i++){

            if(tabla[i] < k){
                (*m)++;
                ob++;
                swap(&tabla[i], &tabla[*m]);
            }
    }

    swap (&tabla[ip], &tabla[*m]);

    return ob;
}

/***************************************************/
/* Funcion: medio                                  */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Funcion que devuelve el argumento ip            */
/* Sobran argumento por compatibilidad             */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a una tabla          */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/* Salida:                                         */
/*      - ip: el argumento ip                      */
/***************************************************/

int medio(int *tabla, int ip, int iu){

    return ip;
}


/***************************************************/
/* Funcion: medio_rand                             */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Funcion que devuelve un valor aleatorio entre   */
/* dos indices de una tabla                        */
/* Sobran argumento por compatibilidad             */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a una tabla          */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/* Salida:                                         */
/*      - int: numero obtenido                     */
/***************************************************/

int medio_rand(int *tabla, int ip, int iu){
   
    return aleat_num(ip, iu);
}

/***************************************************/
/* Funcion: medio_stat                             */
/* Autores: Manuel Reyes & Adrian Bueno            */
/*                                                 */
/* Funcion que devuelve el elemento medio de:      */
/* el primer elemento de una tabla, el segundo,    */
/* y el que ocupe la posicion de la mitad          */
/*                                                 */
/* Entradas:                                       */
/*      - int* tabla: puntero a una tabla          */
/*      - int ip: indice primero de la tabla       */
/*      - int iu: indice ultimo de la tabla        */
/* Salida:                                         */
/*      - el elemento medio                        */
/***************************************************/

int medio_stat(int *tabla, int ip, int iu){
  
   int m = (ip+iu)/2;

   if(tabla[ip]>=tabla[iu]){
        if(tabla[ip]<=tabla[m])
            return ip;
        else if(tabla[m]>=tabla[iu])
            return m;
        else 
            return iu;
   } else{
        if(tabla[ip]>=tabla[m])
            return ip;
        else if(tabla[m]>=tabla[iu])
            return iu;
        else 
            return m;        
   }
}
