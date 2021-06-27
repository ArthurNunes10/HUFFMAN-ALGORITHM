#include "HuffLib.h"

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