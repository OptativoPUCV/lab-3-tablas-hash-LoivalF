#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {  
    long clave = hash(key, map->capacity);
    Pair * pair = createPair(key, value);
    while (map->buckets[clave] != NULL) {
        if (is_equal(map->buckets[clave]->key, key)) {
            map->buckets[clave]->value = value;
            return;
        }
        clave = (clave + 1) % map->capacity;
    }
    map->buckets[clave] = pair;
    map->size++;
    map->current = clave;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap * map = (HashMap *)malloc(sizeof(HashMap));
    map->buckets = (Pair **)malloc(sizeof(Pair *) * capacity);
    for (int i = 0; i < capacity; i++) {
        map->buckets[i] = NULL;
    }
    map->capacity = capacity;
    map->size = 0;
    map->current = -1;
    return map;
}

void eraseMap(HashMap * map,  char * key) {    
    long clave = hash(key, map->capacity);
    while (map->buckets[clave] != NULL) {
        if (is_equal(map->buckets[clave]->key, key)) {
            map->buckets[clave]->key = NULL;
            map->buckets[clave]->value = NULL;
            map->size--;
        }
        clave = (clave + 1) % map->capacity;
    }
}

Pair * searchMap(HashMap * map,  char * key) {   
    long clave = hash(key, map->capacity);
    while (map->buckets[clave] != NULL) {
        if (is_equal(map->buckets[clave]->key, key)) {
            map->current = clave;
            return map->buckets[clave];
        }
        clave = (clave + 1) % map->capacity;
    }
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
