

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <dirent.h>

using std::cout;
using std::endl;

int main() {

  struct dirent * entry = nullptr;               // entry pointer
  DIR * pwd = opendir(".");                      // open directory

  if (pwd == nullptr) { 
    perror("opendir");
  } else {
    while ((entry = readdir(pwd)) != nullptr) {  // read entries
      cout << entry->d_name << endl;
    } // while
    closedir(pwd);                               // close directory; avoid memory leak
  } // if

  return EXIT_SUCCESS;

} // main

