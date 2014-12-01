#include "syscalls/msgqueue.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>

using namespace std;

namespace {
  constexpr int PERMISSIONS = 0666;
}

syscalls::removed_queue::removed_queue(const string &syscall)
  : runtime_error(syscall) {

  }

int syscalls::msgget() {
  auto result = ::msgget(IPC_PRIVATE, ::PERMISSIONS);
  if (result < 0) {
    throw syscalls::error("msgget");
  }

  return result;
}

void syscalls::msgsnd(int id, const void *message, size_t size) {
  auto result = ::msgsnd(id, message, size, 0);

  if (result < 0) {
    if (errno == EIDRM) {
      throw syscalls::removed_queue("msgsnd");
    } else {
      syscalls::check_interrupt("msgsnd");
    }
  }
}

void syscalls::msgrcv(int id, long type, void *message, size_t size) {
  auto result = ::msgrcv(id, message, size, type, 0);

  if (result < 0) {
    if (errno == EIDRM) {
      throw syscalls::removed_queue("msgrcv");
    } else {
      syscalls::check_interrupt("msgrcv");
    }
  }
}

void syscalls::msgrelease(int id) {
  auto result = ::msgctl(id, IPC_RMID, 0);

  if (result < 0) {
    throw syscalls::error("msgrelease");
  }
}
