
//Faz o mapeamento dos caracteres com 0s e 1s e armazena na hash
/* Navega por toda a árvore de huffman já construída e faz o mapeamento da sequência de bits pra cada caractere do arquivo
*  @param: o nó raiz da Huff_Tree, um vetor onde será armazenado o mapeamento de bits dos caracteres, um inteir oque representa
*  a posição no vetor e uma hash vazia que será preenchida durante a execução da função
*/
void traveling_the_Tree(huffman_tree *node_tree, byte binary[], long long int current, hash *table);

/* Escreve a árvore de huffman em pré ordem no arquivo de saída 
*  @param: raiz da árvore e o arquivo de saída
*/
void write_tree(huffman_tree *hf, FILE *oFile);


/* Retorna o tamanho da árvore levando em consideração os caracteres '*' e '\'
*  @param: raiz da árvore
*/
int size_of_tree(huffman_tree *ht);

/* Verifica a quantidade de bits no arquivo de entrada e, a partir disso, faz o cálculo do tamanho do lixo e retorna esse valor
*  @param: um arquivo de entrada e a tabela hash já finalizada com o mapeamento dos bits
*/
long long int sizeTrash(FILE *iFile, hash *hashtable);

/* Cria o cabeçalho do arquivo de saída e escreve o mapeamento de bits dos caracteres bit a bit no arquivo de saída
*  @param: o arquivo de enrtada, o arquivo de saída, a tabela hash finalizada e a raiz da árvore de huffman
*/
void create_header(FILE *iFile, FILE *oFile, hash *hashtable, huffman_tree *node_tree);

/* Função responsável por chamar as funções auxiliares para compressão do arquivo
*  @param: o arquivo de enrtada e o arquivo de saída
*/
void compress(FILE *iFile, FILE *oFile);