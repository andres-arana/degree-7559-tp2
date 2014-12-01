#include "raii/msgqueue_owner.h"
#include "syscalls/msgqueue.h"

using namespace raii;

msgqueue_owner::msgqueue_owner()
  : identifier(syscalls::msgget()) {

  }

int msgqueue_owner::id() const {
  return identifier;
}

msgqueue_owner::~msgqueue_owner() {
  syscalls::msgrelease(identifier);
}
