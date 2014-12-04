#ifndef __SERVER__HANDLER_H_INCLUDED__
#define __SERVER__HANDLER_H_INCLUDED__

#include "server/context.h"
#include "shared/data.h"

namespace server {
  class handler {
    public:
      explicit handler(context &c);

      virtual void handle(shared::msgs::server &message) = 0;


      virtual ~handler();
    protected:
      context &c;
  };
}

#endif
