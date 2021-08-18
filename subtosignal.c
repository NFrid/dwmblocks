#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(char* cmd) {
  printf("usage: %s \"callback\"\n", cmd);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    print_help(argv[0]);
    exit(1);
  }

  if (!(strcmp(argv[1], "-h") && strcmp(argv[1], "--help"))) {
    print_help(argv[0]);
    exit(0);
  }

  while (1) {
    while (getchar() != '\n')
      ;
    system(argv[1]);
  }
}
