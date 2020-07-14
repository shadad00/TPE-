# procesarArbolesADT

El proyecto permite procesar la informacion de los arboles censados en distintas ciudades.
Su objetivo principal es la creacion de ciertas consultas especificas. 

## Instalacion

1) Invocar al comando `make build`. Esto generará dos ejecutables procesarArbolesBUE y procesarArbolesVAN.
2) Seleccione e invoque el ejecutable deseado, seguido de los archivos .csv a procesar en el siguiente orden: 
	i)  Informacion sobre los arboles
	ii) Informacion sobre los barrios

## Uso

Ejemplo de uso para archivos nombrados arbolesBUE.csv y barriosBUE.csv. 
Los archivos deben ser llamados en ese orden (primero el de arboles y despues el de barrios) 

```bash
make build 
./procesarArbolesBUE arbolesBUE.csv barriosBUE.csv
```

## Sobre las consultas producidas

El programa crea tres consultas en formato csv en el mismo directorio de ejecucion del programa: 
	i) Total de arboles por barrios. Ordenado descendente por cantidad de arboles y luego alfabeticamente por nombre de barrio. 
	ii) Total de arboles por habitante. Ordenado descendente por cantidad de arboles por habitante y luego alfabeticamente por nombre de barrio. 
	iii) Diametro promedio por especie de arbol. Ordenado descendente por diametro y luego alfabeticamente por nombre de especie. 

## Posibles errores

El programa aborta en caso de errores esenciales. 

Los codigos de error y sus referencias son: 

>1) No ha compilado el codigo con VAN o BUE 
>2) Cantidad de argumentos incorrecta
>3) No se pudo abrir el archivo
>4) No hay memoria suficiente	

El programa no acepta barrios repetidos en el archivo de barrios. En caso de haberlos, se los ignora. 
El programa no contabiliza arboles de un barrio que no esta en el archivo de barrios, pero si toma su diametro y apariciones. 
El usuario es notificado de toda omision. 
