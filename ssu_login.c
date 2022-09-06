#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char userID[16][32];
char pwdID[16][32];
int user_num;

// [param]
// fd: read from fd
// s: destination of reading
int parse(int fd, char *s) {
    char c;
    for (int i = 0; i < 32; i++) {
        if (read(fd, &c, 1) <= 0) return 0;
        if (c == ' ' || c == '\n') return 1;
        s[i] = c;
    }
    return 1;
}

void get_user_list() {
    int fd = open("list.txt", O_RDONLY);
    if (fd < 0) printf(1, "open list.txt error");
    for (int i = 0; i < 16; i++, user_num++) {
        if (!parse(fd, userID[i])) break;
        if (!parse(fd, pwdID[i])) break;
    }
    close(fd);
}

int check_idpw(char *name, char *pwd) {
    for (int i = 0; i < user_num; i++) {
        if (!strcmp(name, userID[i]) && !strcmp(pwd, pwdID[i])) return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    get_user_list();
    char name[32] = {0, };
    char pwd[32] = {0, };
    
    printf(1, "Username: ");
    parse(0, name); // input from fd 0

    printf(1, "Password: ");
    parse(0, pwd);

    if (!check_idpw(name, pwd)) {
        printf(1, "login fail\n");
        return 0;
    }
    
    int pid = fork();
    if (pid < 0) {
      printf(1, "init: fork failed\n");
      exit();
    }
    if (pid == 0) {
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    int wpid;
    while((wpid = wait()) >= 0 && wpid != pid) 
        printf(1, "zombie!\n");
}