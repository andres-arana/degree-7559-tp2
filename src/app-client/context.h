#ifndef __CLIENT__CONTEXT_H_INCLUDED__
#define __CLIENT__CONTEXT_H_INCLUDED__

#include "raii/msgqueue.h"
#include "util/sync_log.h"

namespace client {
  struct context {
    raii::msgqueue &queue;
    util::sync_log &log;
    long client_id;
  };
}

#endif
