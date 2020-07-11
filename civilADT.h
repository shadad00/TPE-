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

/*Guarda la informacion de cada barrio con su
cantidad de habitantes.No admite barrios repetidos,ignorandolos. 
Devuelve true or false dependiendo de si pudo almacenar o no la informacion.
*/
bool addNeigh(civilADT civil,char * barrio, unsigned long habitantes);

/*
Incrementa en uno la cantidad de arboles del 
barrio
*/
void addTree(civilADT civil, char * barrio);

/*
** Funciones para poder iterar. 
*/

/*Deuelve true si no hay mas barrios en la coleccion*/
bool noMoreNeighs (civilADT civil);
/*Resetea el iterador al principio de la coleccion*/
void resetNeigh (civilADT civil); 
/*Mueve una unidad el iterador*/
void nextNeigh (civilADT civil);

/*
** Funciones que extraen informacion del actual 
** elemento de la coleccion
*/
char * getNeighName (civilADT civil); 
unsigned long getNeighPop (civilADT civil);
unsigned long getNeighTrees (civilADT civil);
double getTreesPerHab (civilADT civil);

/*
** Funciones SORT para ordenar
*/

/*Ordena decreciente por arboles por habitantes*/
void sortDescTBHAscAlf(civilADT civil);

/*Ordena decreciente por arboles por barrio*/
void sortDescTreeAscAlf(civilADT civil);


#endif /*civilADT.h*/

