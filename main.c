#include <stdio.h>
#include "botanicalADT.h"
#include "civilADT.h"
#include "manageCSV.h"
#include <errno.h>

/* Libera la memoria utilizada y cierra los archivos abiertos */
void goodbye(FILE * f1, FILE * f2, botanicalADT botanical, civilADT civil);

int main (int argc, char * argv[]){

  #if !defined BUE && !defined VAN
   fprintf(stderr, "Modo no definido o codigo no valido\n");
   return 2; 
  #endif 

/*Chequear cantidad de parametros, en caso de error aborta la ejecucion*/
   if (argc != 3) {
	fprintf(stderr, "Cantidad de parametros incorrecta\n"); 
	return 1;
   }
 
/*Preparacion inicial de los ADTs y archivos*/
  botanicalADT datosPlantas = newBotanical();
  civilADT datosBarrios = newCivil();
  FILE * pBarrios = NULL, * pArboles = NULL;
  

/* Abre los archivos a ejecutar, en caso de error aborta la ejecucion */
  pBarrios = loadFile(argv[2]);
  if (errno == 2) {
       return errno; 
  } 

  pArboles = loadFile(argv[1]);
   if(errno == 2) {
      fclose(pBarrios);
      return errno;
  }


/*Lectura de los archivos*/
   if(readNeighs(datosBarrios, pBarrios) != true) {
       goodbye(pArboles, pBarrios, datosPlantas, datosBarrios);
  }
  

   if(readPlants(datosPlantas, datosBarrios, pArboles) != true) {
       goodbye(pArboles, pBarrios, datosPlantas,datosBarrios);
  }
  
  
 
/*Archivo para la Query1*/ 
   FILE * query1 = newQuery("BARRIO", "ARBOLES", "query1.csv");
       sortDescTreeAscAlf(datosBarrios);
       q1(query1, datosBarrios);	
  
  
/*Archivo para la Query2*/
   FILE * query2 = newQuery("BARRIO", "ARBOLES_POR_HABITANTE", "query2.csv");
       sortDescTBHAscAlf(datosBarrios);
       q2(query2, datosBarrios);	
  
/* Archivo para la Query3*/
   FILE * query3 = newQuery("NOMBRE_CIENTIFICO", "PROMEDIO_DIAMETRO", "query3.csv");
       sortDescDiamAscAlf (datosPlantas);
       q3(query3, datosPlantas);	

	
  /*Liberacion de la memoria reservada*/
  goodbye(pArboles, pBarrios, datosPlantas, datosBarrios);

  
   return 0;
} 

/*Libera toda la memoria reservada durante la ejecucion del programa*/
void goodbye(FILE * f1, FILE * f2, botanicalADT botanical, civilADT civil) {
  freeBotanical(botanical);
  freeCivil(civil); 
  fclose(f1);
  fclose(f2);
}
