typedef struct priority_queue priority_queue;

/* Cria uma fila alocada dinamicamente e retorna o endereço dessa fila vazia
*  @param: 
*/
priority_queue *construct ();

/* Função básica que retorna o tamanho atual da fila de prioridade
*  @param: a posição head de uma fila
*/
int size_list(priority_queue *pq);

/* Função booleana básica que verifica se a fila recebida está vazia e retorna verdadeiro caso seja vazia
*  @param: a posição head de uma fila
*/
bool empty (priority_queue *pq);

//Cria nó de arvore e adiciona na fila de acordo com sua frequencia
/* Ao ser chamada, cria um novo node_tree com filhos NULL e enfileira na priority_queue de acordo com a frequência inserida no node
*  @param: uma fila de prioridade, um caractere do tipo byte e a frequência desse caractere dentro do arquivo de entrada
*/
void enqueue(priority_queue *pq, byte item, long long int freq);

//Insere o nó pai na fila de prioridade (é igual a enqueue, porém com algumas modificações)
/* Insere um nó pai criado através da função 'TreeFather' que cria um novo nó a partir de 2 nós (somando suas frequências)
* Esse novo nó pai deve ser reinserido na fila de prioridade até que essa fila possua apenas 1 elemento
*  @param: a fila de prioridade e um nó pai que contêm a soma das frequências dos 2 nós filhos
*/
void insert_father(priority_queue *pq, huffman_tree *father);

//tira ó primeiro no da fila, e retorna ele;
/* Desenfileira o primeiro nó da fila de prioridade e retorna esse elemento (no caso da fila de huffman, o elemento é um tree_node)
*  @param: a fila de prioridade
*/
huffman_tree *dequeue(priority_queue *pq);


/* Imprime toda a fila de prioridade
*  @param: a fila de prioridade
*/
void Print_list(priority_queue *pq);