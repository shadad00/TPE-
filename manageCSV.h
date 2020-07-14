/*
**  manageCSV.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  La biblioteca manageCSV.h permite manejar archivos
**  csv para la realizacion de queries especificos.
**  Operaciones basicas de manejo de archivos:
**  apertura, lectura, almacenaje y escritura. 
**
**  Se trata de una biblioteca independiente
**  pero muy atada al procesamiento de arboles
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "botanicalADT.h"
#include "civilADT.h"
#include <stdbool.h>
#include <math.h>


//Ya valide en el main que VAN o BUE este definido
//Columnas donde se encuentra cada informacion necesaria
#ifdef VAN
#define NEIGH_NAME 1
#define NEIGH_POP 2
#define BOT_NEIGH 13
#define BOT_TREE 7
#define BOT_DIAM 16
#else
#define NEIGH_NAME 1
#define NEIGH_POP 2
#define BOT_NEIGH 3
#define BOT_TREE 8
#define BOT_DIAM 12
#endif

// Cantidad de columnas de los archivos a crear
#define NUMCOLSCIV 2
#define NUMCOLSBOT 3

/* Delimitador de archivo csv */
#define DEL ";"

/*Maximo lugar ocupable por una linea*/
#define MAX_LINE 1024

/*Maximo lugar ocupable por un campo*/
#define MAX_LENGTH 128

#ifndef manageCSV_h
#define manageCSV_h

/*** APERTURA  ***/

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename); 

/*** LECTURA  ***/

/**Carga iterativamente la informacion de todo el archivo en el civilTAD**/
/*Devuelve  0 si fallo, 1 si tuvo exito y -1 si hubo barrios repetidos*/
int readNeighs (civilADT civil, FILE * fNeighs);

/**Carga iterativamente la informacion de todo el archivo en el botanicTAD**/
/**Devuelve 0 si fallo, 1 si exito y -1 si habia un barrio inexistente en el csv de barrios en el csv de arboles**/
int readPlants(botanicalADT botanical, civilADT civil,FILE * fPlants);

/*** ESCRITURA  ***/

/*Inicializa una nueva query vacia con dos titulares y un nombre de archivo*/
//STATIC O SIRVE PARA ALGO?
FILE * newQuery (char header1[], char header2[], char queryName[]);



/*Retornan verdadero o falso dependiendo si fallan en el cargado de los datos o no respectivamente*/

/*Ejecuta los cambios necesarios y produce el query 1*/
bool q1 (FILE * query, civilADT civil);

/*Ejecuta los cambios necesarios y produce el query 2*/
bool q2 (FILE * query, civilADT civil);

/*Ejecuta los cambios necesarios y produce el query 3*/
bool q3 (FILE * query, botanicalADT botanical);

#endif /*CSV.h*/