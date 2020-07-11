#include "manageCSV.h"
#include <stdbool.h>

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename) {
//deberia chequear errno
  FILE * pFile = fopen(filename, "r");
  if (pFile == NULL)
   {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", filename) ; 
    exit(2);
   }
  return pFile; 
}

/* Retorna en parametros de salida los datos a cargar en el civilADT leidos de una linea
 * NeighCol es el numero de columna en la que esta el nombre del barrio en el archivo.
 * popCol es el numero de columna en la que se especifica la cantidad de habitantes de cada barrio en el archivo.
 * line es una linea del archivo.
 *
 * */
static void getRegCIV(char * line, char * neigh, size_t neighCol, long * pop, size_t popCol){
  short stored = 0;
	char * tok = strtok(line, DEL);
	size_t iter = 1;
	while (tok != NULL && stored < 2) { // 2 ES MAGIC NUMBER? Buscar alternativa // chequear que ambas condiciones sean Necesarias.
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

/* Retorna en parametros de salida los datos a cargar en el botanicalADT leidos de una linea 
  neighcol es el numero de columna donde se almacena el nombre del barrio en el archivo
  scname numero de columna donde se guarda el nombre del arbol
  diamCol numero de columna donde se guarda el diametro del arbol
*/
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

/* funcion que se encarga de procesar los datos del archivo que contiene el nombre del arbol
 * , el nombre del barrio y el diametro.
 * Pasa la informacion a los respectivos CDTs.
  Devuelve true or false dependiendo si falla el proceso de almacenamiento o no.
*/
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

/* Carga iterativamente la informacion de todo el archivo que contiene nombre del barrio
 * y cantidad de habitantes en el civilTAD 
 * Devuelve true or false dependiendo si falla o no el proceso de almacenamiento de la in
 * fomacion.
*/
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


/* Crea un nuevo archivo de nombre queryName en el cual se puede escribir informacion.
 * Agrega el encabezado en el mismo header1;header2
*/
FILE * newQuery (char header1[], char header2[], char queryName[]) {
  FILE * query = fopen(queryName, "w");
  fprintf(query, "%s%s%s\n", header1, DEL, header2);
  return query; 
}




/* Carga en el archivo query el nombre de todos los barrios seguido de su cantidad de 
 * arboles en orden decreciente por arboles por barrios.
*/

void q1 (FILE * query, civilADT civil) {
  resetNeigh(civil);
    do {
     fprintf(query, "%s%s%zu\n", getNeighName(civil), DEL, getNeighTrees(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
   fclose(query);
}

/* Carga en el archivo query el nombre de todos los barrios y el cociente entre 
 * cantidad de arboles y cantidad de habitantes. Lo hace de manera decreciente.
*/
void q2(FILE * query, civilADT civil) {
  resetNeigh(civil); 
  do {
    fprintf(query, "%s%s%.2f\n", getNeighName(civil), DEL, getTreesPerHab(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
  fclose(query);
}

/* Carga en el archivo query el nombre de todos los arboles y sus respectivos diametros promedios
 * ordenados de manera decreciente.
*/
void q3 (FILE * query, botanicalADT botanical) {
  resetPlant(botanical); 
  do {
    fprintf(query, "%s%s%.2f\n", getPlantName(botanical), DEL, getDiameter(botanical));
    nextPlant(botanical); 
  } while (! noMorePlants(botanical));
  fclose(query);
}
