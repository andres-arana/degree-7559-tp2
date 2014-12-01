#include "syscalls/process.h"
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

pid_t syscalls::getpid() {
  auto result = ::getpid();

  if (result < 0) {
    throw syscalls::error("getpid");
  }

  return result;
}
