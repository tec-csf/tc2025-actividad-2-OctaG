/*
  Octavio Garduza
  A01021660

  Actividad 2

  Implementación de diferentes tipos de iteradores que recorren un arreglo de
  cualquier tipo de datos utilizando memoria dinámica y apuntadores a funciones

*/

#include <stdio.h>
#include <stdlib.h>

//Tamaño del arreglo
#define N 10
#define L 5

//Apuntadores a funciones genéricas
typedef void (*data_t)(void*);
typedef void (*iterator_t)(void*, void*, data_t, size_t);

//Apuntadores a funciones del struct iterador
typedef void (*fnp_recorre)(void*, void*, iterator_t , data_t, size_t);
typedef void *(*fpn_prev)(void*, void*, size_t);
typedef void *(*fpn_next)(void*, void*, size_t);

//Recibe un arreglo dinámico y recorre utilizando un tipo de iterador
void recorre(void* itrtr_start, void* itrtr_end, iterator_t iterator, data_t datatype, size_t data_size);

//Tipos de iteradores
void forward_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size);
void reverse_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size);
void bidirectional_itrtr(void* start, void* end, data_t datatype, size_t data_size);

void *next(void* itrtr_current, void* itrtr_end, size_t);
void *prev(void* itrtr_current, void* itrtr_start, size_t);

//Auxiliares para imprimir el tipo de dato
void int_t(void *elem);
void float_t(void *elem);
void libro_t(void *elem);

typedef struct {
  char * titulo;
  int paginas;
}libro;

typedef struct{
  fnp_recorre iterate;
  fpn_prev prev;
  fpn_next next;
  void* begin;
  void* end;
}iterator;


int main(int argc, const char * argv[]){
  printf("\n");

  //Iterador genérico
  iterator iterator_obj;

  iterator_obj.iterate = recorre;
  iterator_obj.prev = prev;
  iterator_obj.next = next;

  /*----- Arreglo de enteros -----*/

  int *vector_i = (int *) malloc(N * sizeof(int));
  int *fin_vector_i = vector_i + N;

  int c_int = 0;
  for (int *aux = vector_i; aux < fin_vector_i; ++aux) {
    *aux = c_int++;
  }

  //Iterador de todo el arreglo
  iterator_obj.begin = vector_i; //Elem
  iterator_obj.end = fin_vector_i;

  //Imprimir el arreglo
  printf("Arreglo de ints iterado con forward_itrtr:\n");
  iterator_obj.iterate(iterator_obj.begin, iterator_obj.end, &forward_itrtr, &int_t, sizeof(int));
  printf("\n\n");


  /*----- Arreglo de floats -----*/

  float *vector_f = (float *) malloc(N * sizeof(float));
  float *fin_vector_f = vector_f + N;

  float c_float = 0.0;
  for (float *aux = vector_f; aux < fin_vector_f; ++aux) {
    *aux = c_float++;
  }

  //Iterador de un subarreglo
  iterator_obj.begin = vector_f + 3; //Elem 3
  iterator_obj.end = fin_vector_f - 2; //Elem 7

  //Imprimir el subarreglo
  printf("Subarreglo de floats iterado con reverse_itrtr:\n");
  iterator_obj.iterate(iterator_obj.end, iterator_obj.begin, &reverse_itrtr, &float_t, sizeof(float));
  printf("\n\n");

  //Previo del elemento 8 llamado con el begin del iterador
  float* current = iterator_obj.begin+(5*sizeof(float));
  float* previous_elem = iterator_obj.prev(current, iterator_obj.begin, sizeof(float));
  if(previous_elem){
   printf("Elemento previo a %.1f: %.1f\n", *current, *previous_elem);
  }
  else{
   printf("NULL\n");
  }
  //Next del elemento 5 llamado con el puntero inicial
  float* next_elem = iterator_obj.next(vector_f+5, iterator_obj.end, sizeof(float));
  if(next_elem){
   printf("Elemento siguiente a %.1f: %.1f\n",*vector_f+5, *next_elem);
  }
  else{
   printf("NULL\n");
  }
  printf("\n\n");

  /*----- Arreglo de libros -----*/
  libro *biblioteca = (libro *) malloc(sizeof(libro) * L); //L libros
  libro *final_biblioteca = biblioteca + L;

  for(libro *aux = biblioteca; aux < final_biblioteca; ++aux) {
    aux->titulo = (char *) malloc(sizeof(char) * 25);

    printf("Ingrese el titulo del libro: ");
    scanf("%s", aux->titulo);
    printf("Ingrese las páginas del libro: ");
    scanf("%d", &aux->paginas);

    printf("\n");
  }
  iterator_obj.begin = biblioteca+1; //Libro 2
  iterator_obj.end = final_biblioteca; //Libro L
  printf("Subarreglo de libros con bidirectional_itrtr ascendente:\n\n");
  iterator_obj.iterate(iterator_obj.begin, iterator_obj.end, &bidirectional_itrtr, &libro_t, sizeof(libro));

  iterator_obj.begin = biblioteca; //Libro 1
  iterator_obj.end = final_biblioteca-1; //Libro 4
  printf("Subarreglo de libros con bidirectional_itrtr descendente:\n\n");
  iterator_obj.iterate(iterator_obj.end, iterator_obj.begin, &bidirectional_itrtr, &libro_t, sizeof(libro));
}//Fin de main

/*
 * Function:  next
 * --------------------
 * Retorna un apuntador al elemento siguiente del pasado como argumento
 *
 *  itrtr_current: Apuntador al elemento del que se quiere conocer el siguiente
 *  itrtr_end: Apuntador al elemento final del arreglo o subarreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 *  returns: apuntador al elemento itrtr_current + data_size.
 *           NULL si itrtr_current es el último elemento del arreglo.
 */
void *next(void* itrtr_current, void* itrtr_end, size_t data_size){
  if(itrtr_current >= itrtr_end){
    return NULL;
  }
  return itrtr_current + data_size;
}

/*
 * Function:  prev
 * --------------------
 * Retorna un apuntador al elemento previo del pasado como argumento
 *
 *  itrtr_current: Apuntador al elemento del que se quiere conocer el previo
 *  itrtr_end: Apuntador al elemento inicial del arreglo o subarreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 *  returns: apuntador al elemento itrtr_current - data_size.
 *           NULL si itrtr_current es el primer elemento del arreglo.
 */
void *prev(void* itrtr_current, void* itrtr_start, size_t data_size){
  if(itrtr_current <= itrtr_start){
    return NULL;
  }
  return itrtr_current - data_size;
}

/*
 * Function:  recorre
 * --------------------
 * Función genérica para recorrer un arreglo o subarreglo
 *
 *  itrtr_start: Apuntador al elemento inicial del arreglo o subarreglo
 *  itrtr_end: Apuntador al elemento final del arreglo o subarreglo
 *  iterator: Tipo de iterador a utilizar.
 *  datatype: Tipo de dato almacenado en el arreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 *  Se llama a la función pasada como iterador.
 */
void recorre(void* itrtr_start, void* itrtr_end, iterator_t iterator, data_t datatype, size_t data_size)
{
  (*iterator)(itrtr_start, itrtr_end, datatype, data_size);
}

/*
 * Function:  forward_itrtr
 * --------------------
 * Recorre el arreglo desde itrtr_start hasta itrtr_end de manera ascendente
 *
 *  itrtr_start: Apuntador al elemento inicial del arreglo o subarreglo
 *  itrtr_end: Apuntador al elemento final del arreglo o subarreglo
 *  datatype: Tipo de dato almacenado en el arreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 */
void forward_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size){
  void* current = itrtr_start;
  while(current < itrtr_end){
    (*datatype)(current);
    current+=data_size;
  }
}

/*
 * Function:  reverse_itrtr
 * --------------------
 * Recorre el arreglo desde itrtr_start hasta itrtr_end de manera descendente
 *
 *  itrtr_start: Apuntador al elemento final del arreglo o subarreglo
 *  itrtr_end: Apuntador al elemento inicial del arreglo o subarreglo
 *  datatype: Tipo de dato almacenado en el arreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 */
void reverse_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size){
  void* current = itrtr_start - data_size;
  while(current >= itrtr_end){
    (*datatype)(current);
    current -= data_size;
  }
}

/*
 * Function:  reverse_itrtr
 * --------------------
 *  Cuando itrtr_start <= itrtr_end recorre el arreglo de manera ascendente.
 *  Cuando itrtr_start > itrtr_end recorre el arreglo de manera descendente.
 *
 *  itrtr_start: Apuntador al elemento inical o final del arreglo o subarreglo
 *  itrtr_end: Apuntador al elemento inicial o final del arreglo o subarreglo
 *  datatype: Tipo de dato almacenado en el arreglo
 *  data_size: Tamaño del tipo de dato en el arreglo
 *
 */
void bidirectional_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size){
  if(itrtr_start <= itrtr_end){
    forward_itrtr(itrtr_start, itrtr_end, datatype, data_size);
  }else{
    reverse_itrtr(itrtr_start, itrtr_end, datatype, data_size);
  }
}


//Auxiliares para imprimir cada tipo de dato
void int_t(void* elem){
  int *aux = elem;
  printf("%d ", *aux);
}

void float_t(void* elem){
  float *aux = elem;
  printf("%.1f ", *aux);
}

void libro_t(void* elem){
  libro *aux = elem;
  printf("Titulo: %s\nPaginas: %d\n\n", aux->titulo, aux->paginas);
}
