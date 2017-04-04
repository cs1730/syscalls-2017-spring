
#include <unistd.h>
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

void my_handler1() {
  cout << "my_handler1" << endl;
} // my_handler1

void my_handler2() {
  cout << "my_handler2" << endl;
} // my_handler2

int main() {
  cout.setf(std::ios_base::unitbuf); // turn off buffering for cout
  atexit(my_handler1);
  atexit(my_handler2);
  atexit(my_handler1);
  cout << "hello" << endl;
  //_exit(EXIT_SUCCESS);
  exit(EXIT_SUCCESS);
  cout << "nope" << endl;
  return EXIT_SUCCESS;
} // main

