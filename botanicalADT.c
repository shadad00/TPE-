#include "botanicalADT.h"

#define EPSILON 0.01
/*Name: nombre del arbol
 * quantity: cantidad de ejemplares
 * diameter: suma de los diametros
*/
typedef struct tTree {
	char * name; 
	unsigned long quantity; 
	double diameter; 
} tTree; 
/* qSpecies:cantidad diferentes de especies de arboles
 * trees vector de punteros a tTree
 * current: indice del elemento actual sobre el que se esta interactuando
*/
typedef struct botanicalCDT {
  unsigned qSpecies;
  tTree ** trees;
  unsigned current;
} botanicalCDT; 

/*Crea un nuevo ADT*/
botanicalADT newBotanical() {
  botanicalADT aux = calloc(1, sizeof(botanicalCDT));
  //ASSERT ERRNO!! FALTA LO DE BENJA
  return aux;
}

static int checkMem (void * pointer) {
   if (errno == 12) {
    fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
    return 1; 
  }   
  return 0;
}



/*Libera los recursos ocupados por el CDT.
 *Primero libera el puntero al nombre del arbol
  Luego libera el puntero a la estructura y por ultimo libera
  el ADT
 **/
void freeBotanical(botanicalADT botanical) {
  for (int i=0; i<botanical->qSpecies; i++) {
    free(botanical->trees[i]->name);
    free(botanical->trees[i]);
  }
  free(botanical->trees);
  free(botanical);
}

bool addPlant(botanicalADT botanical, char * treeName, double diameter) {
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
  
  tTree ** aux=realloc(botanical->trees, sizeof(tTree *)*(i+1)); //CHEQUEAR ESTO
        if (checkMem(aux))
          return false;
  botanical->trees = aux; 
  //El vector es ahora lo suficientemente largo
  botanical->trees[i]=malloc(sizeof(tTree));
          if (checkMem(botanical->trees[i]))
            return false;
  botanical->trees[i]->diameter=diameter; 
  botanical->trees[i]->quantity=1;
  botanical->trees[i]->name=malloc(sizeof(char)*(strlen(treeName)+1)); 
        if (checkMem(botanical->trees[i]->name))
          return false;
  strcpy(botanical->trees[i]->name,  treeName); 
  botanical->qSpecies++;
  return true;  
}

/*Devuelve 1 si no hay mas elementos en el vector*/
int noMorePlants (botanicalADT botanical) {
  return botanical->current == botanical->qSpecies;
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

/*Retorna 1 si no se almaceno informacion en el CDT*/
static bool empty (botanicalADT botanical) {
  return !botanical->qSpecies; 
}

/*Retorna un puntero al noombre del arbol del elemento actual*/
char * getPlantName (botanicalADT botanical) {
  if (! empty(botanical)) 
    return botanical->trees[botanical->current]->name;
  else 
    return NULL; 
} 

/*Retorna la cantidad de ejemplares del arbol al que apunta el iterador*/
unsigned long getQPlant (botanicalADT botanical) {
  if (! empty(botanical)) 
    return botanical->trees[botanical->current]->quantity;
  else 
    return 0;
}

/*Calcula el cociente entre el diametro y la cantidad de ejemplares del elemento al que apunta tree*/
static double calcDiam (tTree * tree) {
  return tree->diameter/tree->quantity;
} 

/*Retorna el diametro promedio del elemento al que apunta el iterador*/
double getDiameter (botanicalADT botanical) {
  if (! empty(botanical)) 
    return calcDiam(botanical->trees[botanical->current]);
  else 
    return 0;
}


/*retorna 1 si elemento el diametro del elemento al que apunta a es mayor al diametro del ele
 * mento del que apunta b.
 * Es funcion auxiliar pasada por parametro al qsort.*/ 
static int compareDescDiamAscAlf (const void * a, const void * b) {
 
  tTree ** elem1 = (tTree **) a;
  tTree ** elem2 = (tTree **) b;
   

  double diam1 = calcDiam(*elem1);
  double diam2 = calcDiam(*elem2);

 
  if ( fabs(diam1-diam2)<EPSILON ) 
    return strcmp((*elem1)->name, (*elem2)->name);
  else
    return diam2 > diam1;
}

/*Ordena el vector de manera decreciente de acuerdo al diametro promedio de la especie*/
void sortDescDiamAscAlf (botanicalADT botanical) {
   qsort(botanical->trees, botanical->qSpecies, sizeof(tTree *), compareDescDiamAscAlf);
}
