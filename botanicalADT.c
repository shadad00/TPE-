#include "botanicalADT.h"
#define BLOCK 10
#define EPSILON 0.001

typedef struct treeType { //elemento del vector 
	char * name; 
	unsigned long quantity; //cantidad de ejemplares
	double diameter; //suma total de los diametros recolectados
} treeType; 

typedef struct botanicalCDT {
	unsigned long qTrees; 
	unsigned qSpecies; //dimension del vector 
	treeType * trees;  //puntero al primer elemento del vector de estructuras
  unsigned current; 
} botanicalCDT;

/*Inicializa un nuevo TAD */
botanicalADT newBotanical() {
	botanicalADT aux = calloc(1, sizeof(botanicalCDT)); 
	if (aux == NULL) {
    fprintf(stderr, "Fallo en la asignación de memoria\n") ;
    exit(2); 
  }
	return aux; 
}  


/*Libera los recursos utilizados por el TAD*/
void freeBotanical(botanicalADT botanical) {	
	for (int i=0; i<botanical->qSpecies; i++) {
		free(botanical->trees[i].name); //liberando el nombre de cada arbol
	}
  free(botanical->trees); //liberando el vector
	free(botanical);	//el ADT
}

/*Agrega en el vector la planta*/
void addPlant(botanicalADT botanical, char * treeName, double diameter) {
 
	botanical->qTrees ++; /*Cantidad de arboles ¿?*/

  for (int i=0; i<botanical->qSpecies; i++) {
	//revisa si existe ya el nodo
		if (strcmp(botanical->trees[i].name, treeName) == 0) {
			botanical->trees[i].diameter +=diameter; 
			botanical->trees[i].quantity ++; 
			return; 
		}; 
  }
  
  	//Si llego hasta aca quiere decir que no existia esa especie en la coleccion
  //  if (botanical->qSpecies % BLOCK == 0) {

		  botanical->trees = realloc(botanical->trees, sizeof(treeType)*(botanical->qSpecies+1/*BLOCK*/));
     /*CHEQUEAR MEMORIA SIN PERDER TODOS LOS DATOS*/

      if (botanical->trees == NULL) {
        fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
        exit(2);
      }
   // }

   
		botanical->trees[botanical->qSpecies].diameter = diameter; 
		botanical->trees[botanical->qSpecies].quantity=1;
		botanical->trees[botanical->qSpecies].name = malloc(sizeof(char)*(strlen(treeName)+1)); 

    if (botanical->trees[botanical->qSpecies].name == NULL) {
        fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
        exit(2);
      }

    
    strcpy(botanical->trees[botanical->qSpecies].name, treeName); 
    
    botanical->qSpecies ++; //se incrementa la dimension del vector
	}

void printBotanical (botanicalADT botanical) {
  printf("%10s %5s %5s\n", "ESPECIE", "CANT", "DIAM");
  for (int i=0; i<botanical->qSpecies; i++) {
    printf("%10s %5zu %5f\n", botanical->trees[i].name, botanical->trees[i].quantity, botanical->trees[i].diameter);
  }
}

int noMorePlants (botanicalADT botanical) {
  return (botanical->current == botanical->qSpecies); 
}

void resetPlant (botanicalADT botanical) {
  botanical->current=0;
}

void nextPlant (botanicalADT botanical) {
  if (! noMorePlants(botanical))
    botanical->current ++; 
}

char * getPlantName (botanicalADT botanical) {
  return(botanical->trees[botanical->current]).name;
}

unsigned long getQPlant (botanicalADT botanical) {
  return(botanical->trees[botanical->current]).quantity;
}

double getDiameter (botanicalADT botanical) {
  return(botanical->trees[botanical->current]).diameter;
}




/*Ordena el vector  segun diámetro promedio decreciente*/
void sortDescDiamAscAlf (botanicalADT botanical) {

/*para cada elemento del vector recorro hasta el final e intercambio con el mas chico*/
double  mayor;
int indiceMayor;
struct treeType aux;
int c;

for(int i = 0 ; i < botanical->qSpecies-1 ; i++ ){
  indiceMayor=i;
  mayor=(botanical->trees[i].diameter/(double)botanical->trees[i].quantity); 
  for(int j=i+1 ; j < botanical->qSpecies ; j++){
    
    double actual=(botanical->trees[j].diameter/(double)botanical->trees[j].quantity);
    if( actual > mayor){
      mayor=actual;
      indiceMayor=j;
    }else if( (mayor - actual) < EPSILON && (c=strcmp(botanical->trees[indiceMayor].name, botanical->trees[j].name) > 0 )) {
      mayor = actual;
      indiceMayor=j;   /*Estan separados por claridad podrian unificarse en un if*/

    }
   }
  
  //intercambio el primero con el menor
  aux=botanical->trees[indiceMayor];
  botanical->trees[indiceMayor]=botanical->trees[i];
  botanical->trees[i]=aux;

}
}


void Query3(botanicalADT botanical,FILE * archivo){
  for(int i = 0 ;i < botanical->qSpecies;i++)
    fprintf(archivo,"\n%s;%.2f",botanical->trees[i].name,botanical->trees[i].diameter/(float)botanical->trees[i].quantity);
 /*Cerrar el archivo deberia ir en el main*/
  fclose(archivo);
}


/*funcion de testeo*/
 int CantidadArboles(botanicalADT botanical)
 {
   return botanical->qSpecies; //retorna la dimension del vector
 }




void printSpecies(botanicalADT botanical) {

  printf("%d", botanical->qSpecies); 

}


