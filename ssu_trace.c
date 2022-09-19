#include "types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(1, "ssu_trace err\n");
        exit();
    }
    int pid = fork();
    trace(atoi(argv[1]));
    if (pid == 0) {
        exec(argv[2], argv + 2);
    } else if (pid > 0) {
        wait();
    }
    exit();
}