# Tarea\_2 | Sistema de Gestión de Canciones

Este programa en lenguaje C permite gestionar una colección de canciones usando estructuras de datos como listas enlazadas y tablas hash (MultiMap). A partir de un archivo `.csv` con datos musicales, el sistema permite **buscar canciones por ID, artista, género o tempo**, clasificarlas según su velocidad y acceder rápidamente a ellas gracias a una estructura de hash.

Es una herramienta ideal para organizar y consultar grandes volúmenes de información musical, con aplicaciones potenciales en sistemas de recomendación, bases de datos musicales, reproductores personalizados, entre otros.

---

## Cómo compilar y ejecutar

Este sistema puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con una extensión para C/C++.

### Requisitos previos:

* [Visual Studio Code](https://code.visualstudio.com/)
* Extensión **C/C++** (Microsoft)
* Compilador de C, como **gcc** (en Windows puedes usar [MinGW](https://www.mingw-w64.org/) o [WSL](https://learn.microsoft.com/en-us/windows/wsl/))

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime** el archivo `.zip` del proyecto en una carpeta.

2. **Abre el proyecto en Visual Studio Code**:

   * Selecciona `Archivo > Abrir carpeta...` y elige la carpeta del proyecto.

3. **Compila el código**:
   Asegúrate de tener estos archivos en la misma carpeta:

   * `main.c`
   * `multiMap.c`
   * `multiMap.h`
   * `canciones.csv` (archivo con los datos de canciones)
   * Abre la terminal integrada (`Terminal > Nueva terminal`).
   En la terminal integrada de VS Code, compila con:

   ```bash
   gcc main.c multiMap.c -o gestor_canciones
   ```

4. **Ejecuta el programa**:

   * En Linux/macOS:

     ```bash
     ./gestor_canciones
     ```

   * En Windows:

     ```bash
     gestor_canciones.exe
     ```

---

## 📜 Menú de Opciones

```txt
1. Cargar canciones desde archivo CSV.
2. Buscar canciones por género.
3. Buscar canciones por artista.
4. Buscar canciones por tempo.
5. Buscar canción por ID.
0. Salir.
```

---

## 🛠️ Funcionalidades principales

* **Carga eficiente** desde CSV en estructuras organizadas por:

  * ID (`porId`)
  * Artista (`porArtista`)
  * Género (`porGenero`)
  * Tempo (`lentas`, `moderadas`, `rapidas`)

* **Búsqueda por clave** con tiempo constante promedio gracias al uso de `MultiMap` y hashing.

* **Clasificación por tempo**: lenta (<85 BPM), moderada (85-120 BPM), rápida (>120 BPM).

* **Liberación de memoria dinámica** antes de salir del programa.

---

## 🔍 Ejemplo de uso

Ejemplo de uso
Paso 1: Cargar canciones
Opción seleccionada: 1. Cargar Canciones

Se carga el archivo song_dataset_.csv.

Las canciones se insertan en listas enlazadas clasificadas por tempo (lentas, moderadas y rápidas), y en tres MultiMap por artista, género e ID.

Se imprime:
Proceso Completado!

Paso 2: Buscar canciones por género
Opción seleccionada: 2. Buscar por Género

Ingrese el género: Pop

El sistema imprime una lista de todas las canciones del género Pop, mostrando:

ID: 1234
Artista: John Doe
Álbum: Hit Parade
Nombre: Summer Vibes
Tempo: 100.50
Género: Pop
--------------------------

Si no se encuentran canciones:
No se encontraron canciones del género 'Pop'.

Paso 3: Buscar canciones por artista
Opción seleccionada: 3. Buscar por Artista

Ingrese el nombre del artista: Adele

Se imprimen todas las canciones correspondientes a ese artista con sus datos.

Si no se encuentra ninguna canción:
No se encontraron canciones del artista 'Adele'.

Paso 4: Buscar por tempo
Opción seleccionada: 4. Buscar por Tempo

Se despliega un submenú:
SELECCIONE UNA VELOCIDAD:
1. Lentas.
2. Moderadas.
3. Rápidas
0. Volver al menú

Seleccionando opción 2 (Moderadas):
Se imprimen todas las canciones con tempo entre 80.00 y 120.00.
Si no hay resultados: no imprime nada.

Seleccionando opción 0:
Volviendo al menú principal...

Paso 5: Buscar canción por ID
Opción seleccionada: 5. Buscar por ID

Ingrese el ID: TRK-9901

Se imprime la información completa de la canción si existe.

Si no se encuentra:
No se encontró el ID 'TRK-9901'.

Paso 6: Salida del programa
Opción seleccionada: 0. Salir

Se imprime:
Saliendo del programa...

