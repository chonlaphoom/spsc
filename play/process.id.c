#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(void){
  printf("hello from process %d\n", getpid());
  return EXIT_SUCCESS;
}
