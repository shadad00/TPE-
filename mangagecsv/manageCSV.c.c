#include "manageCSV.h"



FILE * loadFile (char * filename) {

  FILE * pFile = fopen(filename, "r");
  if (pFile == NULL)
   {
    fprintf(stderr, "No se pudo abrir el archivo %s\n", filename) ; 
    exit(2);
   }

  return pFile; 
}

// int checkMem (void * pointer) {
//   if (pointer == NULL) {
//     fprintf(stderr, "Fallo en la asignación de memoria\n") ; 
//   }
//   return 1;
// }


void getRegCIV(char * line, char * neigh, size_t neighCol, long * pop, size_t popCol){
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

void getRegBOT(char * line, char * neigh, size_t neighCol, char *scName, size_t scNameCol, double * diam, size_t diamCol) {
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

void readPlants(botanicalADT botanical, civilADT civil, FILE * fPlants) {

  double tempDiam;
  char tempNeigh[MAX_LENGTH];
  char tempArbol [MAX_LENGTH];
  char buf[MAX_LINE];
  //La primera linea del archivo es basura 
  fgets(buf, MAX_LINE, fPlants);
   //Para cualquier otra linea, debo almacenar esa informacion
     while(fgets(buf, MAX_LINE, fPlants) != NULL){
       getRegBOT(buf, tempNeigh, 3, tempArbol, 8, &tempDiam, 12);
       addTree(civil, tempNeigh);
       addPlant(botanical, tempArbol, tempDiam);
     } 
}

void readNeighs (civilADT civil, FILE * fNeighs){

  long tempPop; 
  char tempNombre[MAX_LENGTH];
  char buf[MAX_LENGTH];
  
  //La primera linea del archivo es basura 
    fgets(buf, MAX_LINE, fNeighs);

  //Para cualquier otra linea, debo almacenar esa informacion
    while(fgets(buf, MAX_LINE, fNeighs) != NULL){
      getRegCIV(buf, tempNombre, 1, &tempPop, 2);
      addNeigh(civil, tempNombre, tempPop);
    } 
 
}



FILE * newQuery (char header1[], char header2[], char queryName[]) {
  FILE * query = fopen(queryName, "w");
  fprintf(query, "%s%s%s\n", header1, DEL, header2);
  return query; 
}


////MODULARIZAR Y SEPARAR !!!!!!!!!!!!!!!!!!
void q1 (FILE * query, civilADT civil) {
  FILE * query1=newQuery("BARRIO", "ARBOLES", "query1.csv");
  sortDescTreeAscAlf(civil);
  resetNeigh(civil); 
  do {
    fprintf(query1, "%s%s%zu\n", getNeighName(civil), DEL, getNeighTrees(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
  fclose(query1);
}

void q2(FILE * query, civilADT civil) {
  FILE * query2=newQuery("BARRIO", "ARBOLES_POR_HABITANTE", "query2.csv");
  sortDescTBHAscAlf(civil);
  resetNeigh(civil); 
  do {
    fprintf(query2, "%s%s%.2f\n", getNeighName(civil), DEL, getTreesPerHab(civil));
    nextNeigh(civil); 
  } while (! noMoreNeighs(civil));
  fclose(query2);
}

void q3 (FILE * query, botanicalADT botanical) {
  FILE * query3=newQuery("NOMBRE_CIENTIFICO", "PROMEDIO_DIAMETRO", "query3.csv");
  sortDescDiamAscAlf (botanical);
  resetPlant(botanical); 
  do {
    fprintf(query3, "%s%s%.2f\n", getPlantName(botanical), DEL, getDiameter(botanical));
    nextPlant(botanical); 
  } while (! noMorePlants(botanical));
  fclose(query3);
}