
#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;

int main() {
  cout.setf(std::ios_base::unitbuf); // turn off buffering for cout
  cout << "unbuffered writes!" << endl;
  return EXIT_SUCCESS;
} // main

