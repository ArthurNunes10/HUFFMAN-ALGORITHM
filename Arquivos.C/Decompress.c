#include "Decompress.h"
#include "BinaryTree.h"
#include "Help.h"
#include "Byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// Recebe o arquivo de entrada (compactado) e 2 vetores: um para armazenar o tamanho lixo e outro para armazenar o tamanho da árvore
void get_tree_trash_size(FILE *iFile, int *trash, int *size_tree){

  byte Byte1, Byte2, flag;
  int cont=0, bits=7;
  Byte1 = (byte)fgetc(iFile);
  Byte2 = (byte)fgetc(iFile);
  flag = Byte1;

  while(cont < 16){
    if(bits < 0) {
      bits = 7;
      flag = Byte2;
    }
    
    if(cont < 3) {
      if(is_bit_set(flag, bits)){
        trash[cont] = 1;
      } 
      else 
        trash[cont] = 0;
    } 
        
    else {
      if(is_bit_set(flag, bits)){
        size_tree[cont-3] = 1;
      } 
      else 
        size_tree[cont-3] = 0;
    }
    bits--;
    cont++;
  }
}

// Recebe o arquivo, um vetor vazio que vai ser preenchido com os characteres da árvore em pré ordem e o tamanho da árvore
void get_huff_tree(FILE *iFile, byte *tree, int tree_size) {
  int i=0, oByte;
  while(i<tree_size) {
    oByte = fgetc(iFile);
    tree[i] = (char)oByte;
    i++;
  }
}

//Função utilizada para criar os nós durante a Rebuild_Tree
huffman_tree *create_node2(byte character, long long int freq, huffman_tree *left, huffman_tree *right) {
	byte *symbol_aux = malloc(sizeof(byte));
	*symbol_aux = character;

	huffman_tree *new_tree = malloc(sizeof(huffman_tree));
	new_tree->item = *(byte*)symbol_aux;
	new_tree->freq = freq;
	new_tree->left = left;
	new_tree->right = right;

	return new_tree;
}

//reconstroi a arvore
huffman_tree *rebuildTree(huffman_tree *hf, byte *tree, int size, int *pos) {

  if(*pos >= size)
    return NULL;

  if(tree[*pos] == '*') {
    hf = create_node2(tree[*pos], 0, NULL, NULL);
    ++(*pos);
    hf->left = rebuildTree(hf->left, tree, size, pos);
    ++(*pos);
    hf->right = rebuildTree(hf->right, tree, size, pos);
  }
  else {
    if(tree[*pos] == '\\')
      ++(*pos);
    hf = create_node2(tree[*pos], 0, NULL, NULL);
  }
return hf;
}


void write_character_on_file(huffman_tree *rebuild_tree, FILE *iFile, FILE *oFile, int trash, int tree_size) {
  rewind(iFile);
  fseek(iFile, 0, SEEK_END);
  int qtde_bytes = ftell(iFile);
  int content = qtde_bytes - (tree_size + 2);
  fseek(iFile, (tree_size+2), SEEK_SET);

  huffman_tree *hf_aux = rebuild_tree;

  int helper, bits=7, i=0;

  while(i <= content) {
    helper = fgetc(iFile);
    while (bits >= 0) {
      if(hf_aux->left == NULL && hf_aux->right == NULL) {
        fprintf(oFile, "%c", hf_aux->item);
        hf_aux = rebuild_tree;
      }
      if(is_bit_set((byte)helper, bits)) 
        hf_aux = hf_aux->right;
      else
        hf_aux = hf_aux->left;
      bits--;
    }
    bits = 7;
    i++;
  }

  helper = fgetc(iFile);
  bits = 7;
  while(bits >= trash) {
    if(hf_aux->left == NULL && hf_aux->right == NULL) {
      fprintf(oFile, "%c", hf_aux->item);
      hf_aux = rebuild_tree;
    }
    if(is_bit_set((byte)helper, bits)) 
        hf_aux = hf_aux->right;
    else 
      hf_aux = hf_aux->left;
    bits--;
  }
}

// Recebe os arquivos de entrada e saída e chama funções auxiliares para realizar a descompressão
void decompress(FILE *iFile, FILE *oFile) {

  int tree_size[13], trash_size[3], trash, size_of_tree, pos=0;	

  get_tree_trash_size(iFile, trash_size, tree_size);
  size_of_tree = bin_to_dec(tree_size, 13);
  trash = bin_to_dec(trash_size, 3);

  char tree[size_of_tree];

  get_huff_tree(iFile, tree, size_of_tree);
  huffman_tree *huff_tree = NULL;
  huff_tree = rebuildTree(huff_tree, tree, size_of_tree, &pos);
  write_character_on_file(huff_tree, iFile, oFile, trash, size_of_tree);
}