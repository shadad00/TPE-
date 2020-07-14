#include "botanicalADT.h"
#include "checkError.h"

#define EPSILON 0.001

typedef struct tTree {
	char * name; //Nombre de la especie
	unsigned long quantity; //Cantidad de la misma especie
	float diameter; //Suma de los diametros
} tTree; 

typedef struct botanicalCDT {
  size_t qSpecies; //Cantidad de especies distintias
  tTree ** trees;
  size_t current;
} botanicalCDT; 

botanicalADT newBotanical (int * flag) {
  botanicalADT aux = calloc(1, sizeof(botanicalCDT));
  *flag=checkMem();
  return aux;
}

/*Libera los recursos ocupados por el ADT.
 *Primero libera el puntero al nombre del arbol
  Luego libera el puntero a la estructura y por ultimo libera el ADT
 **/
void freeBotanical(botanicalADT botanical) {
  for (int i=0; i<botanical->qSpecies; i++) {
    free(botanical->trees[i]->name);
    free(botanical->trees[i]);
  }
  free(botanical->trees);
  free(botanical);
}

bool addPlant(botanicalADT botanical, char * treeName, float diameter) {
  //Chequea si el arbol ya existe
  //Si existe, actualiza los datos y lo populariza
  int i; 
  for (i=0; i<botanical->qSpecies; i++) {
    if (strcmp(botanical->trees[i]->name, treeName) == 0) {
      botanical->trees[i]->diameter+=diameter;
      botanical->trees[i]->quantity++;
      //Populariza el elemento 
      if (i!=0) {
      tTree * aux = botanical->trees[i];
      botanical->trees[i]=botanical->trees[i-1];
      botanical->trees[i-1]=aux; 
      }
      return true; 
    }
  }

  //Si llego hasta aca, el arbol no existe
  //Agrego el arbol al final
  //Primero agrando al vector
  
  tTree ** aux=realloc(botanical->trees, sizeof(tTree *)*(i+1)); 
  if (!checkMem())
    return false;
  botanical->trees = aux; 
  

  //El vector es ahora lo suficientemente largo
  botanical->trees[i]=malloc(sizeof(tTree));
  if (!checkMem())
    return false;
  botanical->trees[i]->diameter=diameter; 
  botanical->trees[i]->quantity=1;
  botanical->trees[i]->name=malloc(sizeof(char)*(strlen(treeName)+1)); 
  if (!checkMem())
    return false;
  strcpy(botanical->trees[i]->name,  treeName); 
  botanical->qSpecies++;
  return true;  
}

/*Funcion auxiliar que trunca a dos decimales*/
static float truncate(float numero){
  numero*=100;
  numero=(int)(numero);
  return numero/100;
}

/*Devuelve 1 si no hay mas elementos en el vector*/
int noMorePlants (botanicalADT botanical) {
  return (isEmptyBotanical(botanical) || botanical->current == botanical->qSpecies);
}

/*Reinicia el iterador*/
void resetPlant (botanicalADT botanical) {
  botanical->current = 0; 
}

/*Aumenta en uno al iterador*/
void nextPlant (botanicalADT botanical) {
  if (! noMorePlants(botanical)) 
    botanical->current ++; 
}

/*Retorna 1 si no se almaceno informacion en el ADT*/
bool isEmptyBotanical (botanicalADT botanical) {
  return botanical==NULL || !botanical->qSpecies; 
}

/*Retorna un puntero al noombre del arbol del elemento actual*/
char * getPlantName (botanicalADT botanical) {
  if (isEmptyBotanical(botanical)) 
    return NULL;
  return botanical->trees[botanical->current]->name; 
} 

/*Retorna la cantidad de ejemplares del arbol al que apunta el iterador*/
unsigned long getQPlant (botanicalADT botanical) {
  if (isEmptyBotanical(botanical)) 
      return -1;
  
   return botanical->trees[botanical->current]->quantity;
}

/*Funcion auxiliar que calcula el cociente entre el diametro y la cantidad de ejemplares del elemento al que apunta tree*/
static float calcDiam (tTree * tree) {
  if( tree != NULL && tree->quantity != 0)
    return truncate(tree->diameter/tree->quantity);
  else
    return -1;
} 

/*Retorna el diametro promedio del elemento al que apunta el iterador*/
float getDiameter (botanicalADT botanical) {
  if (isEmptyBotanical(botanical)) 
    return -1;
  return calcDiam(botanical->trees[botanical->current]);
}


/*Retorna 1 si elemento el diametro del elemento al que apunta a es mayor al diametro del elemento del que apunta b.
Es funcion auxiliar pasada por parametro al qsort.*/ 
static int compareDescDiamAscAlf (const void * a, const void * b) {
 
  tTree ** elem1 = (tTree **) a;
  tTree ** elem2 = (tTree **) b;
   

  float diam1 = calcDiam(*elem1);
  float diam2 = calcDiam(*elem2);

 
  if ( fabs(diam1-diam2)<EPSILON ) 
    return strcmp((*elem1)->name, (*elem2)->name);
  else
    return diam2 > diam1;
}

/*Ordena el vector de manera decreciente de acuerdo al diametro promedio de la especie y luego alfabeticamente*/
void sortDescDiamAscAlf (botanicalADT botanical) {
  if (! isEmptyBotanical(botanical))
     qsort(botanical->trees, botanical->qSpecies, sizeof(tTree *), compareDescDiamAscAlf);
}