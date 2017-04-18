
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>

using std::cout;
using std::endl;

void my_handler(int signo) {
  cout << "NOPE!" << endl;
} // my_handler

int main() {
  // TODO setup signal handler for SIGINT (Interrupt Signal)
  signal(SIGINT, my_handler);
  signal(SIGQUIT, my_handler);
  signal(SIGTERM, SIG_IGN);
  //  while (true) pause(); // wait for signal
  return EXIT_SUCCESS;
} // main

