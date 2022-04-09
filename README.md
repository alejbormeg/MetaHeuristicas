# Prácticas de la asignatura Metaheurísticas 

El objetivo es resolver el problema de Asignación de pesos en características (APC), en el contexto de Aprendizaje supervisado utilizando como clasificador 1-NN con la distancia euclidea ponderada. 

## Estructura de Ficheros

El proyecto se compone de 6 carpetas: 

- **include**: contiene todos los ficheros de cabecera necesarios, actualmente *utilidades.h* con funciones para hacer Clasificación 1-NN, Leave One Out o preparar 5-fold Cross validation. *RELIEF.h* con todas las funciones necesarias para el método gredy RELIEF. *BL.h* con todas las funciones necesarias para el método de Búsqueda Local.

- **lib**: carpeta para librerías, actualmente vacía.
- **instancias_APC**: Carpeta que contiene las bases de datos que utilizaremos: Spectf-heart, Parkinsons e Ionosphere.
- **memoria**: Carpeta dónde se encuentra la memoria de la práctica así como las imágenes que se usarán en esta.
- **output**: Carpeta dónde se encuentra el ejecutable. 
- **src**: Carpeta dónde se encuentran los archivos fuente que implementan las cabeceras así como el programa principal *main.cpp*

Finalmente se tiene un *Makefile* con las siguientes reglas para su uso: 

- make: construye el proyecto
- make clean: limpia archivos .o
- make run_parkinsons: ejecuta el programa pasando como parámetro la base de datos parkinsons
- make run_ionosphere: ejecuta el programa pasando como parámetro la base de datos parkinsons
- make run_heart: ejecuta el programa pasando como parámetro la base de datos spectf-heart