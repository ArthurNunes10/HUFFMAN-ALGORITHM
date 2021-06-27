#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#define max_size 256

//VARIÁVEIS COM LONG LONG INT
typedef unsigned char byte;
typedef struct huffman_tree huffman_tree;
typedef struct priority_queue priority_queue;
typedef struct element element;
typedef struct hashtable hash;

//Estrutura da Árvore de Huffman
struct huffman_tree{
  byte item;
  long long int freq;
  huffman_tree *next;
  huffman_tree *left;
  huffman_tree *right;
};

//Estrutura da Fila de Prioridade
struct priority_queue {
    huffman_tree *head;
    long long int size;
};

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
//Cria uma fila dinamicamente e retorna seu endereço de memoria
priority_queue *construct (){
  priority_queue *new_queue = (priority_queue*) malloc(sizeof(priority_queue));
  new_queue->head = NULL;
  new_queue->size = 0;
  return new_queue;
}

//retorna o tamanho atual da lista de prioridade
int size_list(priority_queue *pq){
  return pq->size;
}

//Verifica se a lista está vazia
bool empty (priority_queue *pq){
  if (pq->size == 0) 
    return true;
  return false;
}

//Verifica se o nó de arvore é NULL. (Localiza as folhas)
bool empty_tree(huffman_tree *hf){
  if(hf==NULL)
    return true;
return false;
}

//Cria nó de arvore e adiciona na fila de acordo com sua frequencia
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

//Insere o nó pai na fila de prioridade (é igual a enqueue, porém com algumas modificações)
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

//tira ó primeiro no da fila, e retorna ele;
huffman_tree *dequeue(priority_queue *pq){
  if (!empty(pq)) {
    huffman_tree *node_tree = pq->head;
    pq->head = pq->head->next;
    pq->size--;
    return node_tree;
  } 
}

//imprime a lista de prioridades
void Print_list(priority_queue *pq){
  huffman_tree *current = pq->head;
  while(current != NULL){
    printf("Caracter: %c Frequencia: %lli\n",  current->item, current->freq);
    current = current->next;
  }
  printf("\n");
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
huffman_tree *build_tree_huffman(priority_queue *pq, huffman_tree*node_father){
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


// Recebe um char e sua posição no byte e acende o bit referente a essa posição
byte setBit(byte c, int i){
    byte mask = 1 << i;
    return  mask|c;
}

// Recebe um character do tipo byte e uma posição
// Verifica se o bit da posição passada está aceso ou não
int is_bit_set(byte c, int i){
    byte mask = 1 << i;
return mask & c;
}

// Recebe um vetor de inteiros contendo uma sequência de binários e o tamanho do vetor
// Retorna o valor dessa sequência binária como um decimal
int bin_to_dec(int *aux, int size){
    int value = 0, i;
    for(i = 0; i < size; i++){
        if(aux[i]){
            if((size-1) - i == 0)
                value += 1;
            else
                value += pow(2,(size-1) - i);
        }
    }

return value;
}

//Escreve cabeçalho
void create_header(FILE *iFile, FILE *oFile, hash *hashtable, huffman_tree *node_tree) {

  short int trash_size, tree_size;
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


// Descompatação

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


int main(){

    printf("Deseja (C)omprimir ou (D)escomprimir ?\n");

    char c, eFile[150], sFile[150];
    scanf("%c", &c);
    getchar();

    printf("Digite o nome do arquivo de entrada: \n");
    scanf("%[^\n]", eFile);
    getchar();
    printf("Digite o nome do arquivo de saida: \n");
    scanf("%[^\n]", sFile);

    FILE *iFile;
    iFile = fopen(eFile, "rb");

    if(iFile == NULL){
        printf("O arquivo nao pode ser aberto\n");
        exit(1);
    }

    if(c == 'C') {
        FILE *oFile = fopen(sFile, "wb");
        compress(iFile, oFile);
    } 
    
    else if(c == 'D') {
        FILE *oFile = fopen(sFile, "wb");
        decompress(iFile, oFile);
    } 
    
    else {
        printf("Comando invalido! O programa sera encerrado\n");
        exit(1);
    }

return 0;
}