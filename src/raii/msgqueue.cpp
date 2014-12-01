#include "raii/msgqueue.h"
#include "syscalls/msgqueue.h"

using namespace raii;

msgqueue::msgqueue(int id)
  : identifier(id) {

  }
