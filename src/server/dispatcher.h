#ifndef __SERVER__DISPATCHER_H_INCLUDED__
#define __SERVER__DISPATCHER_H_INCLUDED__

#include "server/context.h"
#include "server/handler.h"
#include <map>
#include <memory>

namespace server {
  class dispatcher {
    public:
      explicit dispatcher(context &c);

      void dispatch_next();
    private:
      context &c;

      std::map<long, std::unique_ptr<handler>> handlers;
  };
}

#endif
