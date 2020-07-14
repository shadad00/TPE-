/*
**  botanicalADT.h
**  Creado por Hadad, Delasoie & Beade el 06/07/20
**  Copyright (c) 2020 Hadad-Delasoie-Beade. 
**  Todos los derechos reservados.
**
**  El TAD botanicalADT.h permite almacenar 
**  una coleccion de datos biologicos y botanicos
**  de un conjunto de plantas.
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <math.h>


#ifndef botanicalADT_h
#define botanicalADT_h

typedef struct botanicalCDT * botanicalADT;

/*Inicializa un nuevo TAD */
botanicalADT newBotanical(int * flag); 

/*Libera los recursos utilizados por el TAD*/
void freeBotanical(botanicalADT botanical);

/* 
** Agrega un elemento a la coleccion almacenada ordenado
** alfabeticamente de acuerdo al nombre de la especie.
** Si el arbol ya esta en la coleccion incrementa la 
** cantidad de ejemplares y actualiza el promedio.
** Si no esta en la lista, agrega el nodo. 
*/
bool addPlant(botanicalADT botanical, char * treeName, float diameter);

/*
** Ordena la información almacenada en sentido 
** decreciente en diámetro y, luego, alfabeticamente.
*/
void sortDescDiamAscAlf (botanicalADT botanical);

/*
** Funciones para poder iterar. 
*/
int noMorePlants (botanicalADT botanical);
void resetPlant (botanicalADT botanical); 
void nextPlant (botanicalADT);

/*
** Devuelve 1 si el TAD estaba vacio o no fue
** inicializado
*/
bool isEmptyBotanical (botanicalADT botanical);

/*
** Funciones que extraen informacion del actual 
** elemento de la coleccion
*/

char * getPlantName (botanicalADT botanical); 
unsigned long getQPlant (botanicalADT botanical);
//Devuelve truncado a dos decimales 
float getDiameter (botanicalADT botanical);

#endif /* botanicaADT_h */