#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <fcntl.h>
#include <unistd.h>

using std::cout;
using std::endl;

int main(const int argc, const char * argv []) {

  if (argc != 2) {
    cout << "Usage: " << argv[0] << " FILE" << endl;
    exit(EXIT_FAILURE); // see exit(3)
  } // if

  const char * filename = argv[1];
  int fd = open(filename, O_WRONLY);
  int errnum = errno;   // why copy errno? see errno(3)

  if (fd != -1) {
    cout << "Opened " << filename << "; "
	 << "fd = " << fd << "; "
	 << "error = " << strerror(errnum) 
	 << endl;

    char buffer [] = "hello";
    write(fd, buffer, 5);

  } else {
    cout << "Could not open " << filename << "; "
	 << "fd = " << fd  << " (should be -1); "
	 << "error = " << strerror(errnum) 
	 << endl;
    exit(EXIT_FAILURE); // see exit(3)
  } // if
  
  return EXIT_SUCCESS;
} // main

