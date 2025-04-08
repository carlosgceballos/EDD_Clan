Proyecto Clan: Árbol Binario de Sucesión

Descripción General.
Este proyecto tiene como objetivo digitalizar y automatizar la gestión de un clan tradicional del oriente, cuyo rol es mantener segura al shogun. La aplicación convierte los registros del clan, almacenados en un archivo CSV, en un árbol binario. Además, permite:

- Mostrar la línea de sucesión del liderazgo (solo entre miembros vivos).
- Automatizar el cambio de líder cuando el actual muere o alcanza los 70 años.
- Permitir la modificación de los datos de cada nodo (excepto el identificador y el id del padre).
- Gestionar una lista de contribuyentes por cada miembro, ordenada según el grado de contribución y la edad, utilizando estructuras de datos implementadas de forma manual.

Los requerimientos del proyecto se basan en la siguiente descripción:

Conversión y Construcción del Árbol Binario:

- Los datos se importan desde un archivo CSV con las columnas:
id, name, last_name, gender, age, id_father, is_dead, was_chief, is_chief

- Se crea el árbol binario de miembros del clan, partiendo del miembro fundador (identificado por tener valores "null" o vacíos en el campo id_father).

Gestión de la Sucesión del Liderazgo

- Se muestra la línea de sucesión actual, considerando únicamente a los miembros vivos.

- Se asigna automáticamente un nuevo líder basado en criterios establecidos (por ejemplo, el primer hijo varón vivo; si no se cumple, se buscan otras alternativas según el árbol familiar y las edades de los miembros).

Modificación de Datos

- Permite cambiar datos de cualquier miembro del clan (excepto el id y el id del padre).

Manejo de Contribuyentes

- Cada miembro (nodo) contiene una lista personalizada de contribuyentes, ordenada en función del “grado de contribución” (en un rango de 1 a 10) y la edad.

- Los datos de los contribuyentes se cargan desde un archivo CSV adicional.

Estructura del Proyecto:
El proyecto sigue la siguiente organización de carpetas:

/ProyectoClan 
  ├── bin 
     │ ├── ejecutable 
     │ ├── data.csv 
     │ └── contribuyentes.csv 
 └── src 
   ├── main.cpp
   ├── tree.h
   ├── clan.h 
   ├── node.h 
   ├── contribuyentes.h 
   ├── list.h 
   ├── nodelist.h 
   ├── cola.h 
   └── nodecola.h 

Esta organización respeta las condiciones del proyecto:

Carpeta bin: Contiene el ejecutable y los datos de entrada.

Carpeta src: Aloja únicamente el código fuente del proyecto. Los nombres (snake_case o camelCase) se han aplicado según las indicaciones del enunciado.

Para compilarlo escribiremos esto en la terminal: g++ -std=c++11 -I./src -o bin/miPrograma ./src/*.cpp
Luego dentro de la carpeta bin ejecutaremos con: ./miPrograma

EJECUCION:
El programa iniciará mostrando el líder actual y presentará un menú interactivo con las siguientes opciones:
1. Modificar nodo: Actualiza los datos de un miembro (excepto identificadores).
2. Imprimir nodo: Muestra la información de un nodo específico y su lista de contribuyentes.
3. Imprimir árbol: Recorre e imprime todo el árbol binario.
4. Mostrar sucesión: Despliega la línea de sucesión del liderazgo.
5. Imprimir líder: Muestra la información del líder actual.
0. Salir: Finaliza la ejecución del programa.

El programa se mantiene en ejecución hasta que el usuario decida salir, permitiendo múltiples operaciones sin reiniciar.
