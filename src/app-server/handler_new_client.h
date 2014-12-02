#ifndef __SERVER__HANDLER_NEW_CLIENT_H_INCLUDED__
#define __SERVER__HANDLER_NEW_CLIENT_H_INCLUDED__

#include "app-server/handler.h"

namespace server {
  class handler_new_client : public handler {
    public:
      explicit handler_new_client(context & c);

      virtual void handle(shared::msgs::server &message);
    private:
      long current_client_id;
  };
}

#endif
