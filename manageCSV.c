#include "manageCSV.h"
#include <stdbool.h>

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename) {

  FILE * pFile = fopen(filename, "r");
  if (pFile == NULL)
   {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", filename) ; 
    exit(2);
   }
  return pFile; 
}

/* Retorna en parametros de salida los datos a cargar en el civilADT leidos de una linea*/
static void getRegCIV(char * line, char * neigh, size_t neighCol, long * pop, size_t popCol){
  short stored = 0;
	char * tok = strtok(line, DEL);
	size_t iter = 1;
	while (tok != NULL && stored < 2) { // 2 ES MAGIC NUMBER? Buscar alternativa
    if(iter == neighCol) { 
      strcpy(neigh, tok);
      stored++;
    }
    else if(iter == popCol) {
      *pop = atoi(tok);
      stored++;
    }
		tok = strtok(NULL, DEL);
    iter++;
	}
    return;
}

/* Retorna en parametros de salida los datos a cargar en el botanicalADT leidos de una linea */
static void getRegBOT(char * line, char * neigh, size_t neighCol, char *scName, size_t scNameCol, double * diam, size_t diamCol) {
  short stored = 0;
    char * tok = strtok(line, DEL);
    size_t iter = 1;
    while (tok != NULL && stored < 3) { 
    if(iter == neighCol) { 
      strcpy(neigh, tok);
      stored++;
    }
    else if(iter == scNameCol) {
      strcpy(scName, tok);
      stored++;
    }
    else if(iter == diamCol) {
      *diam = atof(tok);
      stored++;
    }
        tok = strtok(NULL, DEL);
    iter++;
    }
    return;
}

/* Carga iterativamente la informacion de todo el archivo en el botanicTAD */
bool readPlants(botanicalADT botanical, civilADT civil, FILE * fPlants) {
  bool flag = true;
  double tempDiam;
  char tempNeigh[MAX_LENGTH];
  char tempArbol [MAX_LENGTH];
  char buf[MAX_LINE];
  //La primera linea del archivo es basura 
  fgets(buf, MAX_LINE, fPlants);
   //Para cualquier otra linea, debo almacenar esa informacion
     while(flag && (fgets(buf, MAX_LINE, fPlants) != NULL)){
       getRegBOT(buf, tempNeigh, BOT_NEIGH, tempArbol, BOT_TREE, &tempDiam, BOT_DIAM);
       addTree(civil, tempNeigh);
       flag = addPlant(botanical, tempArbol, tempDiam);
     }
  return flag;
}

/* Carga iterativamente la informacion de todo el archivo en el civilTAD */
bool readNeighs (civilADT civil, FILE * fNeighs){
  bool flag = true;
  long tempPop; 
  char tempNombre[MAX_LENGTH];
  char buf[MAX_LENGTH];
  
  //La primera linea del archivo es basura 
    fgets(buf, MAX_LINE, fNeighs);

  //Para cualquier otra linea, debo almacenar esa informacion
    while(flag && (fgets(buf, MAX_LINE, fNeighs) != NULL)){
      getRegCIV(buf, tempNombre, NEIGH_NAME, &tempPop, NEIGH_POP);
      flag = addNeigh(civil, tempNombre, tempPop);
    } 
  return flag;
}


/* Inicializa una nueva query vacia con dos titulares y un nombre de archivo */
FILE * newQuery (char header1[], char header2[], char queryName[]) {
  FILE * query = fopen(queryName, "w");
  fprintf(query, "%s%s%s\n", header1, DEL, header2);
  return query; 
}

/*Ejecuta los cambios necesarios y produce el query 1*/
void q1 (FILE * query, civilADT civil) {
  resetNeigh(civil);
    do {
     fprintf(query, "%s%s%zu\n", getNeighName(civil), DEL, getNeighTrees(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
   fclose(query);
}

/*Ejecuta los cambios necesarios y produce el query 2*/
void q2(FILE * query, civilADT civil) {
  resetNeigh(civil); 
  do {
    fprintf(query, "%s%s%.2f\n", getNeighName(civil), DEL, getTreesPerHab(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
  fclose(query);
}

/*Ejecuta los cambios necesarios y produce el query 3*/
void q3 (FILE * query, botanicalADT botanical) {
  resetPlant(botanical); 
  do {
    fprintf(query, "%s%s%.2f\n", getPlantName(botanical), DEL, getDiameter(botanical));
    nextPlant(botanical); 
  } while (! noMorePlants(botanical));
  fclose(query);
}