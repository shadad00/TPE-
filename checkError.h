/*
**  checkError.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  Biblioteca para manejar errores comunes en el
**  procesamiento de informacion.
*/

#include <stdio.h>
#include <errno.h>
#include <stdbool.h>
#include <string.h>

/*
**  El siguiente conjunto de funciones devuelve 1 (true) si 
**  hallaron sus respectivos errores y 0 (false) si no hubo
**  error.
**  Hay errores esenciales que no permiten que el programa
**  se desarrolle y provocan un aborto en ejecucion.
**  Hay errores superficiales que, a pesar de ser errores,
**  permiten el desarrollo del programa y no abortan. 
**  Se le notifica al usuario de todos los errores
*/

#ifndef checkError_h
#define checkError_h

/*Revisa la memoria tras una asignacion e imprime el error en salida de errores.*/
bool checkMem (void);

/*Revisa si se pudo abrir el archivo e imprime el error en salida de errores.*/
bool checkFile (FILE * pFile, char * filename); 

/*Revisa si la cantidad de parametros es correcta e imprime el error en salida de errores.*/
bool checkArgs (size_t args);

/*Compara dos strings y decide si ya existia e  imprime un warning*/
bool checkRep (char * name1, char * name2);

/*Revisa si se estipulo un modo VAN o BUE en la compilacion e imprime el error en salida de errores.*/
bool checkMode (void);

#endif /*checkError.h*/