#ifndef __CLIENT__HANDLER_SELALL_H_INCLUDED__
#define __CLIENT__HANDLER_SELALL_H_INCLUDED__

#include "app-client/handler.h"
#include "app-client/remote_db.h"

namespace client {
  class handler_selall : public handler {
    public:
      handler_selall(context &c);

      virtual void handle(const std::string &args);

      virtual void print_description(std::ostream &os) const;

      virtual std::string summary() const;
    private:
      remote_db db;
  };
}

#endif
