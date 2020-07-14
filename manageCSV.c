#include "manageCSV.h"

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename) {
  FILE * pFile = fopen(filename, "r");
  if (! checkFile(pFile, filename)) 
    exit(3); //Es una funcion de front, puede hacer exit
  return pFile; 
}

/* Retorna en parametros de salida los datos a cargar en el civilADT leidos de una linea*/
static void getRegCIV(char * line, char * neigh, size_t neighCol, long * pop, size_t popCol){
  //stored es un flag que lleva la cuenta de cuantos
  //campos fueron ya leidos
  short stored = 0;
	char * tok = strtok(line, DEL);
  //El iterador marca la iter-esima columna
	size_t iter = 1;
	while (tok != NULL && stored < NUMCOLSCIV) { 
    if(iter == neighCol) { 
      strcpy(neigh, tok);
      stored++;
    } else if(iter == popCol) {
      *pop = atoi(tok);
      stored++;
    }
		tok = strtok(NULL, DEL);
    iter++;
	}
}

/* Retorna en parametros de salida los datos a cargar en el botanicalADT leidos de una linea */
static void getRegBOT(char * line, char * neigh, size_t neighCol, char *scName, size_t scNameCol, float * diam, size_t diamCol) {
  short stored = 0;
    char * tok = strtok(line, DEL);
    size_t iter = 1;
    while (tok != NULL && stored < NUMCOLSBOT) { 
      if(iter == neighCol) { 
        strcpy(neigh, tok);
        stored++;
      }else if(iter == scNameCol) {
        strcpy(scName, tok);
        stored++;
      }else if(iter == diamCol) {
        *diam = atof(tok);
        stored++;
      } 
      tok = strtok(NULL, DEL);
      iter++;
    }
}

/* Carga iterativamente la informacion de todo el archivo en el botanicTAD */
bool readPlants(botanicalADT botanical, civilADT civil, FILE * fPlants) {
  bool flag = true;
  //Variables dummy para hacer el paso del csv al tad
  float tempDiam;
  char tempNeigh[MAX_LENGTH];
  char tempArbol [MAX_LENGTH];
  char buf[MAX_LINE];
  //La primera linea del archivo es basura 
  fgets(buf, MAX_LINE, fPlants);
  //Para cualquier otra linea, debo almacenar esa informacion
  while(flag && (fgets(buf, MAX_LINE, fPlants) != NULL)){
    getRegBOT(buf, tempNeigh, BOT_NEIGH, tempArbol, BOT_TREE, &tempDiam, BOT_DIAM);
    if ( ! addTree(civil, tempNeigh) ) 
      fprintf(stderr, "No se contabiliza un arbol para el barrio \"%s\" pues no esta en el csv de barrios.\n", tempNeigh);
    flag = addPlant(botanical, tempArbol, tempDiam);
  }
  return flag;
}

/* Carga iterativamente la informacion de todo el archivo en el civilTAD */
bool readNeighs (civilADT civil, FILE * fNeighs){
  bool flag = true;
  long tempPop; 
  char tempNombre[MAX_LENGTH];
  char buf[MAX_LINE];
  //La primera linea del archivo es basura 
  fgets(buf, MAX_LINE, fNeighs);
  //Para cualquier otra linea, debo almacenar esa informacion
    while( flag && (fgets(buf, MAX_LINE, fNeighs) != NULL) ){
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

bool q1 (FILE * query, civilADT civil) {
  if( isEmptyCivil(civil) ) {
    fprintf(stderr, "No hay informacion para producir el query 1.\n");
    return false;
  }
  resetNeigh(civil);
  do{
    char * barrio=getNeighName(civil);
    long arboles=getNeighTrees(civil);
    fprintf(query, "%s%s%zu\n",barrio , DEL, arboles);
    nextNeigh(civil); 
  } while( ! noMoreNeighs(civil) );
  fclose(query);
  return true;
}

bool q2(FILE * query, civilADT civil) {
  if( isEmptyCivil(civil) ) {
    fprintf(stderr, "No hay informacion para producir el query 2.\n");
    return false;
  }
  resetNeigh(civil); 
  do{
    char * barrio=getNeighName(civil);
    float Arbxhab=getTreesPerHab(civil);
    if(barrio==NULL|| Arbxhab < 0)
      return false;
    fprintf(query, "%s%s%.2f\n",barrio , DEL,Arbxhab);
    nextNeigh(civil); 
  }while (! noMoreNeighs(civil));
  fclose(query);
  return true;
}

bool q3 (FILE * query, botanicalADT botanical) {
  if( isEmptyBotanical(botanical) ) {
    fprintf(stderr, "No hay informacion para producir el query 3.\n");
    return false;
  }
  resetPlant(botanical); 
  do {
    char * planta=getPlantName(botanical);
    float diametro=getDiameter(botanical);
    if( planta==NULL || diametro < 0)
      return false;
    fprintf(query, "%s%s%.2f\n", planta, DEL, diametro);
    nextPlant(botanical); 
    } while (! noMorePlants(botanical));
  fclose(query);
  return true;

}


