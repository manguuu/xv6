#include "types.h"
#include "stat.h"
#include "user.h"
#define PNUM 5
#define PRINT_CYCLE 10000000
#define TOTAL_COUNTER 500000000

void sdebug_func() {
    printf(1, "start sdebug command\n");

    /*
    PNUM만큼 반복문을 수행하면서 프로세스를 생성한다
    자식 프로세스에서 cnt의 값을 증가해가며 
    cnt가 print_cycle값이 됐을때 출력하고
    total_counter 값이 되면 자식 프로세스를 종료한다.
    */ 
    for (int i = 1; i <= PNUM; i++) {
        int pid = fork();
        if (pid == 0) {
            if (weightset(i) < 0) continue;
            int cnt = 0;
            int begin = uptime();
            while (1) {
                cnt++;
                if (cnt == PRINT_CYCLE) {
                    int end = uptime();
                    printf(1, "PID: %d, WEIGHT: %d, TIMES: %d ms\n",
                        getpid(), i, (end - begin) * 10);
                }
                if (cnt == TOTAL_COUNTER) {
                    printf(1, "PID: %d terminated\n", getpid());
                    exit();
                }
            }
        }
    }

    for (int i = 1; i <= PNUM; i++) {
        if (wait() < 0) {
            printf(1, "wait stopped early\n");
            exit();
        }
    }

    if (wait() != -1){
        printf(1, "wait got too many\n");
        exit();
    }
  
    printf(1, "end of sdebug command\n");
}

int main() {
    sdebug_func();
    exit();
}