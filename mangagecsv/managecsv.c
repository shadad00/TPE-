#include "managecsv.h"
#include <stdlib.h>
#include <stdio.h>

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename) {
    FILE * pFile = fopen(filename, "r");
    if (pFile == NULL) {
        fprintf(stderr, "No se pudo abrir el archivo %s\n", filename) ; 
        exit(2);
    }
    return pFile;
}

/* Obtiene de una linea un campo determinado */
char * getfield (const char * line, size_t field) {
    char del[2] = ";";
	char * tok = strtok(line, del);
	size_t iter = 1;
	while (tok != NULL && iter < field) {
		tok = strtok(NULL, del);
        iter++;
	}
    return tok;
}

/* Funcion que retorna en parametros de salida los datos para civilTAD */
void getRegCIV(char * line, char ** neigh, size_t neighCol, long * pop, size_t popCol){
  short stored = 0;
	char * tok = strtok(line, DEL);
	size_t iter = 1;
	while (tok != NULL && stored < 2) { // 2 ES MAGIC NUMBER? Buscar alternativa
    if(iter == neighCol) { 
    //DILEMA!!!!!!!  VER NOTAS
      strcpy(*neigh, tok);
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

/* Funcion que retorna en parametros de salida los datos para botanicaTAD */
void getRegBOT(char * line, char ** neigh, size_t neighCol, char ** scName, size_t scNameCol, double * diam, size_t diamCol) {
  short stored = 0;
	char * tok = strtok(line, DEL);
	size_t iter = 1;
	while (tok != NULL && stored < 3) { 
    if(iter == neighCol) { 
      strcpy(*neigh, tok);
      stored++;
    }
    else if(iter == scNameCol) {
      strcpy(*scName, tok);
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
