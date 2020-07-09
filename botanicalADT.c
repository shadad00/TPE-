#include "botanicalADT.h"
#include <math.h>
#define EPSILON 0.01

typedef struct tTree {
	char * name; 
	unsigned long quantity; 
	double diameter; 
} tTree; 

typedef struct botanicalCDT {
  unsigned qSpecies;
  tTree ** trees;
  unsigned current;
} botanicalCDT; 

botanicalADT newBotanical() {
  botanicalADT aux = calloc(1, sizeof(botanicalCDT));
  //ASSERT ERRNO!! FALTA LO DE BENJA
  return aux;
}


void freeBotanical(botanicalADT botanical) {
  for (int i=0; i<botanical->qSpecies; i++) {
    free(botanical->trees[i]->name);
    free(botanical->trees[i]);
  }
  free(botanical->trees);
  free(botanical);
}

static bool isNULL (void * p) {
  return (p == NULL);
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
       // if (isNULL(botanical->trees[i]->name))
         // return false;
  botanical->trees = aux; 

  //El vector es ahora lo suficientemente largo
  botanical->trees[i]=malloc(sizeof(tTree));
        //if (isNULL(botanical->trees[i]))
          //return false;
  botanical->trees[i]->diameter=diameter; 
  botanical->trees[i]->quantity=1;
  botanical->trees[i]->name=malloc(sizeof(char)*(strlen(treeName)+1)); 
       // if (isNULL(botanical->trees[i]->name))
         // return false;
  strcpy(botanical->trees[i]->name,  treeName); 
  botanical->qSpecies++;
  return true;  
}

int noMorePlants (botanicalADT botanical) {
  return botanical->current == botanical->qSpecies;
}

void resetPlant (botanicalADT botanical) {
  botanical->current = 0; 
}

void nextPlant (botanicalADT botanical) {
  if (! noMorePlants(botanical)) 
    botanical->current ++; 
}

static bool empty (botanicalADT botanical) {
  return !botanical->qSpecies; 
}

char * getPlantName (botanicalADT botanical) {
  if (! empty(botanical)) 
    return botanical->trees[botanical->current]->name;
  else 
    return NULL; 
} 

unsigned long getQPlant (botanicalADT botanical) {
  if (! empty(botanical)) 
    return botanical->trees[botanical->current]->quantity;
  else 
    return 0;
}

static double calcDiam (tTree * tree) {
  return tree->diameter/tree->quantity;
} 

double getDiameter (botanicalADT botanical) {
  if (! empty(botanical)) 
    return calcDiam(botanical->trees[botanical->current]);
  else 
    return 0;
}


void printBotanical (botanicalADT botanical) {
  resetPlant(botanical);
  while (! noMorePlants(botanical)) {
    printf("%s\t%zu\t%3f\n", getPlantName(botanical), getQPlant(botanical), getDiameter(botanical)); 
    nextPlant(botanical);
  }
}
 
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

void sortDescDiamAscAlf (botanicalADT botanical) {
   qsort(botanical->trees, botanical->qSpecies, sizeof(tTree *), compareDescDiamAscAlf);
}