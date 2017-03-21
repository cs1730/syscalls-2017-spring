#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <unistd.h>
#include <fcntl.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  const int BUFF_SIZE = 1024; // size of data buffer
  char buffer [BUFF_SIZE];    // data buffer 
  int n = 0;                  // number of bytes read

  while ((n = read(STDIN_FILENO, buffer, BUFF_SIZE)) > 0) {
    if (write(STDOUT_FILENO, buffer, n) == -1) perror("write");
  } // while 

  return EXIT_SUCCESS;
} // main

