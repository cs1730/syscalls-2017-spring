
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {
  cout << "before stuff" << endl;                        // print before redirection
  const char * filename = argv[1];                       // get filename
  int fd = open(filename, O_WRONLY | O_CREAT, 0777);     // open file
  if (fd == -1) perror("open");                          // error check open
  int backup = dup(STDOUT_FILENO);                       // make a backup of stdout
  if (dup2(fd, STDOUT_FILENO) == -1) perror("dup2");     // redirect stdout to file
  cout << "stuff" << endl;                               // after first redirection
  if (dup2(backup, STDOUT_FILENO) == -1) perror("dup2"); // restore backup
  if (close(fd) == -1) perror("close");                  // close file
  cout << "after stuff" << endl;                         // after second redirection
  return EXIT_SUCCESS;
} // main
