// Definição de um estrutura padrão de uma Árvore Binária que possui um item do tipo unsigned char e a frequência desse item
typedef struct huffman_tree huffman_tree;


/* Função que cria um nó de árvore para guardar os itens e suas frequências
*  @param: um caractere do tipo byte e a frequência desse caractere num arquivo.
*/
huffman_tree *new_node_tree(byte item, long long int freq);

/* Função auxiliar para a 'BuildHuffmanTree'. Cria um father node a partir de 2 nós e soma suas frequências para inserir no nó pai
* Obs: O huff_tree->item desse novo nó pai será um '*'
*  @param: 2 nós de Huff_Tree
*/
huffman_tree *tree_father(huffman_tree *node_tree1, huffman_tree *node_tree2);


/* Função que verifica se a árvore está vazia 
*  @param: raiz de uma árvore
*/
bool empty_tree(huffman_tree *hf);

/* Função para impressão de uma árvore dada em Pré-Ordem
*  @param: raiz de uma árvore
*/
void print_pre_order(huffman_tree *hf);

/* Função do tipo booleana que retorna verdadeiro caso um determinado nó da árvore seja uma folha
*  @param: um nó de árvore
*/
bool is_leaf(huffman_tree *node_Tree);

/* Cosntrói a Árvore de Huffman a partir de uma fila de nós de árvore
*  @param: Uma fila de prioridade composta por nós de árvore e um nó de árvore vazio que, ao fim da execução,
*  será o nó raiz da árvore e o único nó da fila de prioridade
*/
huffman_tree *build_tree_huffman(priority_queue *pq, huffman_tree *node_father);

// Obtem o filho da esquerda
huffman_tree *get_left(huffman_tree *hf);

// Obtem o filho da direita
huffman_tree *get_right(huffman_tree *hf);

// Obtem o caracter guardado no nó
byte get_item(huffman_tree *hf);