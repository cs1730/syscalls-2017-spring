
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE); // see exit(3)
  } // if

  // open file
  const char * filename = argv[1];
  int fd = open(filename, O_RDONLY);
  if (fd == -1) perror("open");

  // seek to end
  off_t len = lseek(fd, 0, SEEK_END);
  if (len == -1) perror("lseek");

  // print file size
  cout << filename << " is "
       << len << " bytes in length."
       << endl;

  // close file
  if (close(fd) == -1) perror("close");

} // main

