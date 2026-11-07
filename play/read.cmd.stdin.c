#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void) {
  char buf[1024];
  pid_t child_pid;
  int status;

  while (fgets(buf, sizeof(buf), stdin) != 0 /*NULL*/) {
    if (buf[strlen(buf) - 1] == '\n') {
      buf[strlen(buf) - 1] = '\0'; // Remove newline character
    }

    if ((child_pid = fork()) < 0) {
      // man, this is new. I have to think about two saperate
      // processes, one for the parent and one for the child.
      //
      // so fork return 2 values, one for the parent and one for the child.
      // if the return value is 0, then we are in the child process, otherwise we are in the parent process.
      perror("fork error");
      exit(1);
    } else if (child_pid == 0) { // Child process
      execlp(buf, buf, (char *)0);
      fprintf(stderr, "couldn't execute: %s\n", buf);

      exit(127);
    }

    // Parent process
    if ((child_pid = waitpid(child_pid, &status, 0)) < 0) {
      perror("waitpid error");
      exit(1);
    }

    printf("%% ");
  }
  printf("closing stdin (pid %d)\n", getpid());
  exit(0);
}
