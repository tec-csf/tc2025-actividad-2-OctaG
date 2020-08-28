### Iterador genérico 

#### Descripción
Implementación de  un iterador genérico utilizando estructuras, memoria dinámica
y apuntadores a funciones.

#### Diseño del iterador

```
typedef struct{
  fnp_recorre iterate;
  fpn_prev prev;
  fpn_next next;
  void* begin;
  void* end;
}iterator;
```
```
iterator iterator_obj;
```
###### Apuntadores begin y end
El iterador almacena en la variable ```begin``` el apuntador al elemento por el que se empezará a iterar sobre el arreglo, y en la variable ```end```, el apuntador al elemento hasta el cual se iterará el mismo. Esta es una sencilla forma de definir el rango del iterador y da la libertad de recorrer no solo el arreglo original, sino cualquier subarreglo en ambas direcciones.

###### Funciones prev y next
Las funciones ```prev``` y ```next```  del iterador apuntan a las funciones del mismo nombre y al ser llamadas regresan un apuntador al elemento siguiente o al elemento previo del que fue pasado como argumento.

```
iterator_obj.prev = prev;
iterator_obj.next = next;
```

###### Funcion iterate
La función ```iterate``` apunta a la función genérica ```recorre``` y recibe un tipo de iterador con el que se iterará. El argumento ```itrtr_star``` siempre debe pensarse como el inicio del iterador e ```itrtr_end``` como el final del mismo; esto sin importar si el iterador es ascendente o descendendte.   

```
iterator_obj.iterate = recorre;
```

#### Tipos de iteradores

###### forward_itrtr()
```
forward_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size)
```
Recorre el arreglo de manera ascendente desde ```itrtr_start``` hasta ```itrtr_end```. El apuntador a ```itrtr_start``` siempre debe preceder al apuntador a ```itrtr_end```. Recorre el arreglo incrementando un apuntador auxiliar en función al ```data_size``` pasado como argumento. Dependiendo del tipo de dato pasado como ```datatype``` se llamará a una de las funciones auxiliares de impresión.

###### reverse_itrtr()
```
void reverse_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size)
```
Recorre el arreglo de manera descendente desde ```itrtr_start``` hasta ```itrtr_end```. El apuntador a ```itrtr_start``` siempre debe suceder al apuntador a ```itrtr_end```. Recorre el arreglo decrementando un apuntador auxiliar en función al ```data_size``` pasado como argumento. Dependiendo del tipo de dato pasado como ```datatype``` se llamará a una de las funciones auxiliares de impresión.

###### bidirectional_itrtr()
```
void bidirectional_itrtr(void* itrtr_start, void* itrtr_end, data_t datatype, size_t data_size)
```
Recorre el arreglo de manera ascendente o descendente dependiendo de la precedencia entre ```itrtr_start``` e ```itrtr_end```. Si el apuntador a ```itrtr_start``` precede al apuntador a ```itrtr_end```, entonces se llama a la función ```forward_itrtr()```. Si el apuntador a ```itrtr_start``` sucede al apuntador a ```itrtr_end```, entonces se llama a la función ```reverse_itrtr()```.
