#ifndef civilADT_h
#define civilADT_h

typedef struct civilCDT * civilADT;

/*
inicializa un nuevo ADT
*/
civilADT Newcivil();

/*
Libera los recursos usados por el TAD
*/
void freeCivil(civilADT civil);

/*
Agrega un elemento en la lista segun el orden ASCII de los barrios 
Se inicializa la cantidad de arboles en cero 
*/
void addNeigh(civilADT civil,char * barrio,int habitantes);

/*
Incrementa en uno la cantidad de arboles del nodo
barrio 
*/
void IncTrees(civilADT civil, char * barrio);


/*
Reordena los datos recolectados en dos listas: 
a)ordenada por cantidad de arboles por barrio de forma decreciente
b)ordenada por cantidad de arboles por habitante de forma decreciente 
En ambos casos en caso de empate define el orden ASCII
*/
void TreePerHab(civilADT civil);


/*para probarlo*/
void Imprimir(civilADT civil,FILE * archivo);
void ImpPrimera(civilADT civil, FILE * archivo);
void ImpSegunda(civilADT civil,FILE * archivo);

#endif