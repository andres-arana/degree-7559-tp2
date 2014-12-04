#ifndef __SERVER__HANDLER_QUERY_BY_NAME_H_INCLUDED__
#define __SERVER__HANDLER_QUERY_BY_NAME_H_INCLUDED__

#include "server/handler.h"

namespace server {
  class handler_query_by_name : public handler {
    public:
      explicit handler_query_by_name(context & c);

      virtual void handle(shared::msgs::server &message);
  };
}

#endif
