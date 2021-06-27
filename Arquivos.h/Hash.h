// Definição das estruturas utilizadas pela Hash
typedef struct hashtable hash;
typedef struct element element;


/* Cria uma nova hash com 256 posições
*  @param: 
*/
hash* createTable();

/* Função auxiliar que é chamada na 'Traveling_Tree' e é usada para dicionar o mapeamento binário e seu respectivo caractere na hash
*  @param: Uma tabela tash, a key de cada posição da hash (caractere), o mapeamento binário desse caractere 
*  e uma variável auxiliar para percorrer as posiçõe do vetor  binary da hash
*/void put_in_hash(hash *hashtable, byte key, byte binary[], long long int pos);

//imprime tabela hash
void print_hash(hash *hashtable);