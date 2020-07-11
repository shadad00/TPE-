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

#include <math.h>
#include <errno.h>

#ifndef botanicalADT_h
#define botanicalADT_h

typedef struct botanicalCDT * botanicalADT;

/*Inicializa un nuevo TAD */
botanicalADT newBotanical(); 

/*Libera los recursos utilizados por el TAD*/
void freeBotanical(botanicalADT botanical);

/* 
Almacena el nombre de la especie y el diametro promedio de la misma.
Retorna uno si puede almacenar de manera correcta.
*/
bool addPlant(botanicalADT botanical, char * treeName, double diameter);

/*
** Ordena la información almacenada en sentido 
** decreciente en diámetro y, luego, alfabeticamente.
*/
void sortDescDiamAscAlf (botanicalADT botanical);

/*
** Funciones para poder iterar. 
*/
/*Retorna uno si no hay mas arboles almacenados en el iterador*/
int noMorePlants (botanicalADT botanical);
/*Resetea el iterador al primer elemento de la coleccion*/
void resetPlant (botanicalADT botanical);
/*Actualiza el iterador al siguiente elemento*/
void nextPlant (botanicalADT);

/*
** Funciones que extraen informacion del actual 
** elemento de la coleccion
*/
/*Retorna un puntero al nombre del arbol*/
char * getPlantName (botanicalADT botanical);
/*Retorna la cantidad de ejemplares del arbol al que apunta el iterador*/
unsigned long getQPlant (botanicalADT botanical);
/*Retorna el diametro promedio de la especie a la que apunta el iterador*/
double getDiameter (botanicalADT botanical);

#endif /* botanicaADT_h */
