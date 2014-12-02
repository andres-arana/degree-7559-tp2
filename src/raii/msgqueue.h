#ifndef __RAII__MSGQUEUE_H_INCLUDED__
#define __RAII__MSGQUEUE_H_INCLUDED__

#include "syscalls/msgqueue.h"

namespace raii {
  class msgqueue {
    public:
      explicit msgqueue(int id);

      explicit msgqueue(const msgqueue& other) = delete;
      msgqueue &operator=(const msgqueue& other) = delete;

      explicit msgqueue(msgqueue &&other) = delete;
      msgqueue &operator=(msgqueue &&other) = delete;

      template<typename T>
      void send(const T &message) {
        syscalls::msgsnd(
            identifier,
            &message,
            sizeof(T) - sizeof(long));
      }

      template<typename T>
      T receive(long type) {
        T result;

        syscalls::msgrcv(
            identifier,
            type,
            &result,
            sizeof(T) - sizeof(long));

        return result;
      }

    private:
      int identifier;
  };
}

#endif
