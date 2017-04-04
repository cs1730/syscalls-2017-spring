
#include <cstdio>
#include <cstdlib>

int main() {
  setvbuf(stdout, NULL, _IONBF, BUFSIZ);
  printf("unbuffered write!\n");
  return EXIT_SUCCESS;
} // main

