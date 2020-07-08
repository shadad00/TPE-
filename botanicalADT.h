/*
**  botanicalADT.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  El ADT botanicalADT maneja y administra colecciones de datos biológicos de plantas. 
** Puede ser utilizado para organizar información de parques nacionales, parques o similar.
**
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef botanicalADT_h
#define botanicalADT_h

typedef struct botanicalCDT * botanicalADT;

/*Inicializa un nuevo TAD */
botanicalADT newBotanical(); 

/*Libera los recursos utilizados por el TAD*/
void freeBotanical(botanicalADT botanical);

/* 
** Agrega un elemento a la coleccion almacenada ordenado
** alfabeticamente de acuerdo al nombre de la especie.
** Si el arbol ya esta en la coleccion incrementa la 
** cantidad de ejemplares y actualiza el promedio.
** Si no esta en la lista, agrega el nodo. 
*/
void addPlant(botanicalADT botanical, char * treeName, double diameter);

/*
** Ordena la información almacenada en sentido 
** decreciente en diámetro y, luego, alfabeticamente.
*/
/*FALTA IMPLEMENTAR*/

void sortDescDiamAscAlf (botanicalADT botanical);

/*
** Funciones para poder iterar. 
*/
int noMorePlants (botanicalADT botanical);
void resetPlant (botanicalADT botanical); 
void nextPlant (botanicalADT);

/*
** Funciones que extraen informacion del actual 
** elemento de la coleccion
*/

char * getPlantName (botanicalADT botanical); 
unsigned long getQPlant (botanicalADT botanical);
double getDiameter (botanicalADT botanical);


void printBotanical (botanicalADT botanical);
void printSpecies(botanicalADT botanical); 
/*Completa la query3*/
void Query3(botanicalADT botanical,FILE * archivo);

#endif /* botanicaADT_h */