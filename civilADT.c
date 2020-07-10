#include <stdio.h>
#include <stdlib.h>
#include "civilADT.h"
#include <math.h>
#define EPSILON 0.01

/*FRONT END*/
int checkMem (void * pointer) {
   if (pointer == NULL) {
    fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
    return 1; 
  }   
  return 0;
}

/*
La estructura consta de un vector de punteros a estructura, donde cada puntero apunta a una estructura del tipo Telem
*/

struct civilCDT{
  struct elementos** vector;
  int indice; //para iterar en el vector desde afuera 
  size_t dim; //dimension del vector (Cantidad de barrios)
};

/*Elemento al que apunta cada vector*/
typedef struct elementos{
  char * nombre;//nombre del barrio
  size_t habitantes;//cantidad de habitantes 
  size_t CantArboles;//cantidad de arboles en el barrio
}Telem;


/*Para calcular arboles por habitantes*/
static double calcTBH (struct elementos * neigh) {
  return neigh->CantArboles/(double)neigh->habitantes;
}



/*
Inicializa un nuevo ADT
*/
civilADT newCivil(){
  civilADT aux;
  aux=calloc(1,sizeof(struct civilCDT));
  if(checkMem(aux))
    return NULL;/*Chequear*/
  else 
    return aux;

  checkMem(aux);
  return aux;
}



/*
Libera los recursos usados por el TAD
Para cada elemento del vector debe liberar el nombre , luego liberar el puntero y por ultimo liberar el ADT

*/
void freeCivil(civilADT civil){
  for(int i = 0 ; i < civil->dim ; i++){
    //liberar la cadena de cada elemento y el puntero a cada elemento 
    free(civil->vector[i]->nombre);
    free(civil->vector[i]);
  }
  //el vector de punteros
  free(civil->vector);
  //el ADT
  free(civil);
}


/*
Agrega un elemento en la lista segun el orden ASCII de los barrios 
Se inicializa la cantidad de arboles en cero.
Recorre el vector para asegurarse que no haya repetidos.Si exitiesen repetidos en el archivo se consideraria un error y se ignoraria la segunda aparicion. 
*/
bool addNeigh(civilADT civil,char * barrio, unsigned long habitantes){
  int c;
  /*Buscar repetidos, si encuentra lo ignora*/
  for(int i = 0 ; i < civil->dim ; i++){
    if( (c=strcmp(civil->vector[i]->nombre,barrio)) == 0 )
      return 1;
  }

  /* Agrega al final , reservando una posicion mas */
  struct elementos ** aux;
  int Dim = civil->dim;
  aux = realloc(civil->vector,((Dim)+1)*sizeof(struct elementos*) );
  if(checkMem(aux))
    return 0; //Que pasa si no hay memoria? hacer Int?
  else 
    civil->vector=aux;
  
  /*Cargo la informacion*/
   
  civil->vector[Dim]=malloc(sizeof(struct elementos)); // y el checkmem de esto?
  if( checkMem(civil->vector[Dim]) )
    return 0;

  civil->vector[Dim]->habitantes=habitantes;
  civil->vector[Dim]->CantArboles=0;
  int largo=strlen(barrio);
  char * aux1=malloc((largo+1)*sizeof(char));
  if(checkMem(aux1))
    return 0; //fallo asignacion de memoria
  else{
    civil->vector[Dim]->nombre=aux1;
    strcpy(civil->vector[Dim]->nombre,barrio);
  }
  (civil->dim)++;

  return 1;
}


/*
Incrementa en uno la cantidad de arboles del nodo
barrio.Intercambia con el elemento anterior. 
*/
void addTree(civilADT civil, char * barrio){
  /*Recorre el vector hasta encontrar el elemento*/
  int c ;
  for(int i = 0 ; i < civil->dim ; i++)
    if( (c=strcmp(civil->vector[i]->nombre,barrio)) == 0){
      (civil->vector[i]->CantArboles)++;
      
      /*Intercambiar los elementos*/
      if(i>0) {
        struct elementos * aux;  
        aux=civil->vector[i];
        civil->vector[i]=civil->vector[i-1];
        civil->vector[i-1]=aux;
      }
    }
  
  }




/*Resetea el iterador al principio de la coleccion*/
void resetNeigh (civilADT civil){
  civil->indice=0;
  return;
}

/*Deuelve 1 si no hay mas barrios en la coleccion*/
bool noMoreNeighs (civilADT civil){
  return civil->indice==civil->dim;
}

/*Mueve una unidad el iterador*/
/*
En vez de chequear en cada funcion podria chequearse aca
que nunca se igual  a la dimension del vector 
*/
void nextNeigh (civilADT civil){
  if (! noMoreNeighs(civil))
    civil->indice++;
}

static int empty (civilADT civil) {
  return ! civil->dim; 
}

/*Devuelve el puntero al nombre del barrio al que apunta el iterador*/
char * getNeighName (civilADT civil){
  if(!empty(civil))
    return civil->vector[civil->indice]->nombre;
  else 
    return NULL; 
}

/*Devuelve la cantidad de habitantes del elemento actual del iterador*/
unsigned long getNeighPop (civilADT civil){
  //if(!empty(civil))
    return civil->vector[civil->indice]->habitantes;
  //else 
    //return 0;
}


/*Devuelve la cantidad de arboles del elemento actual apuntado por el iterador*/
unsigned long getNeighTrees (civilADT civil){
  if(!empty(civil))
    return civil->vector[civil->indice]->CantArboles;
  else 
    return 0; /*No hay mas elementos*/
}


/*Devuelve el cociente entre arboles y habitantes del elemento apuntado por el iterador*/
double getTreesPerHab (civilADT civil){
     int actual=civil->indice;
     return calcTBH(civil->vector[actual]);

}



/*Ordena en forma descendiente por cantidad de arboles por habitantes*/
static int compareDescTBHAscAlf (const void * a, const void * b){

  struct elementos ** elem1 = (struct elementos **) a;
  struct elementos ** elem2 = (struct elementos **) b;

  double TBH1 = calcTBH(*elem1);
  double TBH2 = calcTBH(*elem2);
  if ( fabs(TBH1-TBH2) < EPSILON )
    return strcmp((*elem1)->nombre, (*elem2)->nombre);
  else
    return TBH2 > TBH1;
}

/*Descendiente por cantidad de arboles por habitante*/
void sortDescTBHAscAlf(civilADT civil) {
  qsort(civil->vector, civil->dim, sizeof(struct elementos*), compareDescTBHAscAlf);
}

static int compareDescTreeAscAlf (const void * a, const void * b){

  struct elementos ** elem1 = (struct elementos**) a;
  struct elementos ** elem2 = (struct elementos**) b;



  if ((*elem2)->CantArboles == (*elem1)->CantArboles)
    return strcmp((*elem1)->nombre, (*elem2)->nombre);
  else
    return (*elem2)->CantArboles > (*elem1)->CantArboles;
}

void sortDescTreeAscAlf(civilADT civil){
  qsort(civil->vector, civil->dim, sizeof(struct elementos *), compareDescTreeAscAlf);
}

