
/** Now it works! -- Supa' Mike */
/** See pipe3.cpp for a working example. */

#include <array>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void close_pipe(int pipefd [2]);
vector<char *> mk_cstrvec(vector<string> & strvec);
void dl_cstrvec(vector<char *> & cstrvec);
void nice_exec(vector<string> args);

int main(const int argc, const char * argv []) {

  int pid;

  vector<vector<string>> commands {
    { "cat", "pipe4.cpp" },
    { "grep", "//" },
    { "less" }
  };

  vector<array<int, 2>> pipes;

  for (unsigned int i = 0; i < commands.size(); ++i) {

    if (i != commands.size() - 1) {
      int pipefd [2];
      if (pipe(pipefd) == -1) {
	perror("pipe");
	exit(EXIT_FAILURE);
      } // if
      pipes.push_back({pipefd[0], pipefd[1]});
    } // if

    if ((pid = fork()) == -1) {
      perror("fork");
      exit(EXIT_FAILURE);
    } else if (pid == 0) {

      if (i != 0) {
	if (dup2(pipes.at(i-1)[0], STDIN_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
      } // if

      if (i != commands.size() - 1) {
	if (dup2(pipes.at(i)[1], STDOUT_FILENO) == -1) {
	  perror("dup2");
	  exit(EXIT_FAILURE);
	} // if
      } // if
      
      // close all pipes created so far
      for (unsigned int i = 0; i < pipes.size(); ++i) {
	close_pipe(pipes.at(i).data());
      } // for
      
      nice_exec(commands.at(i));

    } // if

  } // for

  // close all pipes
  for (unsigned int i = 0; i < pipes.size(); ++i) {
    close_pipe(pipes.at(i).data());
  } // for
  
  waitpid(pid, nullptr, 0);
  return EXIT_SUCCESS;

} // main

void close_pipe(int pipefd [2]) {
  if (close(pipefd[0]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
  if (close(pipefd[1]) == -1) {
    perror("close");
    exit(EXIT_FAILURE);
  } // if
} // close_pipe

vector<char *> mk_cstrvec(vector<string> & strvec) {
  vector<char *> cstrvec;
  for (unsigned int i = 0; i < strvec.size(); ++i) {
    cstrvec.push_back(new char [strvec.at(i).size() + 1]);
    strcpy(cstrvec.at(i), strvec.at(i).c_str());
  } // for
  cstrvec.push_back(nullptr);
  return cstrvec;
} // mk_cstrvec

void dl_cstrvec(vector<char *> & cstrvec) {
  for (unsigned int i = 0; i < cstrvec.size(); ++i) {
    delete[] cstrvec.at(i);
  } // for
} // dl_cstrvec

void nice_exec(vector<string> strargs) {
    vector<char *> cstrargs = mk_cstrvec(strargs);
    execvp(cstrargs.at(0), &cstrargs.at(0));
    perror("execvp");
    dl_cstrvec(cstrargs);
    exit(EXIT_FAILURE);
} // nice_exec

