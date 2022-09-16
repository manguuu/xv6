#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv) {
    int msize = memsize();
    printf(1, "The process is using %dB\n", msize);
    
    char *tmp = (char *)malloc(sizeof(char) * 2048);
    printf(1, "Allocating memory\n");

    msize = memsize();
    printf(1, "The process is using %dB\n", msize);

    free(tmp);
    printf(1, "Freeing memory\n");
    
    msize = memsize();
    printf(1, "The process is using %dB\n", msize);

    exit();
}