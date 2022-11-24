#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int value = 15;
int main() {
  pid_t pid;
  pid = fork();
  if (pid == 0) { /* child process */
    value += 10;
    printf("Child process: value = %d", value); // Check the value in child process
    return 0;
  } else if (pid > 0) { /* parent process */
    wait(NULL);
    printf("Parent process: value = %d", value); /* LINE A */
    return 0;
  }
}
