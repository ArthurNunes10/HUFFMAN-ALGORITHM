/* Função para pegar o tamanho do lixo e o tamanho da árvore em seu valor binário
*  @param: O arquivo de entrada compactado e dois vetores: um para o lixo e um para a árvore
*/
void get_tree_trash_size(FILE *iFile, int *trash, int *size_tree);

/* Preenche o vetor tree com os caracteres da árvore em pré-ordem
*  @param: Recebe o arquivo, um vetor vazio que vai ser preenchido com os characteres da árvore em pré ordem e o tamanho da árvore
*/
void get_huff_tree(FILE *iFile, byte *tree, int tree_size);

/* Função auxiliar que cria os nós durante a execução da função 'rebuildTree'
*  @param: um caracter, uma frequência (nesse caso não é tão relevante quanto na compress) e os filhos left e right
*/
huffman_tree *create_node2(byte character, long long int freq, huffman_tree *left, huffman_tree *right);

/* Função responsável por reconstruir a árvore
*  @param: Recebe um nó pra ser a raiz, o vetor que contém a árvore em pré ordem, seu tamanho e um ponteiro 
*  que será acessado e incrementado para caminhar pelo vetor que contém a árvore
*/
huffman_tree *rebuildTree(huffman_tree *hf, byte *tree, int size, int *pos);


/* Função responsável por escrever o conteúdo original no arquivo de saída
*  @param: a raiz da árvore reconstruída, o arquivo de entrada comprimido e o arquivo de saída, onde os caracteres originais
*  serão escritos, o tamanho do ilxo e o tamanho da árvore
*/
void write_character_on_file(huffman_tree *rebuild_tree, FILE *iFile, FILE *oFile, int trash, int tree_size);

/* Função responsável por chamar as funções auxiliares para fazer a descompressão do arquivo
*  @param: um arquivo de entrada compactado e o arquivo de saída, onde os caracteres originais serão escritos
*/
void decompress(FILE *iFile, FILE *oFile);