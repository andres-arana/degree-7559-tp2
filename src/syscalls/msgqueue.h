#ifndef __SYSCALLS__MSGQUEUE_H_INCLUDED__
#define __SYSCALLS__MSGQUEUE_H_INCLUDED__

#include "syscalls/error.h"
#include "syscalls/interrupt.h"
#include <stdexcept>
#include <string>

namespace syscalls {
  class removed_queue : public std::runtime_error {
    public:

      explicit removed_queue(
          const std::string &syscall);
  };

  int msgget();

  void msgsnd(int id, const void *message, size_t size);

  void msgrcv(int id, long type, void *message, size_t size);

  void msgrelease(int id);
}

#endif
