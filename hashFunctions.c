#include <string.h>
#include <stdlib.h>


long ELFHash(char* str) {
    long hash = 0;
    long x = 0;
    for(int i = 0; i < strlen(str); i++) {
        hash = (hash << 4) + str[i];
        if((x = hash & 0xF0000000L) != 0) {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }    
    return hash;
}


