#include "checkError.h"
#define ARGS 2

bool checkMem (void) {
  if (errno == ENOMEM) {
    fprintf(stderr, "No hay mas memoria disponible.\n"); 
    return false; 
  }
  return true; 
}

bool checkFile (FILE * pFile, char * filename) {
  if (pFile == NULL) {
    fprintf(stderr, "No se pudo abrir el archivo %s.\n", filename);
    return false;  
   }
   return true; 
}

bool checkRep (char * name1, char * name2) {
  if (strcmp(name1, name2) == 0) {
    fprintf(stderr, "Se detecto e ignoro 1 registro repetido en el csv de barrios.\n");
    return false; 
  }
  return true; 
}

bool checkArgs (size_t args) {
  if (args != ARGS+1) {
    fprintf(stderr, "Cantidad de parametros incorrecta.\n"); 
    return false; 
  }
  return true; 
}

bool checkMode (void) {
  #if !defined BUE && !defined VAN
    fprintf(stderr, "Modo no definido o codigo AAA no valido.\n");
    return false; 
  #endif 
  return true; 
}


