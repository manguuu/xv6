#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
int printline;

void cat(int fd) {
  int n;
  int cnt = 0;

  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    for (int i = 0; i < n; i++) {
        if (buf[i] == '\n') cnt++;
        if (cnt == printline) {
            n = i + 1;
            break;
        }
    }
    if (write(1, buf, n) != n) {
      printf(1, "cat: write error\n");
      exit();
    }
    if (cnt == printline) return;
  }
  if (n < 0) {
    printf(1, "cat: read error\n");
    exit();
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  printline = atoi(argv[1]);
  if (argc <= 2){
    cat(0);
    exit();
  }

  for(i = 2; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "cat: cannot open %s\n", argv[i]);
      exit();
    }
    cat(fd);
    close(fd);
  }
  exit();
}
