#include <stdio.h>
#include "botanicalADT.h"
#include "civilADT.h"
#include "manageCSV.h"
#include <errno.h>
#include "checkError.h"
#include <stdlib.h>
#include <math.h>

/* Libera la memoria utilizada y cierra los archivos abiertos */
void goodbye(FILE * f1, FILE * f2, botanicalADT botanical, civilADT civil);

int main (int argc, char * argv[]){

  /*Chequea si al compilar se definio VAN o BUE*/
  if (! checkMode() ) 
    return 1;
  
  /*Chequea cantidad de parametros*/
	 if (! checkArgs(argc) ) 
	   return 2;
   
	/*Preparacion inicial de los ADTs y archivos*/
  int flag;
  botanicalADT datosPlantas = newBotanical(&flag);

  if ( !flag ) {
    freeBotanical(datosPlantas);
    return 4;
  }

  civilADT datosBarrios = newCivil(&flag);
  if ( !flag ) {
    freeBotanical(datosPlantas);
    freeCivil(datosBarrios);
    return 4;
  }
  
  FILE * pBarrios = NULL, * pArboles = NULL;

  /* Abre los archivos a ejecutar */
  pArboles = loadFile(argv[1]);
  pBarrios = loadFile(argv[2]);


  /*Lectura de los archivos*/
	if( ! readNeighs(datosBarrios, pBarrios)) {
    goodbye(pArboles, pBarrios, datosPlantas, datosBarrios);
    return 4; 
  }
  
  if( ! readPlants(datosPlantas, datosBarrios, pArboles)) {
    goodbye(pArboles, pBarrios, datosPlantas,datosBarrios);
    return 4; 
  }


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



