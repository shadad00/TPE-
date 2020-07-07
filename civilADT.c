#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "civilADT.h"
#define EPSILON 0.001

typedef struct node{ 
  char * barrio;
  size_t habitantes;
  size_t arboles;
}Tnode;

typedef struct elem{ //lista ordenada por cociente entre arboles y habitantes
  char *nombre;
  double cociente;
  struct elem * tail;
}Telem;

struct list{ //lista en la cual se almacenan los datos sacados de los csv
  struct node nodo;
  struct list * tail;
};

struct civilCDT{
  struct list * lista; //lista para almacenar los datos de los csv
  struct elem * cociente; 
  struct orden * arbolesxBarrio ;
};

struct orden{ //lista ordenada por cantidad de arboles
  char * nombre;
  size_t arboles;
  struct orden * tail;
};


/*funcion auxiliar para chequear disponibilidad de memoria en la ejecucion*/
static void checkMem (void * pointer) {
  if (pointer == NULL) {
    fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
    exit(3); 
  }

}

/*
inicializa el ADT
*/
civilADT Newcivil(){
  civilADT aux=calloc(1, sizeof(struct civilCDT));
  checkMem(aux);
  return aux ;
}

/*funcion auxiliar que agrega los elementos en la lista de manera ordenada con strcmp
Inicializa la cantidad de arboles en cero 
*/
static struct list * addRec(struct list * lista, char * nombre, int habitantes ){
//agregar si la lista es vacia o es menor que el primer elemento
  int c;
  if( lista==NULL || ( c=strcmp(nombre,lista->nodo.barrio) ) < 0 ){ 
    struct list * aux;
    struct list * disponible;
    disponible= malloc(sizeof(struct list ));
    checkMem(disponible);
    aux=disponible;
    aux->nodo.barrio=nombre;
    aux->nodo.habitantes=habitantes;
    aux->nodo.arboles=0;
    aux->tail=lista;
    return aux;
  }else if( c > 0)
    lista->tail=addRec(lista->tail, nombre,habitantes);
  return lista;

}


/*
Agrega un elemento en la lista segun el orden ASCII de los barrios 
Se inicializa la cantidad de arboles en cero 
*/
void addNeigh(civilADT civil,char * barrio,int habitantes){
  civil->lista=addRec(civil->lista,barrio,habitantes);
}

/*
Funcion recursiva para encontrar un barrio en la lista
*/
static void FindNeighRec(struct list * lista, char * nombre){
  //si lista vacia  (aunque no puede estar vacia y se que va a encontrar al barrio)
  if(lista==NULL)
    return;

  int c=strcmp(lista->nodo.barrio,nombre) ;
  if( c == 0 ){
    lista->nodo.arboles++;
    return ;     
  }
  FindNeighRec(lista->tail,nombre);
}


/*
Incrementa en uno la cantidad de arboles del nodo
barrio.Se sabe que el barrio pertenece a la lista, pues se proceso primero el archivo con barrios y cantidad de habitantes  
*/
void IncTrees(civilADT civil, char * barrio){
  FindNeighRec(civil->lista,barrio);
}

/*
Funcion auxiliar que agrega en la lista de cociente cada nodo de manera decreciente 
*/
static struct elem * AddCocienteRec(struct elem * lista, double cociente, char * nombre){
  int c;
  //si la lista esta vacia o el cociente es mayor que el primer elemento, pueden haber dos iguales , define el orden alfabetico 
  if( lista==NULL || cociente > lista->cociente  || ( ( (cociente-lista->cociente) < EPSILON ) && ( (c=strcmp(nombre, lista->nombre) < 0 ) ) ) ) {
    struct elem * aux;
    struct elem * disponible;
    disponible=malloc(sizeof(struct elem));
    checkMem(disponible);
    aux=disponible;
    aux->cociente=cociente;
    aux->nombre=nombre;
    aux->tail=lista;
    return aux;
  }
  
  lista->tail=AddCocienteRec(lista->tail, cociente, nombre);
  return lista; 
}


/*
Funcion auxiliar que agrega elementos en la lista ordenada por arboles por barrio de manera decreciente y luego por orden 
alfabetico
*/

struct orden * AddNodosRec(struct orden * lista, int arboles,char * nombre){
  int c;
  if( lista==NULL || arboles > lista->arboles || ( (arboles == lista->arboles) && ( (c=strcmp(nombre,lista->nombre) ) < 0) ) ) {
      struct orden * aux;
      struct orden * disponible ;
      disponible=malloc(sizeof(struct orden));
      checkMem(disponible);
      aux=disponible;
      aux->nombre=nombre;
      aux->arboles=arboles;
      aux->tail=lista;
      return aux;
  }
  lista->tail=AddNodosRec(lista->tail,  arboles, nombre);
  return lista; 
}




/*
Crea una lista ordenada segun la cantidad de arboles por habitante y luego por orden alfabetico, simultaneamente crea una lista ordenada segun la cantidad de arboles por barrio y libera el nodo de la primera lista;
*/

void TreePerHab(civilADT civil){
  struct list *aux,*aux2;
  aux=civil->lista;
  
  while(aux!=NULL){
    civil->cociente=AddCocienteRec(civil->cociente, aux->nodo.arboles/(float)aux->nodo.habitantes, aux->nodo.barrio);
    civil->arbolesxBarrio=AddNodosRec(civil->arbolesxBarrio,aux->nodo.arboles, aux->nodo.barrio);
    aux2=aux->tail; // guardo la posicion del siguiente elemento 
    free(aux);
    aux=aux2;
  }


}

/*
Libera todos los recursos utilizados por el ADT
*/

//la primera lista ya fue liberada (podria considerarse o no)

void freeCivil(civilADT civil){

while(civil->arbolesxBarrio!=NULL || civil->cociente!=NULL){
  struct orden * aux1;
  struct elem * aux2;
  if(civil->arbolesxBarrio!=NULL){
    aux1 = civil->arbolesxBarrio->tail;
    free(civil->arbolesxBarrio);
    civil->arbolesxBarrio=aux1;
  }
  if(civil->cociente!=NULL){
    aux2=civil->cociente->tail;
    free(civil->cociente);
    civil->cociente=aux2;
  }

}
free(civil);

};



