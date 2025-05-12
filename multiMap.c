#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN 1000

typedef struct Cancion {
  char id[50]; //id
  char artista[100]; //artist
  char album[100]; //album_name
  char nombre[100]; //track_name
  double tempo; //tempo
  char genero[50]; //track_genre
  struct Cancion *next;
} Cancion;

typedef struct MultiMap {
  Cancion **buckets;
  unsigned int capacity;
  int size;
} MultiMap;

MultiMap *multimap_create(){
  MultiMap *map = (MultiMap *) malloc(sizeof(MultiMap));
  if (map == NULL) return NULL;

  map->buckets = (Cancion **)calloc(MIN, sizeof(Cancion *));
  if (map->buckets == NULL) {
    free(map);
    return NULL;
  }

  map->capacity = MIN;
  map->size = 0;

  return map;
}

unsigned int hash(const char *str, unsigned int capacity) {
  unsigned int hash = 0;
  while (*str)
    hash = (hash * 31) + (unsigned char)(*str++);
  hash = (unsigned int)hash % capacity;
  return hash;
}


void multimap_insert(MultiMap *map, const char *key, const char *id, const char *artista, const char *album,
  const char *nombre, double tempo, const char *genero) {
if (map == NULL || key == NULL) return;

// Crea un nuevo nodo canción
Cancion *new = (Cancion *)malloc(sizeof(Cancion));
if (!new) return;

strcpy(new->id, id);
strcpy(new->artista, artista);
strcpy(new->album, album);
strcpy(new->nombre, nombre);
new->tempo = tempo;
strcpy(new->genero, genero);
new->next = NULL;

// Calcula índice usando hash en la clave
unsigned int index = hash(key, map->capacity);

// Insertar al inicio de la lista en el bucket correspondiente
new->next = map->buckets[index];
map->buckets[index] = new;

map->size++;
}
