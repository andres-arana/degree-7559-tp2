#ifndef __SERVER__CONTEXT_H_INCLUDED__
#define __SERVER__CONTEXT_H_INCLUDED__

#include "app-server/db.h"
#include "util/sync_log.h"
#include "raii/msgqueue.h"

namespace server {
  struct context {
    db &data;
    util::sync_log &log;
    raii::msgqueue &queue;
  };
}

#endif
