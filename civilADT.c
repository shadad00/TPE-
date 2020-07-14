#include "civilADT.h"
#include <stdbool.h>
#include "checkError.h"

#define EPSILON 0.01

/*
La estructura consta de un vector de punteros a estructura, donde cada puntero apunta a una estructura del tipo tNeigh
*/

typedef struct civilCDT{
  struct tNeigh ** neighs;
  int current; //para iterar en el vector desde afuera 
  size_t qNeighs; //dimension del vector
} civilCDT;

/*Elemento al que apunta cada vector*/
typedef struct tNeigh {
  char * name;//nombre del barrio
  long pop;//cantidad de habitantes 
  long qTrees;//cantidad de arboles en el barrio
} tNeigh;

/*Funcion auxiliar que trunca a dos decimales*/
static float truncate(float numero){
  numero*=100;
  numero=(int)(numero);
  return numero/100;
}


/*Inicializa un nuevo ADT*/
civilADT newCivil(int * flag){
  civilADT aux=calloc(1,sizeof(struct civilCDT));
  *flag=checkMem();
  return aux;
}

/*
Libera los recursos usados por el TAD
Para cada elemento del vector debe liberar el nombre , luego liberar el puntero y por ultimo liberar el ADT
*/

void freeCivil(civilADT civil){
  for(int i = 0 ; i < civil->qNeighs ; i++){
    //liberar la cadena de cada elemento y el puntero a cada elemento 
    free(civil->neighs[i]->name);
    free(civil->neighs[i]);
  }
  //el vector de punteros
  free(civil->neighs);
  //el ADT
  free(civil);
}

/*
Agrega un elemento en la lista segun el orden ASCII de los barrios 
Se inicializa la cantidad de arboles en cero.
Recorre el vector para asegurarse que no haya repetidos.Si exitiesen repetidos en el archivo se consideraria un error y se ignoraria la segunda aparicion. 
*/
bool addNeigh(civilADT civil, char * barrio, unsigned long habitantes){


  /*Buscar repetidos, si encuentra lo ignora*/
  for(int i = 0 ; i < civil->qNeighs ; i++)
    if( ! checkRep(civil->neighs[i]->name, barrio) )
      return true;
  

  /* Agrega al final , reservando una posicion mas */
  tNeigh ** aux;
  int Dim = civil->qNeighs;
  aux = realloc(civil->neighs,(Dim+1)*sizeof(struct elementos*));

  if( !checkMem() )
    return false; 

  civil->neighs=aux;
  
  /*Cargo la informacion*/
   
  civil->neighs[Dim]=malloc(sizeof(tNeigh)); 
  
  if( ! checkMem() )
    return false;

  civil->neighs[Dim]->pop=habitantes;
  civil->neighs[Dim]->qTrees=0;
  int largo=strlen(barrio);
  char * aux1=malloc((largo+1)*sizeof(char));

  if(! checkMem() )
    return false; 
  
  civil->neighs[Dim]->name=aux1;
  strcpy(civil->neighs[Dim]->name,barrio);
  (civil->qNeighs)++;
  return true;
}

/*Calcula arboles por habitante*/
static float calcTBH (struct tNeigh * neigh) {
  if(neigh!=NULL && neigh->pop!=0)
    return truncate(neigh->qTrees/(float)neigh->pop);
  else 
    return -1;
}


/*
Incrementa en uno la cantidad de arboles del nodo
barrio.Intercambia con el elemento anterior. 
El objetivo de esto es mejorar el caso promedio. 
Los elementos mas populares quedan mas adelante
*/
bool addTree(civilADT civil, char * barrio){
  /*Recorre el vector hasta encontrar el elemento*/
  int c ;
  for(int i = 0 ; i < civil->qNeighs ; i++)
    if( (c=strcmp(civil->neighs[i]->name,barrio)) == 0){
      (civil->neighs[i]->qTrees)++;
      
      /*Intercambiar los elementos*/
      if(i>0) {
        tNeigh * aux;  
        aux=civil->neighs[i];
        civil->neighs[i]=civil->neighs[i-1];
        civil->neighs[i-1]=aux;
      }
      return true; 
    }
    //Devuelve 0 si el barrio no existia
  return false; 
}


/*Resetea el iterador al principio de la coleccion*/
void resetNeigh (civilADT civil){
  civil->current=0;
  return;
}

/*Devuelve 1 si no hay mas barrios en la coleccion*/
bool noMoreNeighs (civilADT civil){
    return  isEmptyCivil(civil) ||civil->current==civil->qNeighs ;
}

/*Mueve una unidad el iterador*/
void nextNeigh (civilADT civil){
  if (! noMoreNeighs(civil))
    civil->current++;
}

/*Revisa si el TAD esta vacio*/
bool isEmptyCivil (civilADT civil) {
  return civil == NULL || ! civil->qNeighs; 
}

/*Devuelve el puntero al nombre del barrio al que apunta el iterador*/
char * getNeighName (civilADT civil){
  if(isEmptyCivil(civil))
    return NULL;
  return civil->neighs[civil->current]->name; 
}

/*Devuelve la cantidad de habitantes del elemento actual del iterador*/
 long getNeighPop (civilADT civil){
  if(isEmptyCivil(civil))
    return -1; 
  return civil->neighs[civil->current]->pop;
}


/*Devuelve la cantidad de arboles del elemento actual apuntado por el iterador*/
long getNeighTrees (civilADT civil){
  if(isEmptyCivil(civil))
      return -1; 
  return civil->neighs[civil->current]->qTrees;
}


/*Devuelve el cociente entre arboles y habitantes del elemento apuntado por el iterador*/
float getTreesPerHab (civilADT civil){
  if( isEmptyCivil(civil) )
    return -1; 
  return calcTBH(civil->neighs[civil->current]);
}



/*Funcion auxiliar que retorna 1 si b apunta a un elemento que tiene mas arboles que  a.*/
static int compareDescTBHAscAlf (const void * a, const void * b){

  tNeigh ** elem1 = (tNeigh **) a;
  tNeigh ** elem2 = (tNeigh **) b;

  float TBH1 = calcTBH(*elem1);
  float TBH2 = calcTBH(*elem2);
  if ( fabs(TBH1-TBH2) < EPSILON )
    return strcmp((*elem1)->name, (*elem2)->name);
  else
    return TBH2 > TBH1;
}

/*Descendiente por cantidad de arboles por habitante*/
void sortDescTBHAscAlf(civilADT civil) {
  if (! isEmptyCivil(civil)) 
    qsort(civil->neighs, civil->qNeighs, sizeof(struct elementos*), compareDescTBHAscAlf);
}

/*Funcion auxiliar que retorna 1 si el elemento apuntado por b es mayor que elemento apuntado por a.*/
static int compareDescTreeAscAlf (const void * a, const void * b){

  tNeigh ** elem1 = (tNeigh **) a;
  tNeigh ** elem2 = (tNeigh **) b;

  if ((*elem2)->qTrees == (*elem1)->qTrees)
    return strcmp((*elem1)->name, (*elem2)->name);
  else
    return (*elem2)->qTrees > (*elem1)->qTrees;
}


/*Ordena el vector de manera decreciente por arboles por barrio*/
void sortDescTreeAscAlf(civilADT civil){
  if ( ! isEmptyCivil(civil) ) 
  qsort(civil->neighs, civil->qNeighs, sizeof(struct elementos *), compareDescTreeAscAlf);
}

