#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

// Estrutura de um nó de lista
typedef struct list {
    int item;
    struct list *next;
} node_list;

//Estrutura da Binary Search Tree
typedef struct binary_tree{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

// Cria uma árvore vazia
binary_tree* createEmptyBinaryTree(){
    return NULL;
}

// Função auxiliar para insert_bt (Caso a árvore seja nula, create_tree é chamada)
// Recebe um valor, os filhos left e right e insere na raiz
binary_tree* create_tree(int item, binary_tree *left, binary_tree *right){
   
    binary_tree *new_bt = (binary_tree *) malloc(sizeof(binary_tree));
    new_bt->item = item;
    new_bt->left = left;
    new_bt->right = right;
return new_bt;
}

// Recebe a raiz da árvore, um valor e insere esse valor em seu devido lugar na árvore 
// na sub árvore da esquerda ou da direita, dependendo do valor
binary_tree* insert_bt(binary_tree *bt, int item){
    if(bt == NULL)
        bt = create_tree(item, NULL, NULL);
    
    else if(bt->item > item)
        bt->left = insert_bt(bt->left, item);
    
    else 
        bt->right = insert_bt(bt->right, item);
    
}

// Recebe a raiz da árvore e o item que vai ser procurado na árvore
// Retorna um inteiro referente ao quanto foi preciso "andar" até encontrar esse valor
int search_tree_value(binary_tree *bt, int item){   
    if(bt == NULL || bt->item == item)      
        return 1;

    else if(bt->item > item)
        return 1 + search_tree_value(bt->left, item);
     
     else
        return 1 + search_tree_value(bt->right, item);
}

// Cria uma lista vazia
node_list* createLinkedList(){
    return NULL;
}

// Recebe uma lista e insere um novo nó
node_list* insert_list(node_list *node, int item){
   
    node_list *new_node = (node_list *) malloc(sizeof(node_list));
    new_node->item = item;
    new_node->next = node;

return new_node;
}


// Recebe uma lista, um item e faz uma busca em toda a lista
// Retorna uma variável contadora que mostra quanto foi necessário percorrer até encontrar o valor
int search_node_list(node_list *node, int item){
    int count = 0;
    while(node){
        if(node->item == item)
            break;
        count++;
        node = node->next;
    }
    return count;
}

int main() {

    FILE *file;
    binary_tree *bt = createEmptyBinaryTree();
    node_list *node = createLinkedList();
    int i, valueN, valueT, random;

    file = fopen("count.txt","w+");
    
    for(i = 0; i < MAX; i++) {
        random = rand() % MAX + 1;
        bt = insert_bt(bt, random);
        node = insert_list(node, random);
        random = rand() % MAX + 1;
        valueN = search_node_list(node, random);
        valueT = search_tree_value(bt, random);
        fprintf(file, "%d %d %d\n", i, valueN, valueT);
    }

    fclose(file);

    return 0;
}   