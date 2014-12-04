#ifndef __SERVER__HANDLER_UPSERT_H_INCLUDED__
#define __SERVER__HANDLER_UPSERT_H_INCLUDED__

#include "server/handler.h"

namespace server {
  class handler_upsert : public handler {
    public:
      explicit handler_upsert(context & c);

      virtual void handle(shared::msgs::server &message);
  };
}

#endif
