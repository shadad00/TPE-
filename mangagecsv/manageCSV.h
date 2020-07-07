/*
**  manageCSV.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  La biblioteca CSV.h permite manejar archivos .csv
**  Operaciones basicas de manejo de archivos:
**  apertura, lectura y escritura. 
*/

#include <string.h>
#include <stdlib.h>

#ifndef CSV_h
#define CSV_h

/*
** Libreria para lectura y almacenado de archivos .csv
*/

/* Delimitador de archivo csv */
#define DEL ";"

/*
** APERTURA
*/

/* Devuelve un puntero a filename. Aborta en caso de error */
FILE * loadFile (char * filename); 


/* 
** LECTURA
*/

/* Funcion que retorna en parametros de salida los datos para civilTAD */
void getRegCIV(char * line, char ** neigh, size_t neighCol, long * pop, size_t popCol);

/* Funcion que retorna en parametros de salida los datos para botanicaTAD */
void getRegBOT(char * line, char ** neigh, size_t neighCol, char ** scName, size_t scNameCol, double * diam, size_t diamCol) ;


/* 
** ESCRITURA
*/



#endif /*CSV.h*/
