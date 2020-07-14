#include <stdio.h>
#include "botanicalADT.h"
#include "civilADT.h"
#include "manageCSV.h"
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#define MEMMSG fprintf(stderr, "No hay memoria suficiente\n");
    
/* Libera la memoria utilizada y cierra los archivos abiertos */
void goodbye(FILE * f1, FILE * f2, botanicalADT botanical, civilADT civil);

int main (int argc, char * argv[]){

  /*Chequea si al compilar se definio VAN o BUE*/
  #if !defined BUE && !defined VAN
     fprintf(stderr, "Modo no definido o codigo AAA no valido.\n");
     return 1; 
  #endif 

  /*Chequea cantidad de parametros*/
	 if (argc != 3) {
    fprintf(stderr, "Cantidad de parametros incorrecta.\n");
    return 2; 
   }
  
	/*Preparacion inicial de los ADTs y archivos*/
  int flag;
  botanicalADT datosPlantas = newBotanical(&flag);
  FILE * pBarrios = NULL, * pArboles = NULL;

  /* Abre los archivos a ejecutar */
  pArboles = loadFile(argv[1]);
  pBarrios = loadFile(argv[2]);


  if ( flag ) {
    MEMMSG
    freeBotanical(datosPlantas);
    fclose(pArboles);
    fclose(pBarrios);
    return 4;
  }
  
  civilADT datosBarrios = newCivil(&flag);
  if ( flag ) {
    MEMMSG
    goodbye(pArboles, pBarrios, datosPlantas,datosBarrios);
    return 4;
  }
  
  /*Lectura de los archivos*/
  int c; 
  c = readNeighs(datosBarrios, pBarrios); 
	if( c == 0 ) {
    MEMMSG
    goodbye(pArboles, pBarrios, datosPlantas,datosBarrios);
    return 4; 
  } else if (c == -1 ) 
    fprintf(stderr, "Se detectaron e ignoraron registros repetidos en el csv de barrios.\n");
  

  c = readPlants(datosPlantas, datosBarrios, pArboles);
  if( c == 0 ) {
    MEMMSG
    goodbye(pArboles, pBarrios, datosPlantas,datosBarrios);
    return 4; 
  } else if (c == -1)
    fprintf(stderr, "No se contabilizaron arboles para ciertos barrios pues no estaban en el csv de barrios.\n");


  //Archivo para la Query1
  FILE * query1 = newQuery("BARRIO", "ARBOLES", "query1.csv");
	sortDescTreeAscAlf(datosBarrios);
	q1(query1, datosBarrios);
  

  // Archivo para la Query2
  FILE * query2 = newQuery("BARRIO", "ARBOLES_POR_HABITANTE", "query2.csv");
  sortDescTBHAscAlf(datosBarrios);
  q2(query2, datosBarrios);

  // Archivo para la Query3
  FILE * query3 = newQuery("NOMBRE_CIENTIFICO", "PROMEDIO_DIAMETRO", "query3.csv");
  sortDescDiamAscAlf (datosPlantas);
  q3(query3, datosPlantas);

  /*Liberacion de la memoria reservada*/
  goodbye(pArboles, pBarrios, datosPlantas, datosBarrios);

  return 0;
}


void goodbye(FILE * f1, FILE * f2, botanicalADT botanical, civilADT civil) {
  freeBotanical(botanical);
	freeCivil(civil);
  fclose(f1);
  fclose(f2);
}



