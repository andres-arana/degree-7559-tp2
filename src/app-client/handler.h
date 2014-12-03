#ifndef __CLIENT__HANDLER_H_INCLUDED
#define __CLIENT__HANDLER_H_INCLUDED

#include "app-client/context.h"
#include <string>
#include <iostream>

namespace client {
  class handler {
    public:
      handler(context &c);

      virtual void handle(const std::string &args) = 0;

      virtual void print_description(std::ostream &os) const = 0;

      virtual std::string summary() const = 0;

      virtual ~handler();

    protected:
      context &c;
  };
}

#endif
