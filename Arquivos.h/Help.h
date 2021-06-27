/* Função responsável por 'acender' o bit na posição em que foi passada
*  @param: um determinado byte e a posição do bit que será setado dentro do byte
*/
byte setBit(byte c, int i);

/* Verifica se o bit da posição passada está aceso/setado ou não
*  @param: um determinado caracter do tipo byte e a posição do bit a ser verificado
*/
int is_bit_set(byte c, int i);

/* Função que faz a conversão de uma sequência de binários para decimal e retorna esse valor
*  @param: Recebe um vetor de inteiros contendo uma sequência de binários e o tamanho do vetor
*/
int bin_to_dec(int *aux, int size);