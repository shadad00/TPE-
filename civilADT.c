#include "civilADT.h"

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
  size_t pop;//cantidad de habitantes 
  size_t qTrees;//cantidad de arboles en el barrio
} tNeigh;


/*Calcula arboles por habitante*/
static double calcTBH (struct tNeigh * neigh) {
  return neigh->qTrees/(double)neigh->pop;
}

/*Inicializa un nuevo ADT*/
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
bool addNeigh(civilADT civil,char * barrio, unsigned long habitantes){
  int c;
  /*Buscar repetidos, si encuentra lo ignora*/
  for(int i = 0 ; i < civil->qNeighs ; i++){
    if( (c=strcmp(civil->neighs[i]->name,barrio)) == 0 )
      return 1;
  }

  /* Agrega al final , reservando una posicion mas */
  tNeigh ** aux;
  int Dim = civil->qNeighs;
  aux = realloc(civil->neighs,((Dim)+1)*sizeof(struct elementos*) );
  if(checkMem(aux))
    return 0; //Que pasa si no hay memoria? hacer Int?
  else 
    civil->neighs=aux;
  
  /*Cargo la informacion*/
   
  civil->neighs[Dim]=malloc(sizeof(tNeigh)); // y el checkmem de esto?
  
  if( checkMem(civil->neighs[Dim]) )
    return 0;

  civil->neighs[Dim]->pop=habitantes;
  civil->neighs[Dim]->qTrees=0;
  int largo=strlen(barrio);
  char * aux1=malloc((largo+1)*sizeof(char));
  if(checkMem(aux1))
    return 0; //fallo asignacion de memoria
  else{
    civil->neighs[Dim]->name=aux1;
    strcpy(civil->neighs[Dim]->name,barrio);
  }
  (civil->qNeighs)++;

  return 1;
}


/*
Incrementa en uno la cantidad de arboles del nodo
barrio.Intercambia con el elemento anterior. 
El objetivo de esto es mejorar el caso promedio. 
Los elementos mas populares quedan mas adelante
*/
void addTree(civilADT civil, char * barrio){
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
    }
  
  }




/*Resetea el iterador al principio de la coleccion*/
void resetNeigh (civilADT civil){
  civil->current=0;
  return;
}

/*Devuelve 1 si no hay mas barrios en la coleccion*/
bool noMoreNeighs (civilADT civil){
  return civil->current==civil->qNeighs;
}

/*Mueve una unidad el iterador*/
void nextNeigh (civilADT civil){
  if (! noMoreNeighs(civil))
    civil->current++;
}

/*Revisa si el TAD esta vacio*/
static int empty (civilADT civil) {
  return ! civil->qNeighs; 
}

/*Devuelve el puntero al nombre del barrio al que apunta el iterador*/
char * getNeighName (civilADT civil){
  if(!empty(civil))
    return civil->neighs[civil->current]->name;
  else 
    return NULL; 
}

/*Devuelve la cantidad de habitantes del elemento actual del iterador*/
unsigned long getNeighPop (civilADT civil){
  if(!empty(civil))
    return civil->neighs[civil->current]->pop;
  else 
    return 0;
}


/*Devuelve la cantidad de arboles del elemento actual apuntado por el iterador*/
unsigned long getNeighTrees (civilADT civil){
  if(!empty(civil))
    return civil->neighs[civil->current]->qTrees;
  else 
    return 0; 
}


/*Devuelve el cociente entre arboles y habitantes del elemento apuntado por el iterador*/
double getTreesPerHab (civilADT civil){
     int actual=civil->current;
     return calcTBH(civil->neighs[actual]);

}



/*Funcion auxiliar que retorna 1 si b apunta a un elemento que tiene mas arboles que  a.*/
static int compareDescTBHAscAlf (const void * a, const void * b){

  tNeigh ** elem1 = (tNeigh **) a;
  tNeigh ** elem2 = (tNeigh **) b;

  double TBH1 = calcTBH(*elem1);
  double TBH2 = calcTBH(*elem2);
  if ( fabs(TBH1-TBH2) < EPSILON )
    return strcmp((*elem1)->name, (*elem2)->name);
  else
    return TBH2 > TBH1;
}

/*Descendiente por cantidad de arboles por habitante*/
void sortDescTBHAscAlf(civilADT civil) {
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

void sortDescTreeAscAlf(civilADT civil){
  qsort(civil->neighs, civil->qNeighs, sizeof(struct elementos *), compareDescTreeAscAlf);
}
