#ifndef __SERVER__HANDLER_QUERY_ALL_H_INCLUDED__
#define __SERVER__HANDLER_QUERY_ALL_H_INCLUDED__

#include "app-server/handler.h"

namespace server {
  class handler_query_all : public handler {
    public:
      explicit handler_query_all(context & c);

      virtual void handle(shared::msgs::server &message);
  };
}

#endif
