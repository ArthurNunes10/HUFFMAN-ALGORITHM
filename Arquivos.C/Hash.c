#include "Hash.h"
#include "Byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>


//elementos da hash sao vetores que armazenama ate 8bits
struct element{
  byte binary[16];
};

//estrutura hash com no máximo 256 elementos
struct hashtable{
  element *table[256];
};

//cria uma tabela hash
hash* createTable() {
  hash *new_hash = (hash*) malloc(sizeof(hash));
    int i;
    for(i=0;i<256;i++){
        new_hash->table[i]=NULL;
    }
  return new_hash; 
}

//adiciona elementos na hash
void put_in_hash(hash *hashtable, byte key, byte binary[], long long int pos){
    int i;
    element *new_element = (element*)malloc(sizeof(element));
    for(i=0;i<pos;i++){
        new_element->binary[i]=binary[i];
    }
    hashtable->table[key]=new_element;
}

//imprime tabela hash
void print_hash(hash *hashtable){
  int i;
  for(i=0;i<256;i++){
      if(hashtable->table[i] != NULL){
        printf("%c: %s", i, hashtable->table[i]->binary);
        printf("\n"); 
      }
    }
}