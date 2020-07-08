/*
**  manageCSV.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  La biblioteca manageCSV.h permite manejar archivos .csv para la realizacion de queries especificos.
**  Operaciones basicas de manejo de archivos:
**  apertura, lectura, almacenaje y escritura. 
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "botanicalADT.h"
#include "civilADT.h"

#ifndef manageCSV_h
#define manageCSV_h

/* Delimitador de archivo csv */
#define DEL ";"
/*Maximo lugar ocupable por una linea*/
#define MAX_LINE 1024
/*Maximo lugar ocupable por un campo*/
#define MAX_LENGTH 128

/*** APERTURA  ***/

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename); 

/*** LECTURA  ***/

/* Retorna en parametros de salida los datos a cargar en el civilADT leidos de una linea*/
void getRegCIV(char * line, char * neigh, size_t neighCol, long * pop, size_t popCol);

/* Retorna en parametros de salida los datos a cargar en el botanicalADT leidos de una linea*/
void getRegBOT(char * line, char * neigh, size_t neighCol, char * scName, size_t scNameCol, double * diam, size_t diamCol) ;

/**Carga iterativamente la informacion de todo el archivo en el civilTAD**/
void readNeighs (civilADT civil, FILE * fNeighs);

/**Carga iterativamente la informacion de todo el archivo en el botanicTAD**/
void readPlants(botanicalADT botanical, civilADT civil,FILE * fPlants);

/*** ESCRITURA  ***/

/*Inicializa una nueva query vacia con dos titulares y un nombre de archivo*/
//STATIC O SIRVE PARA ALGO?
FILE * newQuery (char header1[], char header2[], char queryName[]);


/*Ejecuta los cambios necesarios y produce el query 1*/
void q1 (FILE * query, civilADT civil);

/*Ejecuta los cambios necesarios y produce el query 2*/
void q2 (FILE * query, civilADT civil);

/*Ejecuta los cambios necesarios y produce el query 3*/
void q3 (FILE * query, botanicalADT botanical);




#endif /*CSV.h*/