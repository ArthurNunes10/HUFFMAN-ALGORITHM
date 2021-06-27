#include "PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>


struct priority_queue {
    huffman_tree *head;
    long long int size;
};


priority_queue *construct (){
  priority_queue *new_queue = (priority_queue*) malloc(sizeof(priority_queue));
  new_queue->head = NULL;
  new_queue->size = 0;
  return new_queue;
}

int size_list(priority_queue *pq){
  return pq->size;
}

bool empty (priority_queue *pq){
  if (pq->size == 0) 
    return true;
  return false;
}

void enqueue(priority_queue *pq, byte item, long long int freq){
  huffman_tree *new_node = new_node_tree(item, freq);
  if ((empty(pq)) || (freq <= pq->head->freq)){
    new_node->next = pq->head;
    pq->head = new_node;
  }
  else{
    huffman_tree *node_aux = pq->head;
    while((node_aux->next != NULL) && (node_aux->next->freq < freq)){
      node_aux = node_aux->next;
    }
    new_node->next = node_aux->next;
    node_aux->next = new_node;
  }
  pq->size++;
}

void insert_father(priority_queue *pq, huffman_tree *father){
  if ((empty(pq)) || (father->freq <= pq->head->freq)){
      father->next = pq->head;
      pq->head = father;
    }
    else {
      huffman_tree *node_aux = pq->head;
      while((node_aux->next != NULL) && (node_aux->next->freq < father->freq)){
        node_aux = node_aux->next;
      }
      father->next = node_aux->next;
      node_aux->next = father;
    }
    pq->size++;
}

huffman_tree *dequeue(priority_queue *pq){
  if (!empty(pq)) {
    huffman_tree *node_tree = pq->head;
    pq->head = pq->head->next;
    pq->size--;
    return node_tree;
  } 
}

void Print_list(priority_queue *pq){
  huffman_tree *current = pq->head;
  while(current != NULL){
    printf("Caracter: %c Frequencia: %lli\n",  current->item, current->freq);
    current = current->next;
  }
  printf("\n");
}