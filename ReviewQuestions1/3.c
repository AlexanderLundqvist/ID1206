#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
  fork();
  fork();
  fork();
  printf("Process executed successfully!\n");
  return 0;
}
