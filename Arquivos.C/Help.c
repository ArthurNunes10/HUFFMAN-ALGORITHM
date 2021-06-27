#include "Help.h"
#include "Byte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <math.h>


byte setBit(byte c, int i){
    byte mask = 1 << i;
    return  mask|c;
}

int is_bit_set(byte c, int i) { 
    byte mask = 1 << i;
return mask & c;
}

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