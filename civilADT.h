/*
**  civilADT.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  El TAD civilADT.h permite almacenar una coleccion
**  de datos geograficos, demograficos y antropologicos
**  de una ciudad.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>

#ifndef civilADT_h
#define civilADT_h

typedef struct civilCDT * civilADT;

/*
Inicializa un nuevo ADT
*/
civilADT newCivil();

/*
Libera los recursos usados por el TAD
*/
void freeCivil(civilADT civil);

/*
Guarda la informacion de cada barrio con su
cantidad de habitantes.No admite barrios repetidos,ignorandolos. 
*/
int addNeigh(civilADT civil,char * barrio, unsigned long habitantes);

/*
Incrementa en uno la cantidad de arboles del 
barrio. Devuelve falso si el barrio no existia.  
*/
int addTree(civilADT civil, char * barrio);

/*
** Funciones para poder iterar. 
*/

/*Deuelve 1 si no hay mas barrios en la coleccion*/
bool noMoreNeighs (civilADT civil);
/*Resetea el iterador al principio de la coleccion*/
void resetNeigh (civilADT civil); 
/*Mueve una unidad el iterador*/
void nextNeigh (civilADT civil);

/*
** Funciones que extraen informacion del actual 
** elemento de la coleccion. 
** Devuelven NULL o -1 si el TAD estaba vacio
*/
char * getNeighName (civilADT civil); 
long getNeighPop (civilADT civil);
long getNeighTrees (civilADT civil);
//Devuelve truncado a dos decimales
float getTreesPerHab (civilADT civil);

/*Devuelve 1 si el TAD estaba vacio o no fue incializado*/
bool isEmptyCivil (civilADT civil);

/*
** Funciones SORT para ordenar
*/

/*Ordena decreciente por arboles por habitantes*/
void sortDescTBHAscAlf(civilADT civil);

/*Ordena decreciente por arboles por barrio*/
void sortDescTreeAscAlf(civilADT civil);


#endif /*civilADT.h*/

