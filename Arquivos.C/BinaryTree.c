#include "BinaryTree.h"
#include "PriorityQueue.h"
#include "Byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>


//Estrutura da Árvore de Huffman
struct huffman_tree{
  byte item;
  long long int freq;
  huffman_tree *next;
  huffman_tree *left;
  huffman_tree *right;
};

//Cria um nó de arvore para guardar os itens
huffman_tree *new_node_tree(byte item, long long int freq){
  huffman_tree *new_node = (huffman_tree*)malloc(sizeof(huffman_tree));
  new_node->item = item;
  new_node->freq = freq;
  new_node->left = NULL;
  new_node->right = NULL;
  new_node->next = NULL;
  return new_node;
}

//Cria um nó pai recebendo filho da esquerda, direita e '*'
huffman_tree *tree_father(huffman_tree *node_tree1, huffman_tree *node_tree2){
  huffman_tree *father = (huffman_tree*)malloc(sizeof(huffman_tree));
  father->item = '*';
  father->freq = (node_tree1->freq)+(node_tree2->freq);
  father->left = node_tree1;
  father->right = node_tree2;
  father->next = NULL;
  return father;
}

//Verifica se o nó de arvore é NULL. (Localiza as folhas)
bool empty_tree(huffman_tree *hf){
  if(hf==NULL)
    return true;
return false;
}

//imprime arvore em pré-ordem
void print_pre_order(huffman_tree *hf){
  if (!empty_tree(hf)) {
    if(hf->right == NULL && hf->left == NULL) {
      if(hf->item == '*' || hf->item == '\\')
        printf("%c", hf->item);
      else
        printf("%c", hf->item);
    }
    else 
      printf("%c",hf->item);
    print_pre_order(hf->left);
    print_pre_order(hf->right);
  }
}

// Função booleana que retorna verdadeiro caso a nó em questão seja uma folha
bool is_leaf(huffman_tree *node_Tree){
  if (node_Tree->right == NULL && node_Tree->left == NULL){
    return true;
  }
return false;
}

//monta a arvore de huffman e retorna o nó raiz
huffman_tree *build_tree_huffman(priority_queue *pq, huffman_tree *node_father){
  huffman_tree *node_tree1, *node_tree2;
  while(size_list(pq)>1){
    node_tree1 = dequeue(pq);
    node_tree2 = dequeue(pq);
    huffman_tree *father = tree_father(node_tree1, node_tree2);
    insert_father(pq, father);
  }
  node_father = pq->head;
return node_father;
}

//Obtem o filho da esquerda
huffman_tree *get_left(huffman_tree *hf){
  return hf->left;
}
//Obtem o filho da direita
huffman_tree *get_right(huffman_tree *hf){
  return hf->right;
}
//Obtem o caracter guardado no nó
byte get_item(huffman_tree *hf){
  return hf->item;
}