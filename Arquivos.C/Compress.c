#include "Compress.h"
#include "BinaryTree.h"
#include "Hash.h"
#include "PriorityQueue.h"
#include "Byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>


//Faz o mapeamento dos caracteres com 0s e 1s e armazena na hash
void traveling_the_Tree(huffman_tree *node_tree, byte binary[], long long int current, hash *table) {
  if(get_left(node_tree)){
    binary[current]='0';
    traveling_the_Tree(node_tree->left, binary, current+1, table);
  }

  if(get_right(node_tree)){
    binary[current]='1';
    traveling_the_Tree(node_tree->right, binary, current+1, table);
  }

  if(is_leaf(node_tree)){
    put_in_hash(table, get_item(node_tree), binary, current);
  }
}  


// Escreve a arvore em pre ordem no arquivo.huff
void write_tree(huffman_tree *hf, FILE *oFile){
  if (!empty_tree(hf)) {
    if(hf->left == NULL && hf->right == NULL) {
      if(hf->item == '*' || hf->item == '\\')
        fprintf(oFile, "\\%c", hf->item);
      else
        fprintf(oFile, "%c", hf->item);
    }
    else
      fprintf(oFile,"%c",hf->item);
    write_tree(hf->left, oFile);
    write_tree(hf->right, oFile);
  }
}

// Retorna o tamanho da árvore levando em consideração os caracteres '*' e '\'
int size_of_tree(huffman_tree *ht) {
  if(ht->left == NULL && ht->right == NULL) {
    if(ht->item == '*' || ht->item == '\\')
      return 2;
    else
      return 1;
 	}
     
  else if (ht != NULL)
    return 1 + size_of_tree(ht->left) + size_of_tree(ht->right);
return 0;
 }

//retorna a quantidade de bits do lixo
long long int sizeTrash(FILE *iFile, hash *hashtable){
  byte character;
  long long int count_bit=0;
    
  while((character = fgetc(iFile)) != (byte)EOF) {
    count_bit+=strlen(hashtable->table[character]->binary);
  }
return (8-count_bit % 8);
}

//Escreve cabeçalho
void create_header(FILE *iFile, FILE *oFile, hash *hashtable, huffman_tree *node_tree) {

  long long int trash_size, tree_size;
  int i;
  trash_size = sizeTrash(iFile, hashtable);
  tree_size = size_of_tree(node_tree);
    
  byte oByte, iByte;
  oByte = trash_size << 5 | tree_size >> 8;
  fprintf(oFile, "%c", oByte);
  oByte = tree_size;
  fprintf(oFile, "%c", oByte);
   
  write_tree(node_tree, oFile); //imprime arvore
    
  byte oByte2;
  int bits = 7;
  oByte2 = iByte = 0;

  rewind(iFile);

  while((fscanf(iFile ,"%c", &iByte) != EOF)) {
    for(i=0; i<strlen(hashtable->table[iByte]->binary); i++) {
      if(hashtable->table[iByte]->binary[i] == '1') {
        oByte2 |= 1 << bits;
      }
      bits--;
      if(bits<0) {
        fprintf(oFile, "%c", oByte2);
        oByte2 = 0;
        bits = 7;
      }
    }
  }
  
  if(trash_size)
    fprintf(oFile, "%c", oByte2);
}


void compress(FILE *iFile, FILE *oFile) {

  priority_queue *pq = construct();
  huffman_tree *root = NULL;
  byte character, binary_vector[100];;
  long long int i, pos[max_size], posicao = 0;

  hash *table = createTable();
    
  //atribui 0 para todas as posicoes do vetor
  memset(pos, 0, sizeof(pos)); 
        
  while((fscanf(iFile ,"%c", &character) != EOF)) {
    pos[(long long int) character]++; //na posicao (int)character incrementa a frequencia
  }

  for(i=max_size-1; i>=0; i--) {
    //caso o item do vetor seja diferente de 0, o caracter da posicao correspondente sera add na lista
    if(pos[i] != 0)
      enqueue(pq, (byte) i, pos[i]); //recebe lista, caracter, frequencia
  }
        
  root = build_tree_huffman(pq, root); //monta a arvore e retorna o nó pai
  traveling_the_Tree(root, binary_vector, posicao, table); //cria hash
  create_header(iFile, oFile, table, root);
  fclose(iFile); 
  fclose(oFile);
}