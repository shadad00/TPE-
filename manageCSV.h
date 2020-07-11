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

//Ya valide en el main que VAN o BUE este definido
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

/*Se encarga de la lectura del archivo que contiene nombre de barrios y cantidad de
 * habitantes y de pasarlo al TAD respectivo
*/
bool readNeighs (civilADT civil, FILE * fNeighs);

/* Se encarga de la lectura del archivo que contiene nombre del barrio , nombre del arbol
 * y diametro del mismo.Transfiere la informacion recuperada al ADT correspondiente.
*/
bool readPlants(botanicalADT botanical, civilADT civil,FILE * fPlants);

/*** ESCRITURA  ***/
/*Crea un nuevo archivo de nombre queryName o lo abre si ya existiese y lo reescribe.
 * Le agrega el encabezado header1:header2
*/
FILE * newQuery (char header1[], char header2[], char queryName[]);

/*Carga en el archivo query el nombre de todos los barrios seguido de su cantidad de habitantes de 
 * manera decreciente por habitantes por barrio
 */
void q1 (FILE * query, civilADT civil);

/*Guarda en el archivo query el  nombre de los barrios seguido del cociente entre los arboles por cantidad de habi
 * tantes de manera decreciente 
*/
void q2 (FILE * query, civilADT civil);

/*Guarda en el archivo query el nombre de todos los arboles seguido del diametro promedio en orden
 * decreciente.
*/
void q3 (FILE * query, botanicalADT botanical);

#endif /*CSV.h*/
