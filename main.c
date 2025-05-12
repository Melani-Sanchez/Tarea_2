#include "multiMap.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrarMenu() {
    printf("---------------------------------------------\n");
    printf("\nMENU OPCIONES - SELECCIONE UNA OPCIÓN:\n");
    printf("---------------------------------------------\n");
    printf("1. Cargar Canciones.\n");
    printf("2. Buscar por Género.\n");
    printf("3. Buscar por Artista.\n");
    printf("4. Buscar por Tempo.\n");
    printf("5. Buscar por ID");
    printf("0. Salir.\n");
}

void mostrarTipoTempo() {
    printf("------------------------------\n");
    printf("\nSELECCIONE UNA VELOCIDAD:\n");
    printf("------------------------------\n");
    printf("1. Lentas.\n");
    printf("2. Moderadas.\n");
    printf("3. Rápidas\n");
    printf("0. Volver al menú\n");
}

void leerCanciones(const char *archivo ,Cancion **listaCanciones, Cancion **lentas, Cancion **moderadas, 
    Cancion **rapidas, MultiMap *porArtista, MultiMap *porGenero, MultiMap *porId) {
    
    FILE *fp = fopen(archivo, "r");
    if (!fp) {
        perror("No se pudo abrir el archivo");
        return;
    }

    char linea[1024];
    fgets(linea, sizeof(linea), fp); // Saltar cabecera

    while (fgets(linea, sizeof(linea), fp)) {
        char *id = strtok(linea, ",");
        strtok(NULL, ","); //Saltar columna
        char *artista = strtok(NULL, ",");
        char *album = strtok(NULL, ",");
        char *nombre = strtok(NULL, ",");
        for (int i = 0; i < 13; i++) strtok(NULL, ","); // Saltar columnas hasta tempo
        char *tempoStr = strtok(NULL, ",");
        strtok(NULL, ","); // Saltar columna
        char *genero = strtok(NULL, ",\n");

        if (!id || !artista || !album || !nombre || !tempoStr || !genero) continue;

        double tempo = atof(tempoStr);

        // Crear canción
        Cancion *new = (Cancion *)malloc(sizeof(Cancion));
        strcpy(new->id, id);
        strcpy(new->artista, artista);
        strcpy(new->album, album);
        strcpy(new->nombre, nombre);
        new->tempo = tempo;
        strcpy(new->genero, genero);
        new->next = NULL;

        // Insertar en lista
        new->next = *listaCanciones;
        *listaCanciones = new;

        Cancion *copia = (Cancion *) malloc(sizeof(Cancion));
        *copia = *new;
        copia->next = NULL;


        if (tempo < 80.00) { // Canciones lentas
            copia->next = *lentas;
            *lentas = copia;
        } 
        else if (tempo > 80.00 && tempo < 120.00) { // Canciones moderadas
            copia->next = *moderadas;
            *moderadas = copia;
        }
        else { //Canciones rápidas
            copia->next = *rapidas;
            *rapidas = copia;
        } 

        // Insertar en MultiMaps
        multimap_insert(porId, id, id, artista, album, nombre, tempo, genero);
        multimap_insert(porArtista, artista, id, artista, album, nombre, tempo, genero);
        multimap_insert(porGenero, genero, id, artista, album, nombre, tempo, genero);
    }
    printf("Proceso Completado!\n");
    fclose(fp);
}

void buscarGenero(MultiMap *porGenero) {
    if (porGenero == NULL) return;
    
    char genero[100];
    printf("Ingrese el género a buscar: ");
    scanf(" %[^\n]", genero); // Leer con espacios
    
    unsigned int index = hash(genero, porGenero->capacity);
    Cancion *aux = porGenero->buckets[index];
    
    int encontrado = 0;
    while (aux != NULL) {
        if (strcmp(aux->genero, genero) == 0) {
            encontrado = 1;
            printf("ID: %s\n", aux->id);
            printf("Artista: %s\n", aux->artista);
            printf("Álbum: %s\n", aux->album);
            printf("Nombre: %s\n", aux->nombre);
            printf("Tempo: %.2f\n", aux->tempo);
            printf("Género: %s\n", aux->genero);
            printf("--------------------------\n");
        }
        aux = aux->next;
    }
    
    if (!encontrado) {
        printf("No se encontraron canciones del género '%s'.\n", genero);
    }
}

void buscarArtista(MultiMap *porArtista) {
    if (porArtista == NULL) return;

    char artista[100];
    printf("Ingrese el nombre del artista: ");
    scanf(" %[^\n]", artista); // Leer con espacios

    unsigned int index = hash(artista, porArtista->capacity);
    Cancion *actual = porArtista->buckets[index];

    int encontrado = 0;
    while (actual != NULL) {
        if (strcmp(actual->artista, artista) == 0) {
            encontrado = 1;
            printf("ID: %s\n", actual->id);
            printf("Artista: %s\n", actual->artista);
            printf("Álbum: %s\n", actual->album);
            printf("Nombre: %s\n", actual->nombre);
            printf("Tempo: %.2f\n", actual->tempo);
            printf("Género: %s\n", actual->genero);
            printf("--------------------------\n");
        }
        actual = actual->next;
    }

    if (!encontrado) {
        printf("No se encontraron canciones del artista '%s'.\n", artista);
    }
}

void mostrarLista(Cancion *lista) {
    Cancion *aux = lista;
    while (aux != NULL) {
        printf("ID: %s\n", aux->id);
        printf("Artista: %s\n", aux->artista);
        printf("Álbum: %s\n", aux->album);
        printf("Nombre: %s\n", aux->nombre);
        printf("Tempo: %.2f\n", aux->tempo);
        printf("Género: %s\n", aux->genero);
        printf("--------------------------\n");
        aux = aux->next;
    }
}

void buscarTempo(Cancion **lentas, Cancion **moderadas, Cancion **rapidas) {
    if (lentas == NULL || moderadas == NULL || rapidas == NULL) {
        printf("No se han ingresado canciones");
        return;
    }

    while (1) {
        mostrarTipoTempo();
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "1") == 0) {
            printf("\nCANCIONES LENTAS:\n");
            mostrarLista(*lentas);
        }
        else if (strcmp(op, "2") == 0) {
            printf("\nCANCIONES MODERADAS:\n");
            mostrarLista(*moderadas);
        }
        else if (strcmp(op, "3") == 0) {
            printf("\nCANCIONES RÁPIDAS:\n");
            mostrarLista(*rapidas);
        }
        else if (strcmp(op, "0") == 0) {
            printf("Volviendo al menú principal...\n");
            break;
        }
        else printf("Opción inválida, vuelva a intentarlo.\n");
    }
}

void buscarId(MultiMap *porId) {
    if (porId == NULL) return;

    char id[100];
    printf("Ingrese el ID: ");
    scanf(" %[^\n]", id); // Leer con espacios

    unsigned int index = hash(id, porId->capacity);
    Cancion *actual = porId->buckets[index];

    int encontrado = 0;
    while (actual != NULL) {
        if (strcmp(actual->id, id) == 0) {
            encontrado = 1;
            printf("ID: %s\n", actual->id);
            printf("Artista: %s\n", actual->artista);
            printf("Álbum: %s\n", actual->album);
            printf("Nombre: %s\n", actual->nombre);
            printf("Tempo: %.2f\n", actual->tempo);
            printf("Género: %s\n", actual->genero);
            printf("--------------------------\n");
        }
        actual = actual->next;
    }

    if (!encontrado) {
        printf("No se encontró el ID '%s'.\n", id);
    }
}

void ejecutarPrograma() {
    Cancion *listaCanciones = NULL;
    Cancion *lentas = NULL;
    Cancion *moderadas = NULL;
    Cancion *rapidas = NULL;
    MultiMap *porArtista = multimap_create();
    MultiMap *porGenero = multimap_create();
    MultiMap *porId = multimap_create();

    while (1) {
        mostrarMenu();
        char op[10];
        scanf("%s", op);

        if (strcmp(op, "0") == 0 || strcmp(op, "salir") == 0) {
            printf("Saliendo del programa...\n");
            break;
        }
        int contador = 0;
        if(strcmp(op,"1") == 0) {
            if (contador == 0) {
                leerCanciones("song_dataset_.csv", &listaCanciones, &lentas, 
            &moderadas, &rapidas, porArtista, porGenero, porId);
                contador = 1;
            }
            else printf("Las canciones ya fueron cargadas.\n");
        }
        else if (strcmp(op, "2") == 0) buscarGenero(porGenero);
        else if (strcmp(op, "3") == 0) buscarArtista(porArtista);
        else if (strcmp(op, "4") == 0) buscarTempo(&lentas, &moderadas, &rapidas);
        else if (strcmp(op, "5") == 0) buscarId(porId);
        else printf("Respuesta inválida, inténtelo de nuevo.\n");
    }
    free(listaCanciones);
    free(lentas);
    free(moderadas);    
    free(rapidas);
    free(porArtista);
    free(porGenero);
    free(porId);
}

int main() {
    ejecutarPrograma();

    return 0;
}